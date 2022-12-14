#include "Beam.hpp"
#include <Geometory.h>
#include <DebugWindow.hpp>
#include <Easing.hpp>

#include <SceneBase.hpp>
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
	Collision();
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

void CBeam::Collision()
{
	// プレイヤーのデータを取得
	DirectX::XMVECTOR vPos = DirectX::XMLoadFloat3(&m_pos);
	DirectX::XMVECTOR vTarget = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&m_target), vPos));


	// 敵のリスト
	auto enemyList = CSceneBase::GetObjList().lock()->FindTagAll(TAG_ENEMY);
	// 敵のリスト全探索
	for (auto itr = enemyList.begin(); itr != enemyList.end(); itr++)
	{
		// 敵のデータ格納
		auto enemyParam = (*itr)->GetParam();

		// 敵のデータを使ってエネミーとの当たり判定をとる
		m_enemyPos = enemyParam.pos;
		DirectX::XMVECTOR vEnemyPos = DirectX::XMLoadFloat3(&m_enemyPos);
		DirectX::XMVECTOR vEnemyTarget = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&m_pos), vEnemyPos));

		//// 内積の計算
		DirectX::XMVECTOR vdot = DirectX::XMVector3Dot(vTarget, vEnemyTarget);
		
		float rad;
		DirectX::XMStoreFloat(&rad, vdot);

		// ビームと敵の角度を計算
		rad = acosf(rad) * 180 / 3.14f;

		// 当たっていたらこれを呼ぶ。ちなみに今はTrueなので、ビームを発射しただけで全部死にます。
		if (rad <= 30)
		{
			(*itr)->OnCollisionTag(TAG_BEAM);
		}
		
	}

	//m_enemyPos = pos;
	//m_enemyTarget = target;
	//m_enemySize = size;

	//DirectX::XMVECTOR vPos = DirectX::XMLoadFloat3(&m_pos);
	//DirectX::XMVECTOR vTarget = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&m_target), vPos));

	//DirectX::XMVECTOR vEnemyPos = DirectX::XMLoadFloat3(&m_enemyPos);
	//DirectX::XMVECTOR vEnemyTarget = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&m_enemyTarget), vEnemyPos));


	//// 内積の計算
	//DirectX::XMVECTOR vdot = DirectX::XMVector3Dot(vTarget, vEnemyTarget);
	//
	//float rad;
	//DirectX::XMStoreFloat(&rad, vdot);

	//rad = acosf(rad);

	//if (rad <= 10) // 敵とビームの当たり判定
	//{
	//	return true;
	//}
	//else if(rad <= 20) // 敵と衝撃波の当たり判定
	//{
	//	return false;
	//}
}
