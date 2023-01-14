#include "CutinCamera.hpp"
#include <Easing.hpp>

CCutinCamera::CCutinCamera()
{
}

CCutinCamera::~CCutinCamera()
{
}

void CCutinCamera::Update()
{
	const float easingTime = 1.0f;	// •b
	const float easingAdd = 1 / easingTime / 60;
	auto easing = Utility::OutCubic(m_step);
	m_data.pos.x = (m_endPos.x - m_startPos.x) * easing + m_startPos.x;
	m_data.pos.y = (m_endPos.y - m_startPos.y) * easing + m_startPos.y;
	m_data.pos.z = (m_endPos.z - m_startPos.z) * easing + m_startPos.z;
	m_step += easingAdd;
}

void CCutinCamera::SetData(DirectX::XMFLOAT3 startpos, DirectX::XMFLOAT3 endpos, DirectX::XMFLOAT3 startrad, DirectX::XMFLOAT3 endrad)
{
	m_startPos = startpos;
	m_endPos = endpos;
	m_startRad = startrad;
	m_endRad = endrad;
	m_step = 0;
}
