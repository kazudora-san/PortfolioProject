#ifndef		ENEMYBASE_H
#define		ENEMYBASE_H

#include	"GameCharacter/GameCharacter.h"
#include	<string>

class EnemyBase : public GameCharacter
{
private:


public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};

#endif // PLAYER_H