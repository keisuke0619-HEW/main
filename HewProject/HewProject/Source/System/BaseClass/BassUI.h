#pragma once

#include <list>
#include <GameUI.h>
class CBassUI
{
public:
	CBassUI();
	~CBassUI();

	void Update();
	void SetLife(float);
private:
	float m_LifeUV;
};