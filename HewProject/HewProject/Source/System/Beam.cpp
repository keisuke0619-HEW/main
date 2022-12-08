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
	// m_direction�Ɍ����̒P�ʃx�N�g�����i�[����Ă��܂��B
	// ���̃x�N�g������XYZ�����ꂼ��̊p�x�����߂ĕϐ�rot�Ɋi�[���Ă�������
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
