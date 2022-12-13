#include "PlayerUI.hpp"
#include <Blend.hpp>
CPlayerUI::CPlayerUI()
{
	// ここでUIのスプライトを生成
	auto tmp = AddList(new CGameUI("Assets/Img/crosshear.png"));
	tmp->SetPos({ 640, 360 });
	tmp->SetSize({ 64, -64 });




}

CPlayerUI::~CPlayerUI()
{
	// リストの削除は不要です。
}

void CPlayerUI::Update()
{
	// ここでUIのスプライトを更新
}

void CPlayerUI::Draw()
{
	Utility::SetBlendState(BLEND_ADD);
	// すべてのスプライトを更新
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
