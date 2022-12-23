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
	m_reticle = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/Reticle/UI　Reticle4.png"));
	m_reticle.lock()->SetPos({ 640, 360 });
	m_reticle.lock()->SetSize({ 32,32 });
	m_reticle.lock()->SetColor(1, 0, 0, 1);

	// HP
	m_lifeSprite = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/HPbar/HP.png"));;
	m_lifeSprite.lock()->SetPos(PLAYER_UI_LIFE_CENTER);
	m_lifeSprite.lock()->SetSize(PLAYER_UI_LIFE_SIZE);
	m_lifeSprite.lock()->SetColor(0.376f, 0.698f, 0.753f, 0.8f);

	// HPバー外枠
	m_hpbar = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/HPbar/UI hitpoint①.png"));
	m_hpbar.lock()->SetPos({ 234, 630 });
	m_hpbar.lock()->SetSize({ 448, 168 });
	m_hpbar.lock()->SetColor(0.376f, 0.698f, 0.753f, 0.8f);

	// 歯車
	m_haguruma = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/HPbar/UI bar_02_haguruma2.png"));
	m_haguruma.lock()->SetPos({ 94, 630 });
	m_haguruma.lock()->SetSize({ 68, 68 });
	m_haguruma.lock()->SetColor(0.376f, 0.698f, 0.753f, 0.8f);

	// チャージゲージ
	m_chargeSprite = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/Charge2.png"));
	m_chargeSprite.lock()->SetPos(PLAYER_UI_CHARGE_CENTER);
	m_chargeSprite.lock()->SetSize(PLAYER_UI_CHARGE_SIZE);
	m_chargeSprite.lock()->SetColor(0, 1, 1, 1);
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
	m_haguruma.lock()->SetRotation(hagurumaAngle);
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
