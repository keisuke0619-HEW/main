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
	std::weak_ptr<CGameUI> m_lifeSprite;

	void UpdateLife();
};