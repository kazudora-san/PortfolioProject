#ifndef		GAMECHARACTER_H
#define		GAMECHARACTER_H

#include	"GameObject.h"
#include	"Main.h"
#include	<string>

constexpr float		SearchRadius = 2.0f;

class StateMachine;
class AnimationModel;

class CharacterStatus
{
private:
	// ƒpƒ‰ƒ[ƒ^‚Ì”’lİ’è‚ÍAŒp³æ‚Ì"cpp"‚Åİ’è‚·‚é
	int		m_Health		= {};	// HP
	int		m_MaxHealth		= {};	// MaxHP
	int		m_MagicPower	= {};	// MP
	int		m_MaxMagicPower	= {};	// MaxMP
	int		m_Attack		= {};	// UŒ‚—Í
	int		m_Defense		= {};	// ç”õ—Í
	int		m_Agility		= {};	// ‘f‘‚³
	int		m_Luck			= {};	// ‰^

public:
	CharacterStatus();
	CharacterStatus(int health,		int maxHealth,
					int magicPower,	int maxMagicPower,
					int attack,		int defense,
					int agility,	int luck);

	void	InitCharacterStatus(const CharacterStatus& CharacterStatus);

	void	SetHealth(int health) { m_Health = health; }

	int		GetHealth()			const { return m_Health; }
	int		GetMaxHealth()		const { return m_MaxHealth; }
	int		GetMagicPower()		const { return m_MagicPower; }
	int		GetMaxMagicPower()	const { return m_MaxMagicPower; }
	int		GetAttack()			const { return m_Attack; }
	int		GetDefense()		const { return m_Defense; }
	int		GetAgility()		const { return m_Agility; }
	int		GetLuck()			const { return m_Luck; }
};

class GameCharacter : public GameObject
{
protected:
	CharacterStatus				m_CharacterStatus	= {};
	StateMachine*				m_StateMachine		= {};

	ID3D11InputLayout*			m_VertexLayOut		= {};
	ID3D11PixelShader*			m_PixelShader		= {};
	ID3D11VertexShader*			m_VertexShader		= {};

	AnimationModel*				m_AnimationModel	= {};
	std::string					m_AnimationName		= {};
	std::string					m_AnimationNameNext	= {};
	float						m_AnimationBlend	= {};

	unsigned int				m_Frame				= {};

public:
	virtual void	Init()		override;
	virtual void	Uninit()	override;
	virtual void	Update()	override;
	virtual void	Draw()		override;

	virtual void	Attack()		= 0;
	virtual void	Idle()			= 0;
	virtual void	Move()			= 0;
	bool			IsCritical();

	CharacterStatus&	GetCharacterStatus() { return m_CharacterStatus; }
};

#endif // GAMECHARACTER_H