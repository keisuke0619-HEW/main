#include "PlayerUI.hpp"
#include <Blend.hpp>
CPlayerUI::CPlayerUI()
{
	// ������UI�̃X�v���C�g�𐶐�
	auto tmp = AddList(new CGameUI("Assets/Img/crosshear.png"));
	tmp->SetPos({ 640, 360 });
	tmp->SetSize({ 64, -64 });




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
	Utility::SetBlendState(BLEND_ADD);
	// ���ׂẴX�v���C�g���X�V
	for (auto itr = m_spriteList.begin(); itr != m_spriteList.end(); itr++)
	{
		(*itr)->Draw();
	}
	Utility::SetBlendState(BLEND_ALPHA);
}

CGameUI::Ptr CPlayerUI::AddList(CGameUI* gameUI)
{
	CGameUI::Ptr shareP;
	shareP.reset(gameUI);
	m_spriteList.push_back(shareP);
	return shareP;
}
