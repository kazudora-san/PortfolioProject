#include "Main.h"
#include "Renderer/Renderer.h"
#include "BattleCommandCursor.h"
#include "Renderer/Polygon2D/Polygon2D.h"
#include "Input/Input.h"
#include "Player/Player.h"

enum BattleCommandKey
{
	BattleAttack = 0,
	BattleSkill,
	BattleGuard,
	BattleEscape,
	BattleMax,
};

constexpr XMFLOAT2 BattleCommandCursorPosition = { 100.0f, 420.0f };
constexpr XMFLOAT2 BattleCommandCursorMove = { 0.0f, 50.0f };
constexpr unsigned int MaxBattleCmdIndex = { BattleMax };	// コマンドによって選択番号を割り振る

void BattleCommandCursor::Init()
{
	CursorBase::Init();

	// 親クラスでdeleteする
	Polygon2D* UIWindow = new Polygon2D();
	UIWindow->Init(
		BattleCommandCursorPosition.x - CursorScale.x / 2.0f,
		BattleCommandCursorPosition.y - CursorScale.y / 2.0f,
		CursorScale.x,
		CursorScale.y,
		m_CursorFileName
	);

	m_UIWindows.push_back(UIWindow);
}

void BattleCommandCursor::Uninit()
{
	CursorBase::Uninit();
}

void BattleCommandCursor::Update()
{
	CursorBase::Update();

	CursorMove();
	Select();
}

void BattleCommandCursor::Draw()
{
	CursorBase::Draw();
}

void BattleCommandCursor::CursorMove()
{
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
}

void BattleCommandCursor::Select()
{
	if (Input::CommandDecision())
	{
		// コマンド決定
		switch (static_cast<BattleCommandKey>(m_SelectIndex))
		{
		case BattleAttack:	// こうげき
		{
			m_OwnerObject->Attack();
			break;
		}
		case BattleSkill:	// とくぎ
		{
			break;
		}
		case BattleGuard:	// ぼうぎょ
		{
			break;
		}
		case BattleEscape:	// にげる
		{
			break;
		}
		default:
			break;
		}

		SetIsDisp(false);
	}
}