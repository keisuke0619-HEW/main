#include "Beam.hpp"
#include <Geometory.h>
#include <DebugWindow.hpp>
#include <Easing.hpp>
CBeam::CBeam(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 target, float size)
	: CObjectBase("Assets/Box.fbx")
{
	m_pos = pos;
	m_target = target;
	m_size = 0;

	m_maxSize = size;
	m_time = 2.0f;
}

CBeam::~CBeam()
{
}

void CBeam::Update()
{
	const int beamGrowFrame = 60 * 1;
	const int beamDeadFrame = 60 * 3;
	if (m_param.frame < beamGrowFrame)
	{
		m_size = m_maxSize * Utility::OutQuad((float)m_param.frame / beamGrowFrame);// += m_maxSize / beamGrowFrame;
	}
	if (m_param.frame >= beamDeadFrame)
	{
		Destroy();
	}
}

void CBeam::Draw()
{
	// 発射起点がm_posに、ターゲット座標がm_targetに入っています。
	// それらの変数から軸の回転を求めてrotにぶち込みました。

	DirectX::XMFLOAT3 rot = {};

	DirectX::XMVECTOR vPos = DirectX::XMLoadFloat3(&m_pos);
	DirectX::XMVECTOR vTarget = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&m_target), vPos));
	DirectX::XMVECTOR vToTarget = DirectX::XMVectorAdd(vTarget, DirectX::XMVectorZero());

	DirectX::XMFLOAT3 ToTarget;

	DirectX::XMStoreFloat3(&ToTarget, vToTarget);

	rot.x = atan2f(sqrtf(ToTarget.z * ToTarget.z + ToTarget.x * ToTarget.x), ToTarget.y);
	rot.y = atan2f(ToTarget.x, ToTarget.z);
	rot.z = 0;

	SetGeometoryTranslate(m_pos.x, m_pos.y, m_pos.z);
	SetGeometoryRotation(rot.x, rot.y, rot.z);
	SetGeometoryScaling(m_size, 10000, m_size);

	m_time -= 1.0f / 60.0f;

	
	SetColorPS(true, 0.3f, 0.76f, 1.0f, 0.5f, 1, 1);
	DrawCapsule();
}

bool CBeam::Collision(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 target, float size)
{
	m_enemyPos = pos;
	m_enemyTarget = target;
	m_enemySize = size;

	DirectX::XMVECTOR vPos = DirectX::XMLoadFloat3(&m_pos);
	DirectX::XMVECTOR vTarget = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&m_target), vPos));

	DirectX::XMVECTOR vEnemyPos = DirectX::XMLoadFloat3(&m_enemyPos);
	DirectX::XMVECTOR vEnemyTarget = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&m_enemyTarget), vEnemyPos));


	// 内積の計算
	DirectX::XMVECTOR vdot = DirectX::XMVector3Dot(vTarget, vEnemyTarget);
	
	float rad;
	DirectX::XMStoreFloat(&rad, vdot);

	rad = acosf(rad);

	if (rad <= 10) // 敵とビームの当たり判定
	{
		return true;
	}
	else if(rad <= 20) // 敵と衝撃波の当たり判定
	{
		return false;
	}
}
