#ifndef		PLAYER_H
#define		PLAYER_H

#include	"GameCharacter/GameCharacter.h"

class AudioManager;
class Camera;
class MeshField;
class Score;

class Player : public GameCharacter
{
private:
	Camera*			m_Camera		= {};
	AudioManager*	m_Audio			= {};
	MeshField*		m_MeshField		= {};
	Score*			m_Money			= {};
	float			m_Jump			= {};
	bool			m_IsJump		= {};
	float			m_JumpTime		= {};

public:
	virtual void	Init()		override;
	virtual void	Uninit()	override;
	virtual void	Update()	override;
	virtual void	Draw()		override;

	void			Attack();
};

#endif // PLAYER_H