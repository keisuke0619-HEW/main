#pragma once

#include <list>
#include <GameUI.h>
class CPlayerUI
{
public:
	CPlayerUI();
	~CPlayerUI();

	void Update();
	void Draw();
private:
	std::list<CGameUI::Ptr> m_spriteList;
	CGameUI::Ptr AddList(CGameUI*);
};