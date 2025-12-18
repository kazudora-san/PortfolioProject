#ifndef		GAMECHARACTER_H
#define		GAMECHARACTER_H

#include	"GameObject.h"
#include	<string>

constexpr float		SearchRadius	= 2.0f;

class GameCharacter : public GameObject
{
protected:
	unsigned	int			m_Health		= {};	// HP
	unsigned	int			m_MaxHealth		= {};	// MaxHP
	unsigned	int			m_MasicPower	= {};	// MP
	unsigned	int			m_MaxMasicPower	= {};	// MaxMP
	unsigned	int			m_Attack		= {};	// çUåÇóÕ
	unsigned	int			m_Defense		= {};	// éÁîıóÕ
	unsigned	int			m_Agility		= {};	// ëfëÅÇ≥
	unsigned	int			m_Luck			= {};	// â^		0Å`50

	ID3D11InputLayout*		m_VertexLayOut;
	ID3D11PixelShader*		m_PixelShader;
	ID3D11VertexShader*		m_VertexShader;


	class AnimationModel*	m_AnimationModel;
	std::string				m_AnimationName;
	std::string				m_AnimationNameNext;
	float					m_AnimationBlend;

	unsigned int			m_Frame;

public:
	virtual void	Init()		override;
	virtual void	Uninit()	override;
	virtual void	Update()	override;
	virtual void	Draw()		override;

	virtual void	Attack()		= 0;
	bool			IsCritical();


	void	SetHealth			(unsigned int health)		{ m_Health			= health; }
	void	SetMaxHealth		(unsigned int maxHealth)	{ m_MaxHealth		= maxHealth; }
	void	SetMasicPower		(unsigned int masicPower)	{ m_MasicPower		= masicPower; }
	void	SetMaxMasicPower	(unsigned int maxMasicPower){ m_MaxMasicPower	= maxMasicPower; }
	void	SetAttack			(unsigned int attack)		{ m_Attack			= attack; }
	void	SetDefense			(unsigned int defense)		{ m_Defense			= defense; }
	void	SetAgility			(unsigned int agility)		{ m_Agility			= agility; }
	void	SetLuck				(unsigned int luck)			{ m_Luck			= luck; }

	unsigned int	GetHealth			() const { return m_Health;}
	unsigned int	GetMaxHealth		() const { return m_MaxHealth;}
	unsigned int	GetMasicPower		() const { return m_MasicPower;}
	unsigned int	GetMaxMasicPower	() const { return m_MaxMasicPower;}
	unsigned int	GetAttack			() const { return m_Attack;}
	unsigned int	GetDefense			() const { return m_Defense;}
	unsigned int	GetAgility			() const { return m_Agility;}
	unsigned int	GetLuck				() const { return m_Luck;}
};

#endif // PLAYER_H