#pragma once
#pragma comment(lib, "Xinput.lib")
#include <Windows.h>
#include <DirectXMath.h>
#include <Xinput.h>

namespace Utility
{
	enum ControllerID
	{
		A,
		B,
		X,
		Y,
		UP,
		RIGHT,
		DOWN,
		LEFT,
		RB,
		RT,
		RSTICK,
		LB,
		LT,
		LSTICK,
		START,
		BACK,
	};

	void ControllerUpdate();

	// 押された瞬間
	bool GetKeyTrigger(unsigned id);
	// 押されている間
	bool GetKeyPress(unsigned id);
	// 離された瞬間
	bool GetKeyRelease(unsigned id);
	// 左スティック
	DirectX::XMFLOAT3 GetLeftStick();
	// 右スティック
	DirectX::XMFLOAT3 GetRightStick();

}