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

	// �����ꂽ�u��
	bool GetKeyTrigger(unsigned id);
	// ������Ă����
	bool GetKeyPress(unsigned id);
	// �����ꂽ�u��
	bool GetKeyRelease(unsigned id);
	// ���X�e�B�b�N
	DirectX::XMFLOAT3 GetLeftStick();
	// �E�X�e�B�b�N
	DirectX::XMFLOAT3 GetRightStick();

}