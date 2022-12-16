#pragma once

#include <list>
#include <GameUI.h>
class CPlayerUI
{
public:
	CPlayerUI();
	~CPlayerUI();

	void Update();
	void SetLife(float);
	void SetCharge(float);
};