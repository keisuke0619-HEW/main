#include "Controller.hpp"
namespace Utility
{
    XINPUT_STATE g_keyState;
    XINPUT_STATE g_keyStateOld;
    
    int g_cameraSpeed;
	ControllerID g_keyID[KeySet::KEY_SET_MAX];
}


void Utility::ControllerInit()
{
    g_cameraSpeed = 10;
	g_keyID[KeySet::BEAM] = ControllerID::RT;
	g_keyID[KeySet::JUMP] = ControllerID::A;
	g_keyID[KeySet::SELECT] = ControllerID::A;
	g_keyID[KeySet::CANCEL] = ControllerID::B;
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
	return GetKeyTrigger(g_keyID[key]);
	
}

bool Utility::GetKeyPress(KeySet key)
{
	return Utility::GetKeyPress(g_keyID[key]);
}

bool Utility::GetKeyRelease(KeySet key)
{
	return Utility::GetKeyRelease(g_keyID[key]);
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
	if (id == RT || id == LT)
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

int Utility::GetCameraSpeed()
{
    return g_cameraSpeed;
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
