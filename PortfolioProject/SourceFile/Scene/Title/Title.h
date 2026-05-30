#pragma once

#include "Scene/Scene.h"
#include <string>

class AudioManager;
class AnimationModel;

class Title : public Scene
{
private:
	unsigned int m_Frame = {};
	unsigned int m_StopFrame = {};
	bool m_IsNextScene = {};

	AudioManager* m_Audio = {};

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;
};