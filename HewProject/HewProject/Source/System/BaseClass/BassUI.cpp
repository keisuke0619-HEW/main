#include "BassUI.h"
#include <Blend.hpp>
// �ǉ�
#include <UiManager.hpp>
CBassUI::CBassUI()
{
	auto Basshp = new CGameUI("Assets/Img/BassHP.png");
	Basshp->SetPos({ 520, 20 });
	Basshp->SetSize({ 1040, 40 });
	CUIManager::GetIns()->Add(Basshp);
}

CBassUI::~CBassUI()
{
	// ���X�g�̍폜�͕s�v�ł��B
}

void CBassUI::Update()
{
	// ������UI�̃X�v���C�g���X�V
}


void CBassUI::SetLife(float)
{

}

void CBassUI::SetCharge(float)
{

}