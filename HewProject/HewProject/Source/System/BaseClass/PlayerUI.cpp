#include "PlayerUI.hpp"
#include <Blend.hpp>
// 追加
#include <UiManager.hpp>

// 定数定義
const DirectX::XMFLOAT2 PLAYER_UI_CHARGE_CENTER = { 240, 700 };
const DirectX::XMFLOAT2 PLAYER_UI_CHARGE_SIZE =	{ 480, 40 };

CPlayerUI::CPlayerUI()
{
	// 変数初期化
	m_ChargeUV = 1;

	// ここでUIのスプライトを生成

	auto tmp = new CGameUI("Assets/Img/crosshair.png");
	tmp->SetPos({ 640, 360 });
	tmp->SetSize({ 340, 340 });
	CUIManager::GetIns()->Add(tmp);

	// 体力ゲージ
	auto tmphp = new CGameUI("Assets/Img/HP.png");
	tmphp->SetPos({320, 660});
	tmphp->SetSize({640,40});
	CUIManager::GetIns()->Add(tmphp);

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
	m_LifeUV = Life;
}

void CPlayerUI::SetCharge(float Charge)
{
	m_ChargeUV = Charge > 1.0f ? 1.0f : Charge < 0.0f ? 0.0f : Charge;
}

// ライフゲージの更新
void CPlayerUI::UpdateLife()
{
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
