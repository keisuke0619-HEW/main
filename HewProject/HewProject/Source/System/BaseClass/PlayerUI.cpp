#include "PlayerUI.hpp"
#include <Blend.hpp>
// 追加
#include <UiManager.hpp>

// 定数定義
const DirectX::XMFLOAT2 PLAYER_UI_LIFE_CENTER = { 307, 621 };
const DirectX::XMFLOAT2 PLAYER_UI_LIFE_SIZE = { 269, 57 };
const DirectX::XMFLOAT2 PLAYER_UI_CHARGE_CENTER = { 309, 662 };
const DirectX::XMFLOAT2 PLAYER_UI_CHARGE_SIZE =	{ 269, 10 };

CPlayerUI::CPlayerUI()
{
	// 変数初期化
	m_LifeUV = 1;
	m_ChargeUV = 1;

	// 定義したメンバ変数に変更。
	m_reticle = new CGameUI("Assets/Img/Reticle/UI　Reticle4.png");
	m_reticle->SetPos({ 640, 360 });
	m_reticle->SetSize({ 32,32 });
	CUIManager::GetIns()->Add(m_reticle);
	//// メンバの色を変更
	m_reticle->SetColor(1, 0, 0, 1);

	// HP
	m_hp = new CGameUI("Assets/Img/HPbar/HP.png");
	m_hp->SetPos(PLAYER_UI_LIFE_CENTER);
	m_hp->SetSize(PLAYER_UI_LIFE_SIZE);
	m_lifeSprite = CUIManager::GetIns()->Add(m_hp);
	m_hp->SetColor(0, 1, 0, 1);

	// HPバー外枠
	m_hpbar = new CGameUI("Assets/Img/HPbar/UI hitpoint①.png");
	m_hpbar->SetPos({ 234, 630 });
	m_hpbar->SetSize({ 448, 168 });
	CUIManager::GetIns()->Add(m_hpbar);
	m_hpbar->SetColor(0, 1, 1, 1);

	// 歯車
	m_haguruma = new CGameUI("Assets/Img/HPbar/UI bar_02_haguruma2.png");
	m_haguruma->SetPos({ 94, 630 });
	m_haguruma->SetSize({ 68, 68 });
	CUIManager::GetIns()->Add(m_haguruma);
	m_haguruma->SetColor(0, 1, 1, 1);

	// チャージゲージ
	m_charge = new CGameUI("Assets/Img/Charge2.png");
	m_charge->SetPos(PLAYER_UI_CHARGE_CENTER);
	m_charge->SetSize(PLAYER_UI_CHARGE_SIZE);
	m_chargeSprite = CUIManager::GetIns()->Add(m_charge);
	m_charge->SetColor(0, 1, 1, 1);
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

	// 回転
	static int hagurumaAngle = 0;
	m_haguruma->SetRotation(hagurumaAngle);
	hagurumaAngle += 1;
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
