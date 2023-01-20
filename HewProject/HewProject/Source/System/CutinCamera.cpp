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
	m_data.pos.x = (m_endPos.x - m_startPos.x) * sinf(m_endRad.y) * easing + m_startPos.x;
	m_data.pos.y = (m_endPos.y - m_startPos.y) * easing + m_startPos.y;
	m_data.pos.z = (m_endPos.z - m_startPos.z) * cosf(m_endRad.y) * easing + m_startPos.z;
	m_step += easingAdd;
	//m_data.look = { m_startPos.x, m_startPos.y - 10, m_startPos.z };
}

void CCutinCamera::SetData(DirectX::XMFLOAT3 startpos, DirectX::XMFLOAT3 endpos, DirectX::XMFLOAT3 startrad, DirectX::XMFLOAT3 endrad)
{
	m_startPos = startpos;
	m_endPos = endpos;
	//m_startRad = startrad;
	m_data.look = startrad;
	m_endRad = endrad;
	m_endPos.x = m_endPos.x * sinf(m_endRad.y) - m_data.look.x;
	m_endPos.y = m_endPos.y - m_data.look.y;
	m_endPos.z = m_endPos.z * cosf(m_endRad.y) - m_data.look.z;
	m_step = 0;
}
