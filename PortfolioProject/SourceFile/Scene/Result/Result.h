#pragma once

#include "Scene/Scene.h"

class AudioManager;

class Result : public Scene
{
private:
	AudioManager* m_Audio = {};
	unsigned int m_Frame = {};

public:
	void Init();
	void Update();
};