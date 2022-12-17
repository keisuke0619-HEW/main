#include "BassUI.h"
#include <Blend.hpp>
// 追加
#include <UiManager.hpp>

// 定数定義
const DirectX::XMFLOAT2 BASS_UI_LIFE_CENTER = { 520, 20 };
const DirectX::XMFLOAT2 BASS_UI_LIFE_SIZE = { 1040, 40 };

CBassUI::CBassUI()
{
	// 変数初期化
	m_LifeUV = 1;

	auto Basshp = new CGameUI("Assets/Img/BassHP.png");
	Basshp->SetPos(BASS_UI_LIFE_CENTER);
	Basshp->SetSize(BASS_UI_LIFE_SIZE);
	m_lifeSprite = CUIManager::GetIns()->Add(Basshp);
}

CBassUI::~CBassUI()
{
	// リストの削除は不要です。
}

void CBassUI::Update()
{
	// ここでUIのスプライトを更新
	UpdateLife();
}

void CBassUI::SetLife(float Life)
{
	m_LifeUV = Life > 1.0f ? 1.0f : Life < 0.0f ? 0.0f : Life;
}

// ライフゲージの更新
void CBassUI::UpdateLife()
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
