#ifndef		PLAYER_H
#define		PLAYER_H

#include	"GameCharacter/GameCharacter.h"
#include	<string>

class AnimationModel;
class AudioManager;
class Camera;
class MeshField;

class Player : public GameCharacter
{
private:
	Camera*			m_Camera		= nullptr;
	AudioManager*	m_Audio			= nullptr;
	MeshField*		m_MeshField		= nullptr;

	float m_Jump = 0.0f;
	bool m_IsJump = false;
	float m_JumpTime = 0.0f;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};

#endif // PLAYER_H