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
	m_bosshp = new CGameUI("Assets/Img/Boss/UI bar_boss1.png");
	m_bosshp->SetPos(BASS_UI_LIFE_CENTER);
	m_bosshp->SetSize(BASS_UI_LIFE_SIZE);
	m_lifeSprite = CUIManager::GetIns()->Add(m_bosshp);
	m_bosshp->SetColor(1, 0, 0, 1);

	// バー
	m_bossbar = new CGameUI("Assets/Img/Boss/UI bar_boss2.png");
	m_bossbar->SetPos({ 360, 80 });
	m_bossbar->SetSize({ 705, 27 });// 960, 20
	CUIManager::GetIns()->Add(m_bossbar);
	m_bossbar->SetColor(1, 1, 1, 1);

	// ボスアイコン
	m_bossicon = new CGameUI("Assets/Img/Boss/UI bar_boss3.png");
	m_bossicon->SetPos({ 340, 60 });
	m_bossicon->SetSize({ 660, 110 });
	CUIManager::GetIns()->Add(m_bossicon);
	m_bossicon->SetColor(1, 1, 1, 1);
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
