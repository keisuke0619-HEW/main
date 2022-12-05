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

	// 押された瞬間
	bool GetKeyTrigger(ControllerID);
	// 押されている間
	bool GetKeyPress(ControllerID);
	// 離された瞬間
	bool GetKeyRelease(ControllerID);
}