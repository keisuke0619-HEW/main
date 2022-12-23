#include "PlayerUI.hpp"
#include <Blend.hpp>
// �ǉ�
#include <UiManager.hpp>

// �萔��`
const DirectX::XMFLOAT2 PLAYER_UI_LIFE_CENTER = { 307, 621 };
const DirectX::XMFLOAT2 PLAYER_UI_LIFE_SIZE = { 269, 57 };
const DirectX::XMFLOAT2 PLAYER_UI_CHARGE_CENTER = { 309, 662 };
const DirectX::XMFLOAT2 PLAYER_UI_CHARGE_SIZE =	{ 269, 10 };

CPlayerUI::CPlayerUI()
{
	// �ϐ�������
	m_LifeUV = 1;
	m_ChargeUV = 1;

	// ��`���������o�ϐ��ɕύX�B
	m_reticle = new CGameUI("Assets/Img/Reticle/UI�@Reticle4.png");
	m_reticle->SetPos({ 640, 360 });
	m_reticle->SetSize({ 32,32 });
	CUIManager::GetIns()->Add(m_reticle);
	//// �����o�̐F��ύX
	m_reticle->SetColor(1, 0, 0, 1);

	// HP
	m_hp = new CGameUI("Assets/Img/HPbar/HP.png");
	m_hp->SetPos(PLAYER_UI_LIFE_CENTER);
	m_hp->SetSize(PLAYER_UI_LIFE_SIZE);
	m_lifeSprite = CUIManager::GetIns()->Add(m_hp);
	m_hp->SetColor(0, 1, 0, 1);

	// HP�o�[�O�g
	m_hpbar = new CGameUI("Assets/Img/HPbar/UI hitpoint�@.png");
	m_hpbar->SetPos({ 234, 630 });
	m_hpbar->SetSize({ 448, 168 });
	CUIManager::GetIns()->Add(m_hpbar);
	m_hpbar->SetColor(0, 1, 1, 1);

	// ����
	m_haguruma = new CGameUI("Assets/Img/HPbar/UI bar_02_haguruma2.png");
	m_haguruma->SetPos({ 94, 630 });
	m_haguruma->SetSize({ 68, 68 });
	CUIManager::GetIns()->Add(m_haguruma);
	m_haguruma->SetColor(0, 1, 1, 1);

	// �`���[�W�Q�[�W
	m_charge = new CGameUI("Assets/Img/Charge2.png");
	m_charge->SetPos(PLAYER_UI_CHARGE_CENTER);
	m_charge->SetSize(PLAYER_UI_CHARGE_SIZE);
	m_chargeSprite = CUIManager::GetIns()->Add(m_charge);
	m_charge->SetColor(0, 1, 1, 1);
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

	// ��]
	static int hagurumaAngle = 0;
	m_haguruma->SetRotation(hagurumaAngle);
	hagurumaAngle += 1;
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
