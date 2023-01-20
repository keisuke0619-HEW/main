#include "PlayerCamera.hpp"
#include <Input.h>
#include <SceneBase.hpp>
#include <Controller.hpp>

#define IF_MIN(v, x) v = (v) < (x) ? (x) : (v)
#define IF_MAX(v, x) v = (v) > (x) ? (x) : (v)
#define SET_VAR_RANGE(var, min, max) IF_MIN(var, min); IF_MAX(var, max)

float CPlayerCamera::m_blurX;
float CPlayerCamera::m_blurY;
bool CPlayerCamera::m_Isblur;
int CPlayerCamera::m_frame;

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
	const float MOVE_SPEED = 0.15f * 3.14f / 180;
	const float LOOK_OFFSET_X = 0.5f;
	const float LOOK_OFFSET_Y = 1.5f;
	if(Utility::GetKeyPress(KEY_CAMERA_UP))	m_radY += MOVE_SPEED  * Utility::GetCameraSpeedY();
	if(Utility::GetKeyPress(KEY_CAMERA_DOWN))	m_radY -= MOVE_SPEED  * Utility::GetCameraSpeedY();
	if(Utility::GetKeyPress(KEY_CAMERA_RIGHT))m_radXZ += MOVE_SPEED * Utility::GetCameraSpeedX();
	if(Utility::GetKeyPress(KEY_CAMERA_LEFT))	m_radXZ -= MOVE_SPEED * Utility::GetCameraSpeedX();
	m_radY -= Utility::GetStickRight().y * MOVE_SPEED * Utility::GetCameraSpeedY();
	m_radXZ += Utility::GetStickRight().x * MOVE_SPEED * Utility::GetCameraSpeedX();

	SET_VAR_RANGE(m_radY, -3.1415f / 2, 3.1415f / 2);

	if (m_target.expired() == false)
	{
		m_data.look = m_target.lock()->GetParam().pos;
		m_data.look.y += LOOK_OFFSET_Y;
		m_data.look.x += sinf(m_radXZ - 3.14f / 2) * LOOK_OFFSET_X;
		m_data.look.z += cosf(m_radXZ - 3.14f / 2) * LOOK_OFFSET_X;
	}

	if (m_Isblur)
	{
		m_blurX = sinf((float)m_frame / 3.0f) * 5.1;
		m_blurY = sinf((float)m_frame / 3.0f) * 5.1;
		
		if (m_frame >= m_totalframe)
		{
			m_blurX = 0.0f;
			m_blurY = 0.0f;
			m_Isblur = false;
		}
		m_frame++;
	}

	m_data.pos.x = cosf(m_radY) * sinf(m_radXZ) * m_distance + m_data.look.x;
	m_data.pos.y = sinf(m_radY) * m_distance + m_data.look.y;
	m_data.pos.z = cosf(m_radY) * cosf(m_radXZ) * m_distance + m_data.look.z;

	m_data.pos.x += m_blurX;
	m_data.pos.y += m_blurY;
}

void CPlayerCamera::SetBlur()
{
	m_Isblur = true;
	m_blurX = 0;
	m_blurY = 0;
	m_frame = 0;
}
