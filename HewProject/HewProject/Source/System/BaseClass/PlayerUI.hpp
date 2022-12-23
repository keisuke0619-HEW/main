#pragma once

#include <list>
#include <GameUI.h>
#include <memory>
class CPlayerUI
{
public:
	CPlayerUI();
	~CPlayerUI();

	void Update();
	void SetLife(float);
	void SetCharge(float);
private:
	float m_LifeUV;
	float m_ChargeUV;
	std::weak_ptr<CGameUI> m_lifeSprite;
	std::weak_ptr<CGameUI> m_chargeSprite;

	CGameUI* m_reticle;	// スプライトを格納するメンバ変数を定義
	CGameUI* m_hp;
	CGameUI* m_hpbar;
	CGameUI* m_haguruma;
	CGameUI* m_charge;

	void UpdateLife();
	void UpdateCharge();

};