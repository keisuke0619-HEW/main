#include  "Billboard.h"

CBillboard::CBillboard(const char* FileName)
	: m_pos(0.f, 0.f, 0.f)
	, m_playerPos(0.f, 0.f, 0.f)
	, m_size(1.f, 1.f)
	, m_distance(4.f)
	, m_rot(0.f)
{
	LoadTextureFromFile(FileName, &m_pPicture);

}

CBillboard::~CBillboard()
{
	m_pPicture->Release();
}


void CBillboard::Draw(bool BillOnOff, bool enable)
{
	// �r���[�s��Z�b�g
	Sprite::SetView(m_view);
	// �v���W�F�N�V�����s��Z�b�g
	Sprite::SetProjection(m_proj);

	// ���[���h�s��
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
	DirectX::XMFLOAT4X4 world;
	// �r���{�[�h�I��
	if (BillOnOff)
	{
		DirectX::XMFLOAT4X4 inv; // �t�s��̊i�[��
		inv = m_view;
		// �]�u����Ă���s��Ȃ̂ŁA��x���ɖ߂�
		DirectX::XMMATRIX matInv = DirectX::XMLoadFloat4x4(&inv);
		matInv = DirectX::XMMatrixTranspose(matInv);
		// �ړ������͑ł������K�v���Ȃ��̂�0��ݒ肵�Ĉړ��𖳎�����
		DirectX::XMStoreFloat4x4(&inv, matInv);
		inv._41 = inv._42 = inv._43 = 0.f;
		// �t�s��̌v�Z��XMMATRIX�^�ōs��
		matInv = DirectX::XMLoadFloat4x4(&inv);
		matInv = DirectX::XMMatrixInverse(nullptr, matInv);
		DirectX::XMStoreFloat4x4(&world, DirectX::XMMatrixTranspose(matInv * T));
	}
	// �r���{�[�h�I�t
	else
	{
		DirectX::XMMATRIX R = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(m_rot));
		DirectX::XMStoreFloat4x4(&world, DirectX::XMMatrixTranspose(R * T));
	}

	// ���[���h�s��Z�b�g
	Sprite::SetWorld(world);
	// �e�N�X�`���Z�b�g
	Sprite::SetTexture(m_pPicture);
	// �T�C�Y
	Sprite::SetSize(m_size);
	




	if (!enable)
	{
		// �v���C���[�Ɖ摜�̈ʒu���
		DirectX::XMVECTOR enemy = DirectX::XMLoadFloat3(&m_pos);
		DirectX::XMVECTOR player = DirectX::XMLoadFloat3(&m_playerPos);

		// �������v�Z
		DirectX::XMVECTOR distance = DirectX::XMVectorSubtract(player, enemy);

		// float3�ɕϊ����Ċi�[
		DirectX::XMFLOAT3 movePos;
		DirectX::XMStoreFloat3(&movePos, distance);
		// �摜����O�ɕ\������鋗��
		float disPlayer = m_distance;
		// �v���C���[�Ɖ摜����ȏ㗣��Ă��邩�m�F
		if (fabsf(movePos.x) <= disPlayer && fabsf(movePos.y) <= disPlayer && fabsf(movePos.z) <= disPlayer)
		{
			// ���ȏ�߂��ɂ�����摜����O�ɕ\������
			EnableDepth(enable);
		}
	}


	Sprite::Draw();
	EnableDepth(true);

}

void CBillboard::SetPosViewProj(DirectX::XMFLOAT4X4 view, DirectX::XMFLOAT4X4 proj)
{
	m_view = view;
	m_proj = proj;
}

void CBillboard::SetPos(DirectX::XMFLOAT3 pos)
{
	m_pos = pos;
}

void CBillboard::SetPlayerrPos(DirectX::XMFLOAT3 playerPos, float distance)
{
	m_playerPos = playerPos;
	m_distance = distance;
}

void CBillboard::SetSize(DirectX::XMFLOAT2 size)
{
	m_size = size;
}

void CBillboard::SetRotation(float rot)
{
	m_rot = rot;
}