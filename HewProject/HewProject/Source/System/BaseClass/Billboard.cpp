#include  "Billboard.h"

CBillboard::CBillboard(const char* FileName)
{
	LoadTextureFromFile(FileName, &m_pPicture);

}

CBillboard::~CBillboard()
{
	m_pPicture->Release();
}


void CBillboard::Draw(DirectX::XMFLOAT4X4 view, DirectX::XMFLOAT4X4 proj, DirectX::XMFLOAT3 pos, DirectX::XMFLOAT2 size, bool BillOnOff, bool enable, float rot)
{
	// �r���[�s��Z�b�g
	Sprite::SetView(view);
	// �v���W�F�N�V�����s��Z�b�g
	Sprite::SetProjection(proj);

	// ���[���h�s��
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
	DirectX::XMFLOAT4X4 world;

	// �r���{�[�h�I��
	if (BillOnOff)
	{
		DirectX::XMFLOAT4X4 inv; // �t�s��̊i�[��
		inv = view;
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
		DirectX::XMMATRIX R = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(rot));
		DirectX::XMStoreFloat4x4(&world, DirectX::XMMatrixTranspose(R * T));
	}

	// ���[���h�s��Z�b�g
	Sprite::SetWorld(world);
	// �e�N�X�`���Z�b�g
	Sprite::SetTexture(m_pPicture);
	// �T�C�Y
	Sprite::SetSize(size);
	// �[�x�o�b�t�@
	EnableDepth(enable);
	Sprite::Draw();
	EnableDepth(true);

}