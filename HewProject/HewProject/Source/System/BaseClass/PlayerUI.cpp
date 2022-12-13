#include "PlayerUI.hpp"
#include <Blend.hpp>
CPlayerUI::CPlayerUI()
{
	// ������UI�̃X�v���C�g�𐶐�
	auto tmp = AddList(new CGameUI("Assets/Img/crosshair.png"));
	tmp->SetPos({ 640, 360 });
	tmp->SetSize({ 340, -340 });

	// �̗̓Q�[�W
	auto tmphp = AddList(new CGameUI("Assets/Img/HP.png"));
	tmphp->SetPos({ 320,660 });
	tmphp->SetSize({ 640, -40 });

	// �`���[�W�Q�[�W
	auto tmpchg = AddList(new CGameUI("Assets/Img/Charge2.png"));
	tmpchg->SetPos({ 213, 700 });
	tmpchg->SetSize({ 427, -40 });
}

CPlayerUI::~CPlayerUI()
{
	// ���X�g�̍폜�͕s�v�ł��B
}

void CPlayerUI::Update()
{
	// ������UI�̃X�v���C�g���X�V
}

void CPlayerUI::Draw()
{
	// ���ׂẴX�v���C�g���X�V
	for (auto itr = m_spriteList.begin(); itr != m_spriteList.end(); itr++)
	{
		(*itr)->Draw();
	}
}

void CPlayerUI::SetLife(float)
{

}

void CPlayerUI::SetCharge(float)
{
	
}

CGameUI::Ptr CPlayerUI::AddList(CGameUI* gameUI)
{
	CGameUI::Ptr shareP;
	shareP.reset(gameUI);
	m_spriteList.push_back(shareP);
	return shareP;
}
