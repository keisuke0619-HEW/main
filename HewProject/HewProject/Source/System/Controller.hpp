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

	// âüÇ≥ÇÍÇΩèuä‘
	bool GetKeyTrigger(ControllerID);
	// âüÇ≥ÇÍÇƒÇ¢ÇÈä‘
	bool GetKeyPress(ControllerID);
	// ó£Ç≥ÇÍÇΩèuä‘
	bool GetKeyRelease(ControllerID);
}