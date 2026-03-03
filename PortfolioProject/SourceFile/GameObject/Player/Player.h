#ifndef		PLAYER_H
#define		PLAYER_H

#include	"GameCharacter/GameCharacter.h"

class AudioManager;
class Camera;
class MeshField;

class Player : public GameCharacter
{
private:
	unsigned int	m_CurrentLevel	= {};
	unsigned int	m_CurrentExp	= {};
	Camera*			m_Camera		= {};
	AudioManager*	m_Audio			= {};
	MeshField*		m_MeshField		= {};
	float			m_Jump			= {};
	float			m_JumpTime		= {};
	

public:
	virtual void	Init()			override;
	virtual void	Uninit()		override;
	virtual void	Update()		override;
	virtual void	Draw()			override;

	virtual void	Attack()		override;
	virtual void	Idle()			override;
	virtual void	Move()			override;
};

#endif // PLAYER_H