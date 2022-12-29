#include "Controller.hpp"
namespace Utility
{
    XINPUT_STATE g_keyState;
    XINPUT_STATE g_keyStateOld;
    
    float g_cameraSpeedY;
    float g_cameraSpeedX;
	ControllerID g_keyID[KeySet::KEY_SET_MAX];
	ControllerID g_padID[KeySet::KEY_SET_MAX];

	// 押された瞬間
	bool GetKeyTrigger(ControllerID id);
	// 押されている間
	bool GetKeyPress(ControllerID id);
	// 離された瞬間
	bool GetKeyRelease(ControllerID id);

}


void Utility::ControllerInit()
{
    g_cameraSpeedY = 10.0f;
    g_cameraSpeedX = 10.0f;
	g_padID[KeySet::KEY_BEAM] = ControllerID::Pad_RT;
	g_keyID[KeySet::KEY_BEAM] = ControllerID::Key_B;
	g_padID[KeySet::KEY_JUMP] = ControllerID::Pad_A;
	g_keyID[KeySet::KEY_JUMP] = ControllerID::Key_SPACE;
	g_padID[KeySet::KEY_SELECT] = ControllerID::Pad_A;
	g_keyID[KeySet::KEY_SELECT] = ControllerID::Key_RETURN;
	g_padID[KeySet::KEY_CANCEL] = ControllerID::Pad_B;
	g_keyID[KeySet::KEY_CANCEL] = ControllerID::Key_ESCAPE;
	g_padID[KeySet::KEY_RIGHT] = ControllerID::Pad_RIGHT;
	g_keyID[KeySet::KEY_RIGHT] = ControllerID::Key_Right;
	g_padID[KeySet::KEY_LEFT] = ControllerID::Pad_LEFT;
	g_keyID[KeySet::KEY_LEFT] = ControllerID::Key_Left;
	g_padID[KeySet::KEY_DOWN] = ControllerID::Pad_DOWN;
	g_keyID[KeySet::KEY_DOWN] = ControllerID::Key_Down;
	g_padID[KeySet::KEY_UP] = ControllerID::Pad_UP;
	g_keyID[KeySet::KEY_UP] = ControllerID::Key_Up;
	g_padID[KeySet::KEY_CONFIG] = ControllerID::Key_TAB;
	g_keyID[KeySet::KEY_CONFIG] = ControllerID::Key_TAB;
	g_padID[KeySet::KEY_MOVE_W] = ControllerID::Key_W;
	g_keyID[KeySet::KEY_MOVE_W] = ControllerID::Key_W;
	g_padID[KeySet::KEY_MOVE_A] = ControllerID::Key_A;
	g_keyID[KeySet::KEY_MOVE_A] = ControllerID::Key_A;
	g_padID[KeySet::KEY_MOVE_S] = ControllerID::Key_S;
	g_keyID[KeySet::KEY_MOVE_S] = ControllerID::Key_S;
	g_padID[KeySet::KEY_MOVE_D] = ControllerID::Key_D;
	g_keyID[KeySet::KEY_MOVE_D] = ControllerID::Key_D;
	g_padID[KeySet::KEY_CAMERA_UP] = ControllerID::Key_Up;
	g_keyID[KeySet::KEY_CAMERA_UP] = ControllerID::Key_Up;
	g_padID[KeySet::KEY_CAMERA_DOWN] = ControllerID::Key_Down;
	g_keyID[KeySet::KEY_CAMERA_DOWN] = ControllerID::Key_Down;
	g_padID[KeySet::KEY_CAMERA_RIGHT] = ControllerID::Key_Right;
	g_keyID[KeySet::KEY_CAMERA_RIGHT] = ControllerID::Key_Right;
	g_padID[KeySet::KEY_CAMERA_LEFT] = ControllerID::Key_Left;
	g_keyID[KeySet::KEY_CAMERA_LEFT] = ControllerID::Key_Left;
	g_padID[KeySet::KEY_DEBUG_RETURN] = ControllerID::Key_RETURN;
	g_keyID[KeySet::KEY_DEBUG_RETURN] = ControllerID::Key_RETURN;
}

void Utility::ControllerUpdate()
{
    g_keyStateOld = g_keyState;
    XInputGetState(0, &g_keyState);
}



//--- ここから実装 ---//
bool Utility::GetKeyTrigger(KeySet key)
{
	// 例
	return GetKeyTrigger(g_keyID[key]) || GetKeyTrigger(g_padID[key]);
	
}

bool Utility::GetKeyPress(KeySet key)
{
	return Utility::GetKeyPress(g_keyID[key]) || GetKeyPress(g_padID[key]);
}

bool Utility::GetKeyRelease(KeySet key)
{
	return Utility::GetKeyRelease(g_keyID[key]) || GetKeyRelease(g_padID[key]);
}

