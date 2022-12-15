#include "BassUI.h"
#include <Blend.hpp>

CBassUI::CBassUI()
{
	// ここでUIのスプライトを生成
	// 体力ゲージ
	auto Basshp = AddList(new CGameUI("Assets/Img/BassHP.png"));
	Basshp->SetPos({ 520, 20 });
	Basshp->SetSize({ 1040, -40 });
}

CBassUI::~CBassUI()
{
	// リストの削除は不要です。
}

void CBassUI::Update()
{
	// ここでUIのスプライトを更新
}

void CBassUI::Draw()
{
	// すべてのスプライトを更新
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
