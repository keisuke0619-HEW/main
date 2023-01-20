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
	//m_data.look = { m_startPos.x, m_startPos.y - 10, m_startPos.z };
}

void CCutinCamera::SetData(DirectX::XMFLOAT3 startpos, DirectX::XMFLOAT3 endpos, DirectX::XMFLOAT3 startrad, float rot)
{
	m_startPos = startpos;
	m_endPos = endpos;
	//m_startRad = startrad;
	m_data.look = startrad;
	//m_endRad = endrad;
	m_rad = rot;
	m_endPos.x = m_endPos.x + (cosf(m_rad) * 10);
	m_endPos.y = m_endPos.y;
	m_endPos.z = m_endPos.z + (-sinf(m_rad) * 10);
	// m_endRad.y = 0‚ÌŽžm_endPos.x + 10, z + 0
	// m_endRad.y = 1.57‚ÌŽžm_endPos.x + 0, z - 10
	// m_endRad.y = 3.14‚ÌŽžm_endPos.x - 10, z + 0
	// m_endRad.y = 4.71‚ÌŽžm_endPos.x + 0, z + 10
	//m_endPos.z -= 10;
	//float sin = sinf(4.71f); // z
	//float cos = cosf(3.14f); // x
	//float cos = cosf(m_endRad.y);
	//float sin = sinf(m_endRad.y);
	m_step = 0;
}
