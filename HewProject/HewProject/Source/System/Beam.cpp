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
	// ���ˋN�_��m_pos�ɁA�^�[�Q�b�g���W��m_target�ɓ����Ă��܂��B
	// �����̕ϐ����玲�̉�]�����߂�rot�ɂԂ�����ł��������B
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
