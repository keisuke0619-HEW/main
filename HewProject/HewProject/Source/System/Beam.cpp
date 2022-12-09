#include "Beam.hpp"
#include <Geometory.h>
#include <DebugWindow.hpp>
CBeam::CBeam(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 target, float size)
{
	m_pos = pos;
	m_target = target;
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
	// 発射起点がm_posに、ターゲット座標がm_targetに入っています。
	// それらの変数から軸の回転を求めてrotにぶち込んでください。
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
