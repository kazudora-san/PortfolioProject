//-----------------------------
//	DWPlayer.cpp[プレイヤー処理]
//	千葉知輝
//	作成日 2025/10/06
//-----------------------------

#include "DWMain.h"
#include "DWPlayer.h"
#include "DWComponent/DWStateMachine/DWStateMachine.h"
#include "DWPlayerState/DWPlayerIdle/DWPlayerIdle.h"
#include "DWPlayerState/DWPlayerMove/DWPlayerMove.h"
#include "DWPlayerState/DWPlayerFall/DWPlayerFall.h"
#include "DWPlayerState/DWPlayerLand/DWPlayerLand.h"
#include "DWPlayerState/DWPlayerJump/DWPlayerJump.h"
#include "DWPlayerState/DWPlayerShot/DWPlayerShot.h"
#include "DWManager/DWAudioManager/DWAudioManager.h"

constexpr DWVector2 PlayerScale = { 90.0f, 90.0f };
constexpr DWVector2 PlayerPosition = { ScreenResolutionWidth / 2.0f - PlayerScale.x / 2.0f, 0.0f }; // 画面の真ん中上
constexpr float JumpHeight = -5.0f;
constexpr int PlayerHealth = 4;

void DWPlayer::Init()
{
	Position = PlayerPosition;
	Scale = PlayerScale;
	Health = PlayerHealth;
	Tag = "Player";
	bEnable = true;
	bActive = true;

	// コンポーネントの追加
	Collider = AddComponent<DWBoxCollider>(this);
	if (!Collider)
	{
		return;
	}

	DWStateMachine* stateMachine = AddComponent<DWStateMachine>(this);

	if (stateMachine)
	{
		// 各ステートの登録
		stateMachine->RegistState(new DWPlayerIdle(this));
		stateMachine->RegistState(new DWPlayerMove(this));
		stateMachine->RegistState(new DWPlayerFall(this));
		stateMachine->RegistState(new DWPlayerLand(this));
		stateMachine->RegistState(new DWPlayerJump(this));
		stateMachine->RegistState(new DWPlayerShot(this));

		stateMachine->ChangeState("PlayerFall");
	}
	
	// Component→継承したクラスのInitが呼ばれるので、
	// stateMachine->Init()は不要
	RegistPendingComponent();

	if (Scene)
	{
		BulletManager = Scene->GetManager<DWBulletManager>();
		StageManager = Scene->GetManager<DWStageManager>();
		ResultUI = Scene->GetGameObject<DWResultUI>();
		AudioManager = Scene->GetManager<DWAudioManager>();
	}

	// 画像読み込み
	Texture = LoadGraph("asset\\texture\\Player\\Player.png");
}

void DWPlayer::Uninit()
{
	// 読み込んでいる画像を消去
	DeleteGraph(Texture);

	DWInGameCharacter::Uninit();
}

void DWPlayer::Update()
{
 	if (!bEnable)
	{
		return;
	}

	DWInGameCharacter::Update();

	Position += Velocity;

	if (CurrentInvincibleTime > DamageInvincibleTime)
	{
		bIsInvincible = false;
	}
	else
	{
		CurrentInvincibleTime++;
	}

#ifdef _DEBUG
	//--------------------
	// デバッグ用
	//--------------------
	DWStateMachine* stateMachine = GetComponent<DWStateMachine>();
	if (!stateMachine)
	{
		return;
	}

	DWState* state = stateMachine->GetCurrentState();
	if (!state)
	{
		return;
	}


	StateName_Debug = state->GetStateName();
#endif
}

void DWPlayer::Draw() const
{
	DWInGameCharacter::Draw();

#ifdef _DEBUG
	
	printfDx("\nプレイヤー\n");
	printfDx("\nStateName　　　　：%s", StateName_Debug.c_str());
	printfDx("\nステータス\n");
	printfDx("\nPosition X　　　：%f", Position.x);
	printfDx("\nPosition Y　　　：%f", Position.y);
	printfDx("\nVelocity X　　　：%f", Velocity.x);
	printfDx("\nVelocity Y　　　：%f", Velocity.y);
	printfDx("\nHealth　　　　　：%f", Health);
	printfDx("\n残弾数　　　　　：%d", CurrentAmmo);
	printfDx("\nIsShotFlag　　　：");

#endif // _DEBUG
}

