#include "CutinCamera.hpp"
#include <Easing.hpp>

float CCutinCamera::m_blurZ;
float CCutinCamera::m_blurY;
bool CCutinCamera::m_Isblur;
int CCutinCamera::m_frame;

CCutinCamera::CCutinCamera()
{
}

CCutinCamera::~CCutinCamera()
{
}

void CCutinCamera::Update()
{
	const float easingTime = 1.0f;	// 秒
	const float easingAdd = 1 / easingTime / 60;
	auto easing = Utility::OutCubic(m_step);

	if (m_Isblur)
	{
		m_blurZ = rand() % 10 /10.0f - 0.5f;
		m_blurY = rand() % 10 /10.0f - 0.5f;

		if (m_frame >= m_totalframe)
		{
			m_blurZ = 0.0f;
			m_blurY = 0.0f;
			m_Isblur = false;
		}
		m_frame++;
	}

	m_data.pos.x = (m_endPos.x - m_startPos.x) * easing + m_startPos.x;
	m_data.pos.y = (m_endPos.y - m_startPos.y) * easing + m_startPos.y;
	m_data.pos.z = (m_endPos.z - m_startPos.z) * easing + m_startPos.z;
	m_step += easingAdd;
	//m_data.look = { m_startPos.x, m_startPos.y - 10, m_startPos.z };

	m_data.pos.z += m_blurZ;
	m_data.pos.y += m_blurY;
}

void CCutinCamera::SetData(DirectX::XMFLOAT3 startpos, DirectX::XMFLOAT3 look, float rot)
{
	m_startPos = startpos;
	m_endPos = startpos;
	//m_startRad = startrad;
	m_data.look = look;
	//m_endRad = endrad;
	m_rad = rot;
	// 右斜め
	//m_endPos.x = m_endPos.x + (cosf(m_rad) * 10);
	//m_endPos.y = m_endPos.y;
	//m_endPos.z = m_endPos.z + (-sinf(m_rad) * 10);
	// 右斜め後ろ
	m_endPos.x = m_endPos.x + (cosf(m_rad) * 10) + (-sinf(m_rad) * 10);
	m_endPos.y = m_endPos.y + 13;
	m_endPos.z = m_endPos.z + (-sinf(m_rad) * 10) + (-cosf(m_rad) * 10);
	// 右斜め後ろ
	// rad = 0		: m_endPos.x + 10, z - 10
	// rad = 1.57	: m_endPos.x - 10, z - 10
	// rad = 3.14	: m_endPos.x - 10, z + 10
	// rad = 5.71	: m_endPos.x + 10, z + 10
	// 右斜め
	// m_endRad.y = 0の時m_endPos.x + 10, z + 0
	// m_endRad.y = 1.57の時m_endPos.x + 0, z - 10
	// m_endRad.y = 3.14の時m_endPos.x - 10, z + 0
	// m_endRad.y = 4.71の時m_endPos.x + 0, z + 10
	//m_endPos.z -= 10;
	//float sin = sinf(4.71f); // z
	//float cos = cosf(3.14f); // x
	//float cos = cosf(m_endRad.y);
	//float sin = sinf(m_endRad.y);
	m_step = 0;
}

void CCutinCamera::SetCutinBlur()
{
	m_Isblur = true;
	m_blurZ = 0;
	m_blurY = 0;
	m_frame = 0;
}
