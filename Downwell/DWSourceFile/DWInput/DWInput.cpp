//-----------------------------
//	DWInput.cpp[キーボード処理]
//	千葉知輝
//	作成日 2025/10/02
//-----------------------------

#include "DWMain.h"
#include "DWInput.h"


void DWInput::UpdateKey()
{
	PreviousPadState = PadState;

	PadState = GetJoypadInputState(DX_INPUT_PAD1);

	// 前フレームの状態保存
	memcpy(PreviousKey, CurrentKey, 256);

	// 全てーの（キーボードの）キーを取得
	GetHitKeyStateAll(CurrentKey);
}

bool DWInput::GetKeyDown(int keycode) const
{
	// １フレーム前キーを押していなかった
	// 現在キーを押されている
	return CurrentKey[keycode] != 0 && PreviousKey[keycode] == 0;
}

bool DWInput::GetKeyUp(int keycode) const
{
	// １フレーム前キーを押されていた
	// 現在キーを押していない
	return CurrentKey[keycode] == 0 && PreviousKey[keycode] != 0;
}

bool DWInput::GetActionKeyPad(int keycode) const
{
	return (PadState & keycode);
}

bool DWInput::GetActionDownPad(int keycode) const
{
	return (PreviousPadState != PadState &&
		!(PreviousPadState & keycode) &&
		PadState & keycode);
}

bool DWInput::GetLeftMove() const
{
	if (CheckHitKey(KEY_INPUT_A) || (PadState & PAD_INPUT_LEFT))
	{
		return true;
	}

	return false;
}

bool DWInput::GetRightMove() const
{
	if (CheckHitKey(KEY_INPUT_D) || (PadState & PAD_INPUT_RIGHT))
	{
		return true;
	}

	return false;
}

bool DWInput::GetActionKey() const
{
	if (CheckHitKey(KEY_INPUT_RSHIFT) || CheckHitKey(KEY_INPUT_SPACE) ||
		GetActionKeyPad(PAD_INPUT_A))
	{
		return true;
	}

	return false;
}

bool DWInput::GetActionDown() const
{
	if (GetKeyDown(KEY_INPUT_RSHIFT) || GetKeyDown(KEY_INPUT_SPACE) ||
		GetActionDownPad(PAD_INPUT_A))
	{
		return true;
	}

	return false;
}

bool DWInput::GetTitleKeyDown() const
{
	if (GetKeyDown(KEY_INPUT_RETURN) || GetActionDownPad(PAD_INPUT_B))
	{
		return true;
	}

	return false;
}
