#include "ProducePlane.h"
#include <MeshBuffer.h>
#include <Camera.hpp>

ProducePlane::ProducePlane(const char* FileName)
	:m_pos(0.0f, 0.0f, 0.0f)
	,m_size(1.0f, 1.0f, 0.0f)
	,m_rot(0.0f, 0.0f, 0.0f)
	,m_IsDarw(true)
{
	LoadTextureFromFile(FileName, &m_pPicture);
	//m_pConstantWVP = new ConstantBuffer;
	//m_pConstantWVP->Create(sizeof(m_PlaneMat));

	//// �萔�o�b�t�@�쐬
	//m_pConstant = new ConstantBuffer();
	//m_pConstant->Create(sizeof(UVPos));

	//PlaneVertex vtx[] = {
	//{ {-0.5f, 0.5f, 0.0f}, { 0.0f, 0.0f} },
	//{ { 0.5f, 0.5f, 0.0f}, { 1.0f, 0.0f} },
	//{ {-0.5f,-0.5f, 0.0f}, { 0.0f, 1.0f} },
	//{ { 0.5f,-0.5f, 0.0f}, { 1.0f, 1.0f} }
	//};
	//int idx[] =
	//{
	//	0,1,2, 1,3,2
	//};

	//MeshBuffer::Description desc;
	//desc.pVtx = vtx;
	//desc.vtxCount = 4;
	//desc.vtxSize = sizeof(PlaneVertex);
	//desc.pIdx = idx;
	//desc.idxCount = 6;
	//desc.idxSize = sizeof(int);
	//desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	//m_pProducePlane = new MeshBuffer(desc);
}

ProducePlane::~ProducePlane()
{
	m_pPicture->Release();
}

void ProducePlane::Draw()
{
	if (m_IsDarw == true)
	{
		// �r���[�s��Z�b�g
		Sprite::SetView(m_view);
		// �v���W�F�N�V�����s��Z�b�g
		Sprite::SetProjection(m_proj);

		// ���[���h�s��
		DirectX::XMFLOAT4X4 world;

		DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
		DirectX::XMMATRIX Rx = DirectX::XMMatrixRotationX(m_rot.x);
		DirectX::XMMATRIX Ry = DirectX::XMMatrixRotationY(m_rot.y);
		DirectX::XMMATRIX Rz = DirectX::XMMatrixRotationZ(m_rot.z);
		DirectX::XMMATRIX S = DirectX::XMMatrixScaling(m_size.x, m_size.y, 0.0f);
		DirectX::XMMATRIX mat = S * Rx * Ry * Rz * T;
		mat = DirectX::XMMatrixTranspose(mat);
		DirectX::XMStoreFloat4x4(&world, mat);
		
		// ���[���h�s��Z�b�g
		Sprite::SetWorld(world);
		// �e�N�X�`���Z�b�g
		Sprite::SetTexture(m_pPicture);
		// �T�C�Y
		//Sprite::SetSize(m_size);	// ���ꂢ��H�@�������

		// �`��
		Sprite::Draw();
	}
	/*DirectX::XMStoreFloat4x4(&m_PlaneMat[0], DirectX::XMMatrixIdentity());
	m_PlaneMat[1] = CCameraBase::GetPrimaryViewMatrix();
	m_PlaneMat[2] = CCameraBase::GetPrimaryProjectionMatrix();
	m_pConstantWVP->Write(m_PlaneMat);*/
}

void ProducePlane::SetRect(DirectX::XMFLOAT3 pos1, DirectX::XMFLOAT3 pos2,
	DirectX::XMFLOAT3 pos3, DirectX::XMFLOAT3 pos4)
{
	
}

void ProducePlane::SetProducePlaneInformation(DirectX::XMFLOAT3 center, DirectX::XMFLOAT3 size, DirectX::XMFLOAT3 rot)
{
	// �摜�̒��S�̍��W��ݒ�
	m_pos.x = center.x;
	m_pos.y = center.y;
	m_pos.z = center.z;

	// �摜�̃T�C�Y��ݒ�
	m_size.x = size.x * 10;
	m_size.y = size.y * 10;

	// �摜�̊p�x��ݒ�
	m_rot.x = rot.x;
	m_rot.y = rot.y;
	m_rot.z = rot.z;

	//PlaneVertex vtx[] = {

	//};

	////	���S�_�Ȃǂ��w�肵�ĕ`��
	//m_pPlane->centerpos = center;
	//m_pPlane->size = size;
	//m_pPlane->rot = rot;



	//->Draw();
}

void ProducePlane::SetEnable(bool isDraw)
{
	m_IsDarw = isDraw;
}

void ProducePlane::SetPosViewProj(DirectX::XMFLOAT4X4 view, DirectX::XMFLOAT4X4 proj)
{
	m_view = view;
	m_proj = proj;
}