void Utility::SetKeyBind(KeySet key, ControllerID id)
{
	// 15～18行目を参考に作成。１行で完成します。

	g_keyID[key]	=	id;
	
}
//--- ここまで実装 ---//










bool Utility::GetKeyTrigger(ControllerID id)
{
#ifdef _USE_KEYBOARD_
	if (id >= Key_A && id <= Key_END)
	{
		char Word = Utility::CheckWord(id);
		return IsKeyTrigger(Word);
	}
#endif // _USE_KEYBOARD_
	/*if (id == RT || id == LT)
	{
		int InputNum_LT = g_keyState.Gamepad.bLeftTrigger;
		int InputNum_RT = g_keyState.Gamepad.bRightTrigger;
		if (InputNum_LT >= INPUT_RT_LT || InputNum_RT >= INPUT_RT_LT)
		{
			bool now = g_keyState.Gamepad.bLeftTrigger;
			bool now = g_keyState.Gamepad.bRightTrigger;
			bool old = g_keyStateOld.Gamepad.bLeftTrigger;
			bool old = g_keyStateOld.Gamepad.bRightTrigger;
			if (now && !old)
			{
				return true;
			}
		}
	}*/

    bool now = g_keyState.Gamepad.wButtons & id;
    bool old = g_keyStateOld.Gamepad.wButtons & id;
    return now && !old;
}
// キーボード処理部分は #ifdef _USE_KEYBOARD_ でラッピングしてください。
// VK_SPACEなども使えるようにしてください。
// おそらくチェックワードと列挙にそれぞれVK_〇〇とKey_〇〇を追加すればいけます。
bool Utility::GetKeyPress(ControllerID id)
{
#ifdef _USE_KEYBOARD_
	if (id >= Key_A && id <= Key_END)
	{
		char Word = Utility::CheckWord(id);
		return IsKeyPress(Word);
	}
#endif // _USE_KEYBOARD_
	if (id == Pad_RT || id == Pad_LT)
	{
		int InputNum_LT = g_keyState.Gamepad.bLeftTrigger;
		int InputNum_RT = g_keyState.Gamepad.bRightTrigger;
		if (InputNum_LT >= INPUT_RT_LT || InputNum_RT >= INPUT_RT_LT)
		{
			return true;
		}
	}
	return g_keyState.Gamepad.wButtons & id;
}

bool Utility::GetKeyRelease(ControllerID id)
{
#ifdef _USE_KEYBOARD_
	if (id >= Key_A && id <= Key_END)
	{
		char Word = Utility::CheckWord(id);
		return IsKeyRelease(Word);
	}
#endif // _USE_KEYBOARD_
    bool now = g_keyState.Gamepad.wButtons & id;
    bool old = g_keyStateOld.Gamepad.wButtons & id;
    return old && !now;
}

DirectX::XMFLOAT3 Utility::GetStickLeft()
{
    const float NULL_LEVEL = 0.1f;
    DirectX::XMFLOAT3 stick = {};
    stick.x = g_keyState.Gamepad.sThumbLX / (float)0x7fff;
    stick.y = g_keyState.Gamepad.sThumbLY / (float)0x7fff;
    stick.z = 0;
    if (fabsf(stick.x) < NULL_LEVEL)
        stick.x = 0;
    if (fabsf(stick.y) < NULL_LEVEL)
        stick.y = 0;
    return stick;
}

DirectX::XMFLOAT3 Utility::GetStickRight()
{
    const float NULL_LEVEL = 0.1f;
    DirectX::XMFLOAT3 stick = {};
    stick.x = g_keyState.Gamepad.sThumbRX / (float)0x7fff;
    stick.y = g_keyState.Gamepad.sThumbRY / (float)0x7fff;
    stick.z = 0;
    if (fabsf(stick.x) < NULL_LEVEL)
        stick.x = 0;
    if (fabsf(stick.y) < NULL_LEVEL)
        stick.y = 0;
    return stick;
}

float Utility::GetCameraSpeedX()
{
	return g_cameraSpeedX;
}

float Utility::GetCameraSpeedY()
{
    return g_cameraSpeedY;
}

void Utility::SetCameraSpeedX(float speedX)
{
	g_cameraSpeedX = speedX;
}

void Utility::SetCameraSpeedY(float speedY)
{
	g_cameraSpeedY = speedY;
}


char Utility::CheckWord(unsigned id)
{
	char Keyboard[256] = {
        'A','B', 'C', 'D','E','F', 'G', 'H','I','J', 'K', 'L','M','N', 'O', 'P',
		'Q','R', 'S', 'T','U','V','W', 'X', 'Y','Z','1','2', '3', '4', '5', '6', '7', '8', '9', '0',
        VK_UP, VK_RIGHT, VK_DOWN, VK_LEFT ,VK_BACK ,VK_TAB ,VK_CLEAR ,VK_RETURN ,VK_SHIFT, VK_CONTROL,
		VK_ESCAPE, VK_SPACE, 
    };
	return Keyboard[id - Key_A];
}
