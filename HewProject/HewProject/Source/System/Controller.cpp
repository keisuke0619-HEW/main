#include "Controller.hpp"
namespace Utility
{
    XINPUT_STATE g_keyState;
    XINPUT_STATE g_keyStateOld;

	/*ControllerID g_controllerID;
	KeyboardID	 g_keyboardID;*/
}
void Utility::ControllerUpdate()
{
    g_keyStateOld = g_keyState;
    XInputGetState(0, &g_keyState);
}

bool Utility::GetKeyTrigger(unsigned id)
{
    bool now = g_keyState.Gamepad.wButtons & id;
    bool old = g_keyStateOld.Gamepad.wButtons & id;
    return now && !old;
}

bool Utility::GetKeyPress(unsigned id)
{
	if (id >= Key_A && id <= Key_END)
	{
		char Word = Utility::CheckWord(id);
		return IsKeyPress(Word);
	}
	else
	return g_keyState.Gamepad.wButtons & id;
}

bool Utility::GetKeyRelease(unsigned id)
{
    bool now = g_keyState.Gamepad.wButtons & id;
    bool old = g_keyStateOld.Gamepad.wButtons & id;
    return old && !now;
}
DirectX::XMFLOAT3 Utility::GetStickLeft()
{
    DirectX::XMFLOAT3 stick = {};
    stick.x = g_keyState.Gamepad.sThumbLX / (float)0x7fff;
    stick.y = g_keyState.Gamepad.sThumbLY / (float)0x7fff;
    char str[128];
    stick.z = 0;
    return stick;
}

DirectX::XMFLOAT3 Utility::GetStickRight()
{
    DirectX::XMFLOAT3 stick = {};
    stick.x = g_keyState.Gamepad.sThumbRX / (float)0x7fff;
    stick.y = g_keyState.Gamepad.sThumbRY / (float)0x7fff;
    stick.z = 0;
    return stick;
}

char Utility::CheckWord(unsigned id)
{
	char Keyboard[256] = {'A','B', 'C', 'D','E','F', 'G', 'H','I','J', 'K', 'L','M','N', 'O', 'P',
		'Q','R', 'S', 'T','U','V','W', 'X', 'Y','Z','1','2', '3', '4', '5', '6', '7', '8', '9', '0', };
	return Keyboard[id - Key_A];
}
