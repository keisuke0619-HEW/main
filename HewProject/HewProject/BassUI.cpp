#include "BassUI.h"
#include <Blend.hpp>

CBassUI::CBassUI()
{
	// ������UI�̃X�v���C�g�𐶐�
	// �̗̓Q�[�W
	auto Basshp = AddList(new CGameUI("Assets/Img/BassHP.png"));
	Basshp->SetPos({ 520, 20 });
	Basshp->SetSize({ 1040, -40 });
}

CBassUI::~CBassUI()
{
	// ���X�g�̍폜�͕s�v�ł��B
}

void CBassUI::Update()
{
	// ������UI�̃X�v���C�g���X�V
}

void CBassUI::Draw()
{
	// ���ׂẴX�v���C�g���X�V
	for (auto itr = m_spriteList.begin(); itr != m_spriteList.end(); itr++)
	{
		(*itr)->Draw();
	}
}

void CBassUI::SetLife(float)
{

}

void CBassUI::SetCharge(float)
{

}

CGameUI::Ptr CBassUI::AddList(CGameUI* gameUI)
{
	CGameUI::Ptr shareP;
	shareP.reset(gameUI);
	m_spriteList.push_back(shareP);
	return shareP;
}
