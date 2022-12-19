#include "PlayerUI.hpp"
#include <Blend.hpp>
// �ǉ�
#include <UiManager.hpp>

// �萔��`
const DirectX::XMFLOAT2 PLAYER_UI_LIFE_CENTER = { 267, 621 };
const DirectX::XMFLOAT2 PLAYER_UI_LIFE_SIZE = { 188, 57 };
const DirectX::XMFLOAT2 PLAYER_UI_CHARGE_CENTER = { 240, 700 };
const DirectX::XMFLOAT2 PLAYER_UI_CHARGE_SIZE =	{ 480, 40 };

CPlayerUI::CPlayerUI()
{
	// �ϐ�������
	m_LifeUV = 1;
	m_ChargeUV = 1;

	// ������UI�̃X�v���C�g�𐶐�
	auto tmp = new CGameUI("Assets/Img/Reticle/UI�@Reticle3.png");
	tmp->SetPos({ 640, 360 });
	tmp->SetSize({ 340, 340 });
	CUIManager::GetIns()->Add(tmp);

	// HP
	auto tmphp = new CGameUI("Assets/Img/HPbar/UI bar_02_hittosiro.png");
	tmphp->SetPos(PLAYER_UI_LIFE_CENTER);
	tmphp->SetSize(PLAYER_UI_LIFE_SIZE);
	m_lifeSprite = CUIManager::GetIns()->Add(tmphp);

	// HP�o�[
	auto bar = new CGameUI("Assets/Img/HPbar/UI hitpoint�@.png");
	bar->SetPos({ 234, 630 });
	bar->SetSize({ 448, 168 });
	CUIManager::GetIns()->Add(bar);

	// HP�o�[
	auto haguruma = new CGameUI("Assets/Img/HPbar/UI bar_02_haguruma2.png");
	haguruma->SetPos({ 94, 630 });
	haguruma->SetSize({ 68, 68 });
	CUIManager::GetIns()->Add(haguruma);

	// �`���[�W�Q�[�W
	auto tmpchg = new CGameUI("Assets/Img/Charge2.png");
	tmpchg->SetPos(PLAYER_UI_CHARGE_CENTER);
	tmpchg->SetSize(PLAYER_UI_CHARGE_SIZE);
	m_chargeSprite = CUIManager::GetIns()->Add(tmpchg);
}

CPlayerUI::~CPlayerUI()
{
	// ���X�g�̍폜�͕s�v�ł��B
}

void CPlayerUI::Update()
{
	// ������UI�̃X�v���C�g���X�V
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

// ���C�t�Q�[�W�̍X�V
void CPlayerUI::UpdateLife()
{
	// ���S���W���i�[
	auto center = PLAYER_UI_LIFE_CENTER;
	// ���S���W���v�Z
	center.x -= PLAYER_UI_LIFE_SIZE.x * 0.5f * (1 - m_LifeUV);
	// �X�v���C�g�̉������i�[
	auto size = PLAYER_UI_LIFE_SIZE;
	// �������v�Z
	size.x *= m_LifeUV;
	// �v�Z�������S���W��o�^
	m_lifeSprite.lock()->SetPos(center);
	// UV�̃T�C�Y��ݒ�B
	m_lifeSprite.lock()->SetUVScale({ m_LifeUV, 1 });
	// �v�Z����������o�^�B
	m_lifeSprite.lock()->SetSize(size);
}

// �`���[�W�Q�[�W�̍X�V
void CPlayerUI::UpdateCharge()
{
	// ���S���W���i�[
	auto center = PLAYER_UI_CHARGE_CENTER;
	// ���S���W���v�Z
	center.x -= PLAYER_UI_CHARGE_SIZE.x * 0.5f * (1 - m_ChargeUV);
	// �X�v���C�g�̉������i�[
	auto size = PLAYER_UI_CHARGE_SIZE;
	// �������v�Z
	size.x *= m_ChargeUV;
	// �v�Z�������S���W��o�^
	m_chargeSprite.lock()->SetPos(center);
	// UV�̃T�C�Y��ݒ�B
	m_chargeSprite.lock()->SetUVScale({ m_ChargeUV, 1 });
	// �v�Z����������o�^�B
	m_chargeSprite.lock()->SetSize(size);
}
