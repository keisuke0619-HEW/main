#include "PlayerCamera.hpp"
#include <Input.h>
#include <SceneBase.hpp>
#define IF_MIN(v, x) v = (v) < (x) ? (x) : (v)
#define IF_MAX(v, x) v = (v) > (x) ? (x) : (v)
#define SET_VAR_RANGE(var, min, max) IF_MIN(var, min); IF_MAX(var, max)

CPlayerCamera::CPlayerCamera()
	:CCameraBase()
{
	m_target = CSceneBase::GetObjList().lock()->FindTag(TAG_PLAYER);
}

CPlayerCamera::~CPlayerCamera()
{
}

void CPlayerCamera::Update()
{
	const float MOVE_SPEED = 1.5f * 3.14f / 180;
	const float LOOK_OFFSET_X = 0.5f;
	const float LOOK_OFFSET_Y = 1.5f;
	if(IsKeyPress(VK_UP))	m_radY += MOVE_SPEED;
	if(IsKeyPress(VK_DOWN))	m_radY -= MOVE_SPEED;
	if(IsKeyPress(VK_RIGHT))m_radXZ += MOVE_SPEED;
	if(IsKeyPress(VK_LEFT))	m_radXZ -= MOVE_SPEED;

	SET_VAR_RANGE(m_radY, -3.1415f / 2, 3.1415f / 2);

	if (m_target.expired() == false)
	{
		m_data.look = m_target.lock()->GetParam().pos;
		m_data.look.y += LOOK_OFFSET_Y;
		m_data.look.x += sinf(m_radXZ - 3.14f / 2) * LOOK_OFFSET_X;
		m_data.look.z += cosf(m_radXZ - 3.14f / 2) * LOOK_OFFSET_X;
	}

	m_data.pos.x = cosf(m_radY) * sinf(m_radXZ) * m_distance + m_data.look.x;
	m_data.pos.y = sinf(m_radY) * m_distance + m_data.look.y;
	m_data.pos.z = cosf(m_radY) * cosf(m_radXZ) * m_distance + m_data.look.z;


}
