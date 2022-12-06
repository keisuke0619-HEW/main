#include "Controller.hpp"

// コントローラとキーボードどちらも動くようにしておいてください。
namespace Utility
{
	int g_PadID = -1;
	XINPUT_STATE g_keyState;
	XINPUT_STATE g_keyStateOld;
}


// コントローラーを使用するために必要そうなことをここに書く。
// 毎フレームのアップデートの前に呼ばれる
void Utility::ControllerUpdate()
{
	//ゲームパッドの状態を取得
	XINPUT_STATE state;
	XInputGetState(0, &state);

	g_keyStateOld = g_keyState;
	XInputGetState(0, &g_keyState);

	DWORD dwResult = XInputGetState(0, &state);
	if (dwResult == ERROR_SUCCESS)
	{
		// Controller is connected
		// 接続されている
	}
	else
	{
		// Controller is not connected
		// 接続されていない
	}


	/*g_PadID = -1;
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
		g_PadID = 0;
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B)
		g_PadID = 1;
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_X)
		g_PadID = 2;
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y)
		g_PadID = 3;
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)	
		g_PadID = 4;
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)	
		g_PadID = 5;
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)	
		g_PadID = 6;
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)	
		g_PadID = 7;*/
}
// 押された瞬間だけTrue
bool Utility::GetKeyTrigger(unsigned id)
{
	bool now = g_keyState.Gamepad.wButtons & id;
	bool old = g_keyStateOld.Gamepad.wButtons & id;
	return now && !old;
	return false;
}
// 押している間True
bool Utility::GetKeyPress(unsigned id)
{
	return g_keyState.Gamepad.wButtons & id;
	/*if (g_PadID == id)
	{
		return true;
	}
	return false;*/
}
// 離された瞬間だけTrue
bool Utility::GetKeyRelease(unsigned id)
{
	bool now = g_keyState.Gamepad.wButtons & id;
	bool old = g_keyStateOld.Gamepad.wButtons & id;
	return old && !now;
}

DirectX::XMFLOAT3 Utility::GetLeftStick()
{
	DirectX::XMFLOAT3 stick = {};
	stick.x = g_keyState.Gamepad.sThumbLX / (float)0x7fff;
	stick.y = g_keyState.Gamepad.sThumbLY / (float)0x7fff;
	stick.z = 0;
	return stick;
}

DirectX::XMFLOAT3 Utility::GetRightStick()
{
	DirectX::XMFLOAT3 stick = {};
	stick.x = g_keyState.Gamepad.sThumbRX / (float)0x7fff;
	stick.y = g_keyState.Gamepad.sThumbRY / (float)0x7fff;
	stick.z = 0;
	return stick;
}
