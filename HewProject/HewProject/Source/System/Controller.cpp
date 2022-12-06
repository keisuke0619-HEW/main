#include "Controller.hpp"

// �R���g���[���ƃL�[�{�[�h�ǂ���������悤�ɂ��Ă����Ă��������B
namespace Utility
{
	int g_PadID = -1;
	XINPUT_STATE g_keyState;
	XINPUT_STATE g_keyStateOld;
}


// �R���g���[���[���g�p���邽�߂ɕK�v�����Ȃ��Ƃ������ɏ����B
// ���t���[���̃A�b�v�f�[�g�̑O�ɌĂ΂��
void Utility::ControllerUpdate()
{
	//�Q�[���p�b�h�̏�Ԃ��擾
	XINPUT_STATE state;
	XInputGetState(0, &state);

	g_keyStateOld = g_keyState;
	XInputGetState(0, &g_keyState);

	DWORD dwResult = XInputGetState(0, &state);
	if (dwResult == ERROR_SUCCESS)
	{
		// Controller is connected
		// �ڑ�����Ă���
	}
	else
	{
		// Controller is not connected
		// �ڑ�����Ă��Ȃ�
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
// �����ꂽ�u�Ԃ���True
bool Utility::GetKeyTrigger(unsigned id)
{
	bool now = g_keyState.Gamepad.wButtons & id;
	bool old = g_keyStateOld.Gamepad.wButtons & id;
	return now && !old;
	return false;
}
// �����Ă����True
bool Utility::GetKeyPress(unsigned id)
{
	return g_keyState.Gamepad.wButtons & id;
	/*if (g_PadID == id)
	{
		return true;
	}
	return false;*/
}
// �����ꂽ�u�Ԃ���True
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
