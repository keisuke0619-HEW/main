#pragma once

#include <list>
#include <GameUI.h>
#include <memory>
#include <MiniMap.h>
#include <NumberUI.hpp>
class CPlayerUI
{
public:
	CPlayerUI();
	~CPlayerUI();

	void Update();
	void SetLife(float);
	void SetCharge(float);
	void SetReticleAlpha(int a);
private:
	float m_LifeUV;
	float m_ChargeUV;
	CGameUI::Ref m_lifeSprite;
	CGameUI::Ref m_chargeSprite;

	CGameUI::Ref m_reticle;	// スプライトを格納するメンバ変数を定義
	CGameUI::Ref m_hpbar;
	CGameUI::Ref m_haguruma;

	CMiniMap* m_pMap;
	void UpdateLife();
	void UpdateCharge();

};