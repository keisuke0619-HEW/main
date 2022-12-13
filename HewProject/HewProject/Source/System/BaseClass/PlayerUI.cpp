#include "PlayerUI.hpp"

CPlayerUI::CPlayerUI()
{
	// ここでUIのスプライトを生成
	auto tmp = AddList(new CGameUI("Assets/Img/white.png"));
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
	// すべてのスプライトを更新
	for (auto itr = m_spriteList.begin(); itr != m_spriteList.end(); itr++)
	{
		(*itr)->Draw();
	}
}

CGameUI::Ptr CPlayerUI::AddList(CGameUI* gameUI)
{
	CGameUI::Ptr shareP;
	shareP.reset(gameUI);
	m_spriteList.push_back(shareP);
	return shareP;
}
