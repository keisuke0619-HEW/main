#include "GameUI.h"

CGameUI::CGameUI(const char* FileName)
	: m_pos(0.f, 0.f)
	, m_size(1.f, 1.f)
	, m_sort(SORT_ORDER_DEFAULT)
	, m_rot(0.0f)
	, m_uvPos({0,0})
	, m_uvScale({1,1})
	, m_color({1,1,1,1})
{
	LoadTextureFromFile(FileName, &m_pPicture);
}

CGameUI::~CGameUI()
{
	m_pPicture->Release();
}

void CGameUI::Draw()
{
	// "D�\���̂��߂̍s���ݒ�
	// 1.�r���[�s��̓J�������֌W�Ȃ��̂ŁA����������Ă���s����g��(�P�ʍs��)
	DirectX::XMFLOAT4X4 fView;
	DirectX::XMStoreFloat4x4(&fView, DirectX::XMMatrixIdentity());
	// 2.�v���W�F�N�V�����s�񂪏d�v
	// ���̍s���2D�̃X�N���[���̑傫�������߂�
	DirectX::XMFLOAT4X4 fProj;
	DirectX::XMStoreFloat4x4(&fProj,
		DirectX::XMMatrixTranspose(
			DirectX::XMMatrixOrthographicOffCenterLH(
				0.f,	// ��ʍ��[�̍��W
				1280.f,	// ��ʉE�[�̍��W
				720.f,	// ��ʉ��[�̍��W
				0.f,	// ��ʏ�[�̍��W
				-1.f,	// Z�����Ŏʂ���ŏ��l
				1.f)));	// Z�����Ŏʂ���ő�l

	// ���[���h�s��ŉ�ʂ̕\���ʒu���v�Z
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, 0.f);
	DirectX::XMMATRIX R = DirectX::XMMatrixRotationZ(m_rot);
	DirectX::XMFLOAT4X4 fWorld;
	DirectX::XMStoreFloat4x4(&fWorld, DirectX::XMMatrixTranspose(R * T));

	// �X�v���C�g�̐ݒ�
	Sprite::SetWorld(fWorld);
	Sprite::SetView(fView);
	Sprite::SetProjection(fProj);
	auto tmpSize = m_size;
	tmpSize.y *= -1;
	Sprite::SetSize(tmpSize);
	Sprite::SetTexture(m_pPicture);
	Sprite::SetUVPos(m_uvPos);
	Sprite::SetUVScale(m_uvScale);
	Sprite::SetColor(m_color);
	EnableDepth(false);
	Sprite::Draw();
	EnableDepth(true);
	Sprite::SetUVPos({0,0});
	Sprite::SetUVScale({1,1});
	Sprite::SetColor({ 1,1,1,1 });
}

void CGameUI::SetPos(DirectX::XMFLOAT2 pos)
{
	m_pos = pos;
}

void CGameUI::SetSize(DirectX::XMFLOAT2 size)
{
	m_size = size;
}

void CGameUI::SetUVPos(DirectX::XMFLOAT2 uv)
{
	m_uvPos = uv;
}

void CGameUI::SetUVScale(DirectX::XMFLOAT2 uv)
{
	m_uvScale = uv;
}

void CGameUI::SetRotation(float degRot)
{
	m_rot = DirectX::XMConvertToRadians(degRot);
}

void CGameUI::SetColor(float r, float g, float b, float a)
{
	m_color = { r,g,b,a };
}

DirectX::XMFLOAT2 CGameUI::GetSize()
{
	return m_size;
}

int CGameUI::GetSortID()
{
	return m_sort;
}

void CGameUI::SetSortID(SortOrder order)
{
	m_sort = order;
}
