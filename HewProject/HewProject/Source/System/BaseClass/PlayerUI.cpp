#include "PlayerUI.hpp"
#include <Blend.hpp>
CPlayerUI::CPlayerUI()
{
	// ここでUIのスプライトを生成
	auto tmp = AddList(new CGameUI("Assets/Img/crosshair.png"));
	tmp->SetPos({ 640, 360 });
	tmp->SetSize({ 340, -340 });

	// 体力ゲージ
	auto tmphp = AddList(new CGameUI("Assets/Img/HP.png"));
	tmphp->SetPos({ 320,660 });
	tmphp->SetSize({ 640, -40 });

	// チャージゲージ
	auto tmpchg = AddList(new CGameUI("Assets/Img/Charge2.png"));
	tmpchg->SetPos({ 213, 700 });
	tmpchg->SetSize({ 427, -40 });
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
