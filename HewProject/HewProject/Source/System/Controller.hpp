#pragma once
#pragma comment(lib, "Xinput.lib")
#include <Windows.h>
#include <DirectXMath.h>
#include <Xinput.h>
#include "Input.h"

#define _USE_KEYBOARD_
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

		Key_A = 4097,
		Key_B,
		Key_C,
		Key_D,
		Key_E,
		Key_F,
		Key_G,
		Key_H,
		Key_I,
		Key_J,
		Key_K,
		Key_L,
		Key_M,
		Key_N,
		Key_O,
		Key_P,
		Key_Q,
		Key_R,
		Key_S,
		Key_T,
		Key_U,
		Key_V,
		Key_W,
		Key_X,
		Key_Y,
		Key_Z,
		Key_1,
		Key_2,
		Key_3,
		Key_4,
		Key_5,
		Key_6,
		Key_7,
		Key_8,
		Key_9,
		Key_0,
		Key_Up,
		Key_Right,
		Key_Down,
		Key_Left,
		Key_BACK,
		Key_TAB,
		Key_CLEAR,
		Key_RETURN,
		Key_SHIFT,
		Key_Ctrl,
		Key_ESCAPE,
		Key_SPACE,



		Key_END,
	};


	void ControllerInit();

	void ControllerUpdate();

	// 押された瞬間
	bool GetKeyTrigger(ControllerID id);
	// 押されている間
	bool GetKeyPress(ControllerID id);
	// 離された瞬間
	bool GetKeyRelease(ControllerID id);
	// 左スティック
	DirectX::XMFLOAT3 GetStickLeft();
	// 右スティック
	DirectX::XMFLOAT3 GetStickRight();

	int GetCameraSpeed();

	// 入力したキーの判定
	char CheckWord(unsigned id);
}