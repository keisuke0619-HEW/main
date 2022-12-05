#include "Controller.hpp"

// コントローラとキーボードどちらも動くようにしておいてください。



// コントローラーを使用するために必要そうなことをここに書く。
// 毎フレームのアップデートの前に呼ばれる
void Utility::ControllerUpdate()
{
	////ゲームパッドの状態を取得
	//XINPUT_STATE state;
	//XInputGetState(0, &state);
	//int iPad_left = 0, iPad_right = 0, iPad_up = 0, iPad_down = 0;
	//int iPad_leftshoulder = 0, iPad_rightshoulder = 0;
	//int iPad_A = 0, iPad_B = 0, iPad_X = 0, iPad_Y = 0;
	//if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) iPad_left = 1;//ゲームパッド十字キー左
	//if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) iPad_right = 1;//ゲームパッド十字キー右
	//if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) iPad_up = 1;//ゲームパッド十字キー上
	//if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) iPad_down = 1;//ゲームパッド十字キー下
	//if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) iPad_leftshoulder = 1;//ゲームパッドL
	//if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) iPad_rightshoulder = 1;//ゲームパッドR
	//if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) iPad_A = 1;//ゲームパッドA
	//if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B) iPad_B = 1;//ゲームパッドB
	//if (state.Gamepad.wButtons & XINPUT_GAMEPAD_X) iPad_X = 1;//ゲームパッドX
	//if (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) iPad_Y = 1;//ゲームパッドY
	////ゲームパッドアナログスティックのデッドゾーン処理
	//if ((state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
	//	(state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	//{
	//	state.Gamepad.sThumbLX = 0;
	//	state.Gamepad.sThumbLY = 0;
	//}
}
// 押された瞬間だけTrue
bool Utility::GetKeyTrigger(ControllerID)
{
    return false;
}
// 押している間True
bool Utility::GetKeyPress(ControllerID)
{
    return false;
}
// 離された瞬間だけTrue
bool Utility::GetKeyRelease(ControllerID)
{
    return false;
}

DirectX::XMFLOAT3 Utility::GetLeftStick()
{
    return DirectX::XMFLOAT3();
}

DirectX::XMFLOAT3 Utility::GetRightStick()
{
    return DirectX::XMFLOAT3();
}
