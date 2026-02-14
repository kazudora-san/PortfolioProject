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
	unsigned	int			m_Health		= {};	// HP
	unsigned	int			m_MaxHealth		= {};	// MaxHP
	unsigned	int			m_MagicPower	= {};	// MP
	unsigned	int			m_MaxMagicPower	= {};	// MaxMP
	unsigned	int			m_Attack		= {};	// UŒ‚—Í
	unsigned	int			m_Defense		= {};	// ç”õ—Í
	unsigned	int			m_Agility		= {};	// ‘f‘‚³
	unsigned	int			m_Luck			= {};	// ‰^

public:
	CharacterStatus();
	CharacterStatus(unsigned int health,		unsigned int maxHealth,
					unsigned int magicPower,	unsigned int maxMagicPower,
					unsigned int attack,		unsigned int defense,
					unsigned int agility,		unsigned int luck);

	void	InitCharacterStatus(const CharacterStatus& CharacterStatus);

	void	SetHealth(unsigned int health) { m_Health = health; }

	unsigned int	GetHealth()			const { return m_Health; }
	unsigned int	GetMaxHealth()		const { return m_MaxHealth; }
	unsigned int	GetMagicPower()		const { return m_MagicPower; }
	unsigned int	GetMaxMagicPower()	const { return m_MaxMagicPower; }
	unsigned int	GetAttack()			const { return m_Attack; }
	unsigned int	GetDefense()		const { return m_Defense; }
	unsigned int	GetAgility()		const { return m_Agility; }
	unsigned int	GetLuck()			const { return m_Luck; }
};

class GameCharacter : public GameObject
{
protected:
	CharacterStatus				m_CharacterStatus	= {};
	std::vector<StateMachine*>	m_State				= {};

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

#endif // PLAYER_H