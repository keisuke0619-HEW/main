#include "Controller.hpp"
namespace Utility
{
    XINPUT_STATE g_keyState;
    XINPUT_STATE g_keyStateOld;
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