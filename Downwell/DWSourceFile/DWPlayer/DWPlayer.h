//-----------------------------
//	Player.h[プレイヤー制御]
//	千葉知輝
//	作成日 2025/10/06
//-----------------------------

#ifndef DWPLAYER_H
#define DWPLAYER_H

#include "DWInGameCharacter.h"
#include "DWVector2/DWVector2.h"
#include "DWManager/DWBulletManager/DWBulletManager.h"
#include "DWInput/DWInput.h"
#include "DWManager/DWStageManager/DWStageManager.h"
#include "DWUI/DWWSystemUI/DWResultUI/DWResultUI.h"

class DWAudioManager;

constexpr int MaxAmmoCount = 10;
constexpr DWVector2 PlayerMoveSpeed = { 5.0f, 0.0f };
constexpr float MaxUpAceel = -5.0f;
constexpr int DamageInvincibleCount = 180;

class DWPlayer : public DWInGameCharacter
{
private:
	DWVector2	MoveSpeed			= PlayerMoveSpeed;	// 進む方向
	int			CurrentAmmo			= MaxAmmoCount;				// 現在の弾の数
	const int	MaxAmmo				= MaxAmmoCount;
	const float GravityFactor		= Gravity / GravityScale;	// 落下速度の調整
	const float	ExtraUpAccel		= MaxUpAceel;				// ジャンプボタンを長押しした時の上昇量
	const int	DamageInvincibleTime = DamageInvincibleCount;
	int			CurrentInvincibleTime = 0;
	bool		bIsInvincible		= false;
	DWBulletManager* BulletManager	= nullptr;
	DWStageManager* StageManager	= nullptr;
	DWResultUI*		ResultUI		= nullptr;
	DWAudioManager* AudioManager	= nullptr;

public:
	virtual	void	Init()			override;
	virtual	void	Uninit()		override;
	virtual	void	Update()		override;
	virtual	void	Draw()	const	override;

	void	Move();				// 移動処理
	void	Fall();
	void	Ground();
	void	Jump(float extraUpAccel);
	void	Shot();

	int			GetCurrentAmmo	()	const { return CurrentAmmo; }
	float		GetExtraUpAccel()	const { return ExtraUpAccel; }

	virtual void	Reset()	override;

	virtual void OnCollision(DWGameObject* gameObject, const DWVector2& overlap) override;
};

#endif // PLAYER_H
