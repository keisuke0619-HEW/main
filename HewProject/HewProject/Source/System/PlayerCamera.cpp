#include "PlayerCamera.hpp"
#include <Input.h>

#define IF_MIN(v, x) v = (v) < (x) ? (x) : (v)
#define IF_MAX(v, x) v = (v) > (x) ? (x) : (v)
#define SET_VAR_RANGE(var, min, max) IF_MIN(var, min); IF_MAX(var, max)

CPlayerCamera::CPlayerCamera(std::shared_ptr<CPlayer> player)
	:CCameraBase()
{
	m_target = player;
}

CPlayerCamera::~CPlayerCamera()
{
}

void CPlayerCamera::Update()
{
	const float MOVE_SPEED = 1.5f * 3.14f / 180;
	if(IsKeyPress(VK_UP))	m_radY += MOVE_SPEED;
	if(IsKeyPress(VK_DOWN))	m_radY -= MOVE_SPEED;
	if(IsKeyPress(VK_RIGHT))	m_radXZ += MOVE_SPEED;
	if(IsKeyPress(VK_LEFT))	m_radXZ -= MOVE_SPEED;

	SET_VAR_RANGE(m_radY, -3.1415f / 2, 3.1415f / 2);

	m_pos.x = cosf(m_radY) * sinf(m_radXZ) * m_distance + m_look.x;
	m_pos.y = sinf(m_radY) * m_distance + m_look.y;
	m_pos.z = cosf(m_radY) * cosf(m_radXZ) * m_distance + m_look.z;

	m_look = m_target->GetPos();
	m_look.y += 1.5f;

}
