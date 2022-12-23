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
	std::weak_ptr<CGameUI> m_lifeSprite;

	CGameUI* m_bosshp;
	CGameUI* m_bossbar;
	CGameUI* m_bossicon;

	void UpdateLife();
};