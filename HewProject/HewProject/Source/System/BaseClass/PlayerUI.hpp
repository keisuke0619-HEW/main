#pragma once

#include <list>
#include <GameUI.h>
#include <MiniMap.h>
class CPlayerUI
{
public:
	CPlayerUI();
	~CPlayerUI();

	void Update();
	void SetLife(float);
	void SetCharge(float);
private:
	CMiniMap* m_map;
};