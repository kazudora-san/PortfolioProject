#ifndef		PLAYER_H
#define		PLAYER_H

#include	"GameCharacter/GameCharacter.h"

class AudioManager;
class Camera;
class MeshField;

class Player : public GameCharacter
{
private:
	Camera*			m_Camera		= {};
	AudioManager*	m_Audio			= {};
	MeshField*		m_MeshField		= {};

	float			m_Jump			= {};
	bool			m_IsJump		= {};
	float			m_JumpTime		= {};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};

#endif // PLAYER_H