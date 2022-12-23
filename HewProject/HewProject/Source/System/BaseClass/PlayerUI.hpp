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
	CGameUI::Ref m_lifeSprite;
	CGameUI::Ref m_chargeSprite;

	CGameUI::Ref m_reticle;	// �X�v���C�g���i�[���郁���o�ϐ����`
	CGameUI::Ref m_hpbar;
	CGameUI::Ref m_haguruma;

	void UpdateLife();
	void UpdateCharge();

};