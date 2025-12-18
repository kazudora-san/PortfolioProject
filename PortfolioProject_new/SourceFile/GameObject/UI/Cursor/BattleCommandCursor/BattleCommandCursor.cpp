#include	"Main.h"
#include	"Renderer/Renderer.h"
#include	"BattleCommandCursor.h"
#include	"Renderer/Polygon2D/Polygon2D.h"
#include	"Input/Input.h"
#include	"Player/Player.h"

enum BattleCommandKey
{
	Battle_Attack = 0,
	Battle_Skill,
	Battle_Guard,
	Battle_Escape,
};

constexpr	XMFLOAT2		BattleCmdCursorPosition		= { 100.0f, 420.0f };
constexpr	XMFLOAT2		BattleCmdCursorMove			= { 0.0f, 50.0f };
constexpr	unsigned int	MaxBattleCmdIndex			= { 3 };

void BattleCommandCursor::Init()
{
	CursorBase::Init();

	Polygon2D* UIWindow = new Polygon2D();
	UIWindow->Init(	BattleCmdCursorPosition.x - CursorScale.x / 2.0f, 
					BattleCmdCursorPosition.y - CursorScale.y / 2.0f,
					CursorScale.x, 
					CursorScale.y,
					m_CursorFileName);

	m_UIWindows.push_back(UIWindow);
}

void BattleCommandCursor::Uninit()
{
	UI::Uninit();
}

void BattleCommandCursor::Update()
{
	UI::Update();

	if (Input::CommandUp())
	{
		m_SelectIndex--;

		if (m_SelectIndex < 0)
		{
			m_SelectIndex = 0;
		}
	}
	if (Input::CommandDown())
	{
		m_SelectIndex++;

		if (m_SelectIndex > MaxBattleCmdIndex)
		{
			m_SelectIndex = MaxBattleCmdIndex;
		}
	}

	if (Input::CommandDecision())
	{
		// ƒRƒ}ƒ“ƒhŒˆ’è

		switch (static_cast<BattleCommandKey>(m_SelectIndex))
		{
		case Battle_Attack:	// ‚±‚¤‚°‚«
		{
			m_OwnerObject->Attack();

			break;
		}
		case Battle_Skill:		// ‚Æ‚­‚¬
		{
			break;
		}
		case Battle_Guard:		// ‚Ú‚¤‚¬‚å
		{
			break;
		}
		case Battle_Escape:	// ‚É‚°‚é
		{
			break;
		}
		default:
			break;
		}

		SetIsDisp(false);
	}

	for (Polygon2D* battlecommandcursor : m_UIWindows)
	{
		if (!battlecommandcursor)
		{
			continue;
		}

		m_Position.y = BattleCmdCursorMove.y * m_SelectIndex;
		battlecommandcursor->SetPosition({ m_Position });
	}
}

void BattleCommandCursor::Draw()
{
	UI::Draw();
}