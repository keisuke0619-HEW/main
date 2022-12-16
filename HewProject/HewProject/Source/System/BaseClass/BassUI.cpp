#include "BassUI.h"
#include <Blend.hpp>
// 追加
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
	// リストの削除は不要です。
}

void CBassUI::Update()
{
	// ここでUIのスプライトを更新
}


void CBassUI::SetLife(float)
{

}

void CBassUI::SetCharge(float)
{

}