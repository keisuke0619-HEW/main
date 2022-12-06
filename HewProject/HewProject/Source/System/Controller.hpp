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

	// 押された瞬間
	bool GetKeyTrigger(unsigned id);
	// 押されている間
	bool GetKeyPress(unsigned id);
	// 離された瞬間
	bool GetKeyRelease(unsigned id);
	// 左スティック
	DirectX::XMFLOAT3 GetStickLeft();
	// 右スティック
	DirectX::XMFLOAT3 GetStickRight();

}