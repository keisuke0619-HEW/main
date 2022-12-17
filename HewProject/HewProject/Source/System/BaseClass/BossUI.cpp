#include "BossUI.h"
#include <Blend.hpp>
// �ǉ�
#include <UiManager.hpp>

// �萔��`
const DirectX::XMFLOAT2 BASS_UI_LIFE_CENTER = { 520, 20 };
const DirectX::XMFLOAT2 BASS_UI_LIFE_SIZE = { 1040, 40 };

CBossUI::CBossUI()
{
	// �ϐ�������
	m_LifeUV = 1;

	auto Basshp = new CGameUI("Assets/Img/BassHP.png");
	Basshp->SetPos(BASS_UI_LIFE_CENTER);
	Basshp->SetSize(BASS_UI_LIFE_SIZE);
	m_lifeSprite = CUIManager::GetIns()->Add(Basshp);
}

CBossUI::~CBossUI()
{
	// ���X�g�̍폜�͕s�v�ł��B
}

void CBossUI::Update()
{
	// ������UI�̃X�v���C�g���X�V
	UpdateLife();
}

void CBossUI::SetLife(float Life)
{
	m_LifeUV = Life > 1.0f ? 1.0f : Life < 0.0f ? 0.0f : Life;
}

// ���C�t�Q�[�W�̍X�V
void CBossUI::UpdateLife()
{
	// ���S���W���i�[
	auto center = BASS_UI_LIFE_CENTER;
	// ���S���W���v�Z
	center.x -= BASS_UI_LIFE_SIZE.x * 0.5f * (1 - m_LifeUV);
	// �X�v���C�g�̉������i�[
	auto size = BASS_UI_LIFE_SIZE;
	// �������v�Z
	size.x *= m_LifeUV;
	// �v�Z�������S���W��o�^
	m_lifeSprite.lock()->SetPos(center);
	// UV�̃T�C�Y��ݒ�B
	m_lifeSprite.lock()->SetUVScale({ m_LifeUV, 1 });
	// �v�Z����������o�^�B
	m_lifeSprite.lock()->SetSize(size);
	
}
