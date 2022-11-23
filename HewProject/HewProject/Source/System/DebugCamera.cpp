#include "DebugCamera.hpp"
#include <Input.h>

#define IF_KEY(i) if(IsKeyPress(i))
#define IF_MIN(v, x) v = (v) < (x) ? (x) : (v)
#define IF_MAX(v, x) v = (v) > (x) ? (x) : (v)
#define SET_VAR_RANGE(var, min, max) IF_MIN(var, min); IF_MAX(var, max)
CDebugCamera::CDebugCamera()
	:CCameraBase()
{
}

CDebugCamera::~CDebugCamera()
{
}

void CDebugCamera::Update()
{
	const float MOVE_SPEED = 1.5f * 3.14f / 180;
	IF_KEY('W')	m_radY -= MOVE_SPEED;
	IF_KEY('S')	m_radY += MOVE_SPEED;
	IF_KEY('D')	m_radXZ -= MOVE_SPEED;
	IF_KEY('A')	m_radXZ += MOVE_SPEED;

	IF_KEY(VK_UP)		m_data.look.y += MOVE_SPEED;
	IF_KEY(VK_DOWN)		m_data.look.y -= MOVE_SPEED;
	IF_KEY(VK_RIGHT)	m_data.look.x += MOVE_SPEED;
	IF_KEY(VK_LEFT)		m_data.look.x -= MOVE_SPEED;
	IF_KEY(VK_SHIFT)	m_data.look.z += MOVE_SPEED;
	IF_KEY(VK_CONTROL)	m_data.look.z -= MOVE_SPEED;

	IF_KEY('Q') m_distance -= MOVE_SPEED;
	IF_KEY('E') m_distance += MOVE_SPEED;

	SET_VAR_RANGE(m_distance, 1.0f, 10.0f);
	SET_VAR_RANGE(m_radY, -3.1415f / 2, 3.1415f / 2);

	m_data.pos.x = cosf(m_radY) * sinf(m_radXZ) * m_distance + m_data.look.x;
	m_data.pos.y = sinf(m_radY)                 * m_distance + m_data.look.y;
	m_data.pos.z = cosf(m_radY) * cosf(m_radXZ) * m_distance + m_data.look.z;



}