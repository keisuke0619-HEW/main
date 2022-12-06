#pragma once
#pragma comment(lib, "Xinput.lib")
#include <Windows.h>
#include <DirectXMath.h>
#include <Xinput.h>

namespace Utility
{
	enum ControllerID
	{
		A = XINPUT_GAMEPAD_A,
		B = XINPUT_GAMEPAD_B,
		X = XINPUT_GAMEPAD_X,
		Y = XINPUT_GAMEPAD_Y,
		UP = XINPUT_GAMEPAD_DPAD_UP,
		RIGHT = XINPUT_GAMEPAD_DPAD_RIGHT,
		DOWN = XINPUT_GAMEPAD_DPAD_DOWN,
		LEFT = XINPUT_GAMEPAD_DPAD_LEFT,
		RB = XINPUT_GAMEPAD_RIGHT_SHOULDER,
		RSTICK = XINPUT_GAMEPAD_RIGHT_THUMB,
		LB = XINPUT_GAMEPAD_LEFT_SHOULDER, 
		LSTICK = XINPUT_GAMEPAD_LEFT_THUMB,
		START = XINPUT_GAMEPAD_START,
		BACK = XINPUT_GAMEPAD_BACK,
	};

	void ControllerUpdate();

	// �����ꂽ�u��
	bool GetKeyTrigger(unsigned id);
	// ������Ă����
	bool GetKeyPress(unsigned id);
	// �����ꂽ�u��
	bool GetKeyRelease(unsigned id);
	// ���X�e�B�b�N
	DirectX::XMFLOAT3 GetStickLeft();
	// �E�X�e�B�b�N
	DirectX::XMFLOAT3 GetStickRight();

}