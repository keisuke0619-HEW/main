#include "BossUI.h"
#include <Blend.hpp>
// �ǉ�
#include <UiManager.hpp>

// �萔��`
const DirectX::XMFLOAT2 BASS_UI_LIFE_CENTER = { 360, 80 };
const DirectX::XMFLOAT2 BASS_UI_LIFE_SIZE = { 683, 19 };// 945, 18

CBossUI::CBossUI()
{
	// �ϐ�������
	m_LifeUV = 1;

	// ��HP�o�[�ƃA�C�R���̍���20�����傤�ǂ������ȁH
	// ���C�t�Q�[�W
	m_lifeSprite = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/Boss/UI bar_boss1.png"));
	m_lifeSprite.lock()->SetPos(BASS_UI_LIFE_CENTER);
	m_lifeSprite.lock()->SetSize(BASS_UI_LIFE_SIZE);
	m_lifeSprite.lock()->SetColor(1, 0, 0, 1);

	// �o�[
	m_bossbar = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/Boss/UI bar_boss2.png"));
	m_bossbar.lock()->SetPos({ 360, 80 });
	m_bossbar.lock()->SetSize({ 705, 27 });// 960, 20
	m_bossbar.lock()->SetColor(1, 1, 1, 1);

	// �{�X�A�C�R��
	m_bossicon = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/Boss/UI bar_boss3.png"));
	m_bossicon.lock()->SetPos({ 340, 60 });
	m_bossicon.lock()->SetSize({ 660, 110 });
	m_bossicon.lock()->SetColor(1, 1, 1, 1);
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
