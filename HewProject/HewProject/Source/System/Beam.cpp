#include "Beam.hpp"
#include <Geometory.h>
#include <DebugWindow.hpp>
CBeam::CBeam(DirectX::XMFLOAT3 pos, DirectX::XMVECTOR direction, float size)
{
	m_pos = pos;
	m_direction = direction;
	m_size = size;
}

CBeam::~CBeam()
{
}

void CBeam::Update()
{
}

void CBeam::Draw()
{
	// m_directionに向きの単位ベクトルが格納されています。
	// そのベクトルからXYZ軸それぞれの角度を求めて変数rotに格納してください
	DirectX::XMFLOAT3 rot = {};


	SetGeometoryTranslate(m_pos.x, m_pos.y, m_pos.z);
	SetGeometoryRotation(rot.x, rot.y, rot.z);
	SetGeometoryScaling(m_size, 10000, m_size);



	DrawCapsule();
}

bool CBeam::GetIsDestroy()
{
	return m_time <= 0.0f;
}
