#include "ProducePlane.h"
#include <MeshBuffer.h>
#include <Camera.hpp>

ProducePlane::ProducePlane()
{
	m_pConstantWVP = new ConstantBuffer;
	m_pConstantWVP->Create(sizeof(m_PlaneMat));

	// 定数バッファ作成
	m_pConstant = new ConstantBuffer();
	m_pConstant->Create(sizeof(UVPos));

	PlaneVertex vtx[] = {
	{ {-0.5f, 0.5f, 0.0f}, { 0.0f, 0.0f} },
	{ { 0.5f, 0.5f, 0.0f}, { 1.0f, 0.0f} },
	{ {-0.5f,-0.5f, 0.0f}, { 0.0f, 1.0f} },
	{ { 0.5f,-0.5f, 0.0f}, { 1.0f, 1.0f} }
	};
	int idx[] =
	{
		0,1,2, 1,3,2
	};

	MeshBuffer::Description desc;
	desc.pVtx = vtx;
	desc.vtxCount = 4;
	desc.vtxSize = sizeof(PlaneVertex);
	desc.pIdx = idx;
	desc.idxCount = 6;
	desc.idxSize = sizeof(int);
	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	m_pProducePlane = new MeshBuffer(desc);
}

ProducePlane::~ProducePlane()
{
}

void ProducePlane::Draw()
{
	DirectX::XMStoreFloat4x4(&m_PlaneMat[0], DirectX::XMMatrixIdentity());
	m_PlaneMat[1] = CCameraBase::GetPrimaryViewMatrix();
	m_PlaneMat[2] = CCameraBase::GetPrimaryProjectionMatrix();
	m_pConstantWVP->Write(m_PlaneMat);
}

void ProducePlane::SetRect(DirectX::XMFLOAT3 pos1, DirectX::XMFLOAT3 pos2,
	DirectX::XMFLOAT3 pos3, DirectX::XMFLOAT3 pos4)
{
	
}

void ProducePlane::SetCenterPos(DirectX::XMFLOAT3 center, DirectX::XMFLOAT2 size, DirectX::XMFLOAT3 rot)
{
	PlaneVertex vtx[] = {

	};

	//	中心点などを指定して描画
	m_pPlane->centerpos = center;
	m_pPlane->size = size;
	m_pPlane->rot = rot;



	//->Draw();
}

void ProducePlane::SetEnable(bool isDraw)
{
	m_IsDarw = isDraw;
}