void DWPlayer::Move()
{
	Velocity.x = 0.0f;

	DWInput* input = GetInput();

	if (!input)
	{
		return;
	}

	// 左に移動
	if (input->GetLeftMove())
	{
		Velocity.x = -MoveSpeed.x;
	}

	// 右に移動
	if (input->GetRightMove())
	{
		Velocity.x = MoveSpeed.x;
	}
}

void DWPlayer::Fall()
{
	//--------------------
	// デバッグ用(加算数値)
	//--------------------
	Velocity.y += GravityFactor;
}

void DWPlayer::Ground()
{
	Velocity.y = 0.0f;
	CurrentAmmo = MaxAmmo;
}

void DWPlayer::Jump(float extraUpAccel)
{
	if (AudioManager)
	{
		AudioManager->PlaySE("Jump");
	}

	Velocity.y = JumpHeight + extraUpAccel;
}

void DWPlayer::Shot()
{
	if (!BulletManager)
	{
		return;
	}

	if (AudioManager)
	{
		AudioManager->ReStartSE("Shot");
	}

	const DWVector2& setPosition = { Position.x + Scale.x / 2 - BulletScale.x / 2.0f,
										Position.y + Scale.y };
	BulletManager->SetBullet(setPosition);

	Velocity.y = GravityFactor;

	CurrentAmmo--;
}

void DWPlayer::Reset()
{
	Position = PlayerPosition;

	if (StageManager)
	{
		if (StageManager->GetReStartFlag())
		{
			Health = PlayerHealth;
		}
	}
	
	DWStateMachine* stateMachine = GetComponent<DWStateMachine>();
	if (stateMachine)
	{
		stateMachine->ChangeState("PlayerFall");
	}

	Velocity = { 0.0f, 0.0f };
	CurrentAmmo = MaxAmmo;
	SetEnable(true);
}

void DWPlayer::OnCollision(DWGameObject* gameObject, const DWVector2& overlap)
{
	if (!gameObject)
	{
		return;
	}

	if (gameObject->GetTag() == "EnemyGround")
	{
		if (bIsInvincible)
		{
			return;
		}

		if (AudioManager)
		{
			AudioManager->PlaySE("PlayerDamageHit");
		}

		Health--;
		bIsInvincible = true;
		CurrentInvincibleTime = false;

		if (Health <= 0)
		{
			SetEnable(false);

			if (AudioManager)
			{
				AudioManager->StopBGM("GameBGM");
			}

			if (!ResultUI)
			{
				if (!Scene)
				{
					return;
				}

				ResultUI = Scene->GetGameObject<DWResultUI>();

				if (!ResultUI)
				{
					return;
				}
			}

			ResultUI->ResultUIDisp();
		}

		return;
	}

	if (gameObject->GetTag() == "NormalBlock" ||
		gameObject->GetTag() == "BreakBlock")
	{
		if (!Collider)
		{
			return;
		}

		const DWVector2& pushOut = overlap;

		// めり込んだ分を押し出し
		if (overlap.x < overlap.y)
		{
			if (GetPosition().y + Scale.y / 2.0f < gameObject->GetPosition().y)
			{
				return;
			}

			// X軸
			if (GetPosition().x < gameObject->GetPosition().x)
			{
				Position = { Position.x - overlap.x, Position.y };
			}
			else
			{
				Position = { Position.x + overlap.x, Position.y };
			}
		}
		else
		{
			// Y軸
			if (GetPosition().y < gameObject->GetPosition().y)
			{
				if (StageManager)
				{
					StageManager->CurrentStageView();
				}

				if(AudioManager)
				{
					AudioManager->PlayBGM("GameBGM");
				}
				
				Collider->SetHitFlagY(true);
				Position = { Position.x, Position.y - overlap.y };
			}
			else
			{
				Position = { Position.x, Position.y + overlap.y };
				

				if (Velocity.y < 0.0f)
				{
					Velocity.y = 0.0f;
				}
			}
		}

		Collider->SetBoxPosition(Position);

		return;
	}
}