#include "PlayerUI.hpp"
#include <Blend.hpp>
// �ǉ�
#include <UiManager.hpp>
CPlayerUI::CPlayerUI()
{
	// ������UI�̃X�v���C�g�𐶐�
	//auto tmp = AddList(new CGameUI("Assets/Img/crosshair.png"));
	//tmp->SetPos({ 640, 360 });
	//tmp->SetSize({ 340, -340 });

	auto tmp = new CGameUI("Assets/Img/crosshair.png");
	tmp->SetPos({ 640, 360 });
	tmp->SetSize({ 340, 340 });
	CUIManager::GetIns()->Add(tmp);

	// �̗̓Q�[�W
	//auto tmphp = AddList(new CGameUI("Assets/Img/HP.png"));
	//tmphp->SetPos({ 320,660 });
	//tmphp->SetSize({ 640, 40 });

	auto tmphp = new CGameUI("Assets/Img/HP.png");
	tmphp->SetPos({ 320,660 });
	tmphp->SetSize({ 640, 40 });
	CUIManager::GetIns()->Add(tmphp);

	// �`���[�W�Q�[�W
	//auto tmpchg = AddList(new CGameUI("Assets/Img/Charge2.png"));
	//tmpchg->SetPos({ 213, 700 });
	//tmpchg->SetSize({ 427, 40 });

	auto tmpchg = new CGameUI("Assets/Img/Charge2.png");
	tmpchg->SetPos({ 213, 700 });
	tmpchg->SetSize({ 427, 40 });
	CUIManager::GetIns()->Add(tmpchg);
}

CPlayerUI::~CPlayerUI()
{
	// ���X�g�̍폜�͕s�v�ł��B
}

void CPlayerUI::Update()
{
	// ������UI�̃X�v���C�g���X�V
}


void CPlayerUI::SetLife(float Life)
{
	m_LifeUV = Life;
}

void CPlayerUI::SetCharge(float Charge)
{
	m_ChargeUV = Charge;
}