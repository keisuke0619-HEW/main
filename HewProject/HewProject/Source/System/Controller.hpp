#pragma once

namespace Controller
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
	bool GetKeyTrigger(ControllerID);
	// ������Ă����
	bool GetKeyPress(ControllerID);
	// �����ꂽ�u��
	bool GetKeyRelease(ControllerID);
}