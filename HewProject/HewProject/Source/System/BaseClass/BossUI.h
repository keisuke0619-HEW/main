#pragma once

#include <list>
#include <GameUI.h>
class CBossUI
{
public:
	CBossUI();
	~CBossUI();

	void Update();
	void SetLife(float);
private:
	float m_LifeUV;
	CGameUI::Ref m_lifeSprite;

	CGameUI::Ref m_bossbar;
	CGameUI::Ref m_bossicon;

	void UpdateLife();
};