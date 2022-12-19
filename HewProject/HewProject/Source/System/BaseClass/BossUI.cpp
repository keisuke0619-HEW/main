#include "BossUI.h"
#include <Blend.hpp>
// 追加
#include <UiManager.hpp>

// 定数定義
const DirectX::XMFLOAT2 BASS_UI_LIFE_CENTER = { 360, 80 };
const DirectX::XMFLOAT2 BASS_UI_LIFE_SIZE = { 683, 19 };// 945, 18

CBossUI::CBossUI()
{
	// 変数初期化
	m_LifeUV = 1;

	// ↓HPバーとアイコンの差は20がちょうどいいかな？
	// ライフゲージ
	auto Basshp = new CGameUI("Assets/Img/Boss/UI bar_boss1.png");
	Basshp->SetPos(BASS_UI_LIFE_CENTER);
	Basshp->SetSize(BASS_UI_LIFE_SIZE);
	m_lifeSprite = CUIManager::GetIns()->Add(Basshp);

	// バー
	auto Bossbar2 = new CGameUI("Assets/Img/Boss/UI bar_boss2.png");
	Bossbar2->SetPos({ 360, 80 });
	Bossbar2->SetSize({ 705, 27 });// 960, 20
	CUIManager::GetIns()->Add(Bossbar2);

	// ボスアイコン
	auto Bossbar3 = new CGameUI("Assets/Img/Boss/UI bar_boss3.png");
	Bossbar3->SetPos({ 340, 60 });
	Bossbar3->SetSize({ 660, 110 });
	CUIManager::GetIns()->Add(Bossbar3);
}

CBossUI::~CBossUI()
{
	// リストの削除は不要です。
}

void CBossUI::Update()
{
	// ここでUIのスプライトを更新
	UpdateLife();
}

void CBossUI::SetLife(float Life)
{
	m_LifeUV = Life > 1.0f ? 1.0f : Life < 0.0f ? 0.0f : Life;
}

// ライフゲージの更新
void CBossUI::UpdateLife()
{
	// 中心座標を格納
	auto center = BASS_UI_LIFE_CENTER;
	// 中心座標を計算
	center.x -= BASS_UI_LIFE_SIZE.x * 0.5f * (1 - m_LifeUV);
	// スプライトの横幅を格納
	auto size = BASS_UI_LIFE_SIZE;
	// 横幅を計算
	size.x *= m_LifeUV;
	// 計算した中心座標を登録
	m_lifeSprite.lock()->SetPos(center);
	// UVのサイズを設定。
	m_lifeSprite.lock()->SetUVScale({ m_LifeUV, 1 });
	// 計算した横幅を登録。
	m_lifeSprite.lock()->SetSize(size);
	
}
