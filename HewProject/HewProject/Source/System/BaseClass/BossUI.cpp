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
	auto Basshp = new CGameUI("Assets/Img/Boss/UI bar_boss1.png");
	Basshp->SetPos(BASS_UI_LIFE_CENTER);
	Basshp->SetSize(BASS_UI_LIFE_SIZE);
	m_lifeSprite = CUIManager::GetIns()->Add(Basshp);

	// �o�[
	auto Bossbar2 = new CGameUI("Assets/Img/Boss/UI bar_boss2.png");
	Bossbar2->SetPos({ 360, 80 });
	Bossbar2->SetSize({ 705, 27 });// 960, 20
	CUIManager::GetIns()->Add(Bossbar2);

	// �{�X�A�C�R��
	auto Bossbar3 = new CGameUI("Assets/Img/Boss/UI bar_boss3.png");
	Bossbar3->SetPos({ 340, 60 });
	Bossbar3->SetSize({ 660, 110 });
	CUIManager::GetIns()->Add(Bossbar3);
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
