#pragma once

#include <list>
#include <GameUI.h>
#include <PlayerUI.hpp>

class CBassUI
{
public:
	CBassUI();
	~CBassUI();

	void Update();
	void Draw();
	void SetLife(float);
	void SetCharge(float);
private:
	std::list<CGameUI::Ptr> m_spriteList;
	CGameUI::Ptr AddList(CGameUI*);
};