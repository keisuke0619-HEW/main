#include "PlayerUI.hpp"
#include <Blend.hpp>
// 追加
#include <UiManager.hpp>

// 定数定義
const DirectX::XMFLOAT2 PLAYER_UI_LIFE_CENTER = { 267, 621 };
const DirectX::XMFLOAT2 PLAYER_UI_LIFE_SIZE = { 188, 57 };
const DirectX::XMFLOAT2 PLAYER_UI_CHARGE_CENTER = { 240, 700 };
const DirectX::XMFLOAT2 PLAYER_UI_CHARGE_SIZE =	{ 480, 40 };

CPlayerUI::CPlayerUI()
{
	// 変数初期化
	m_LifeUV = 1;
	m_ChargeUV = 1;

	// ここでUIのスプライトを生成
	auto tmp = new CGameUI("Assets/Img/Reticle/UI　Reticle3.png");
	tmp->SetPos({ 640, 360 });
	tmp->SetSize({ 340, 340 });
	CUIManager::GetIns()->Add(tmp);

	// HP
	auto tmphp = new CGameUI("Assets/Img/HPbar/UI bar_02_hittosiro.png");
	tmphp->SetPos(PLAYER_UI_LIFE_CENTER);
	tmphp->SetSize(PLAYER_UI_LIFE_SIZE);
	m_lifeSprite = CUIManager::GetIns()->Add(tmphp);

	// HPバー
	auto bar = new CGameUI("Assets/Img/HPbar/UI hitpoint①.png");
	bar->SetPos({ 234, 630 });
	bar->SetSize({ 448, 168 });
	CUIManager::GetIns()->Add(bar);

	// HPバー
	auto haguruma = new CGameUI("Assets/Img/HPbar/UI bar_02_haguruma2.png");
	haguruma->SetPos({ 94, 630 });
	haguruma->SetSize({ 68, 68 });
	CUIManager::GetIns()->Add(haguruma);

	// チャージゲージ
	auto tmpchg = new CGameUI("Assets/Img/Charge2.png");
	tmpchg->SetPos(PLAYER_UI_CHARGE_CENTER);
	tmpchg->SetSize(PLAYER_UI_CHARGE_SIZE);
	m_chargeSprite = CUIManager::GetIns()->Add(tmpchg);
}

CPlayerUI::~CPlayerUI()
{
	// リストの削除は不要です。
}

void CPlayerUI::Update()
{
	// ここでUIのスプライトを更新
	UpdateLife();
	UpdateCharge();
}


void CPlayerUI::SetLife(float Life)
{
	m_LifeUV = Life > 1.0f ? 1.0f : Life < 0.0f ? 0.0f : Life;
}

void CPlayerUI::SetCharge(float Charge)
{
	m_ChargeUV = Charge > 1.0f ? 1.0f : Charge < 0.0f ? 0.0f : Charge;
}

// ライフゲージの更新
void CPlayerUI::UpdateLife()
{
	// 中心座標を格納
	auto center = PLAYER_UI_LIFE_CENTER;
	// 中心座標を計算
	center.x -= PLAYER_UI_LIFE_SIZE.x * 0.5f * (1 - m_LifeUV);
	// スプライトの横幅を格納
	auto size = PLAYER_UI_LIFE_SIZE;
	// 横幅を計算
	size.x *= m_LifeUV;
	// 計算した中心座標を登録
	m_lifeSprite.lock()->SetPos(center);
	// UVのサイズを設定。
	m_lifeSprite.lock()->SetUVScale({ m_LifeUV, 1 });
	// 計算した横幅を登録。
	m_lifeSprite.lock()->SetSize(size);
}

// チャージゲージの更新
void CPlayerUI::UpdateCharge()
{
	// 中心座標を格納
	auto center = PLAYER_UI_CHARGE_CENTER;
	// 中心座標を計算
	center.x -= PLAYER_UI_CHARGE_SIZE.x * 0.5f * (1 - m_ChargeUV);
	// スプライトの横幅を格納
	auto size = PLAYER_UI_CHARGE_SIZE;
	// 横幅を計算
	size.x *= m_ChargeUV;
	// 計算した中心座標を登録
	m_chargeSprite.lock()->SetPos(center);
	// UVのサイズを設定。
	m_chargeSprite.lock()->SetUVScale({ m_ChargeUV, 1 });
	// 計算した横幅を登録。
	m_chargeSprite.lock()->SetSize(size);
}
