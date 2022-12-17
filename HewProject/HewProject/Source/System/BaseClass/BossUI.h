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

	void UpdateLife();
};