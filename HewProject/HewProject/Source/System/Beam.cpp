#include "Beam.hpp"
#include <Geometory.h>
#include <DebugWindow.hpp>
#include <Easing.hpp>
#include <Camera.hpp>
#include <SceneBase.hpp>
CBeam::CBeam(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 target, float size)
	: CObjectBase("Assets/Box.fbx")
{
	m_pos = pos;
	m_target = target;
	m_playerPos = DirectX::XMFLOAT3(0, 0, 0);
	m_size = 0;

	m_maxSize = size / 3;
	m_time = 2.0f;

	// エフェクシアの初期化　読み込み
	m_pEfk.reset(new CEffect(u"Assets/Effect/Beamtame.efkefc"));
	m_debugOutput = false;

	m_pEfk2.reset(new CEffect(u"Assets/Effect/Beamhassya.efkefc"));
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
		Collision();
	}
	if (m_param.frame >= beamDeadFrame)
	{
		Destroy();
	}	
	//m_pEfk->SetRotation(0, -60, 0);
	switch (m_SelectEfk)
	{
	case(1):
		m_pEfk->SetScale(m_maxSize, m_maxSize, m_maxSize);
		m_pEfk->SetPos(m_playerPos.x, m_playerPos.y + 1.5f, m_playerPos.z);
		break;
	case(2):
		m_pEfk2->SetScale(m_maxSize, m_maxSize, m_maxSize);
		m_pEfk2->SetPos(m_playerPos.x, m_playerPos.y + 1.5f, m_playerPos.z);
		break;
	default:
		break;
	}
}

void CBeam::Draw()
{
	// 発射起点がm_posに、ターゲット座標がm_targetに入っています。
	// それらの変数から軸の回転を求めてrotにぶち込みました。
	//m_pos = DirectX::XMFLOAT3(0, 0, 0);
	//m_target = DirectX::XMFLOAT3(1, 1, 1);
	SetGeometoryVPMatrix(CCameraBase::GetPrimaryViewMatrix(), CCameraBase::GetPrimaryProjectionMatrix());

	DirectX::XMFLOAT3 rot = {};

	DirectX::XMVECTOR vPos = DirectX::XMLoadFloat3(&m_pos);
	DirectX::XMVECTOR vTarget = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&m_target), vPos));
	DirectX::XMVECTOR vToTarget = DirectX::XMVectorAdd(vTarget, DirectX::XMVectorZero());

	DirectX::XMFLOAT3 ToTarget;

	DirectX::XMStoreFloat3(&ToTarget, vToTarget);

	rot.x = -asinf(ToTarget.y);
	rot.y = atan2f(ToTarget.x, ToTarget.z);
	rot.z = 0;

	SetGeometoryTranslate(m_pos.x, m_pos.y, m_pos.z);
	SetGeometoryRotation(rot.x, rot.y, rot.z);
	SetGeometoryScaling(m_size, 10000, m_size);
	m_time -= 1.0f / 60.0f;

	switch (m_SelectEfk)
	{
	case(1):
		m_pEfk->SetRotation(rot.x, rot.y, rot.z);
		m_pEfk->Play();
		break;
	case(2):
		m_pEfk2->SetRotation(rot.x, rot.y, rot.z);
		m_pEfk2->Play();
		break;
	default:
		break;
	}
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
		DirectX::XMVECTOR vEnemyTarget = DirectX::XMVectorSubtract(vEnemyPos, vPos);		// ビームの開始地から敵の位置のベクトル
		DirectX::XMVECTOR vEnemyTargetNormal = DirectX::XMVector3Normalize(vEnemyTarget);	// ビームの開始地から敵の位置の単位ベクトル

		// 内積の計算
		float normalDot;
		DirectX::XMVECTOR vdot = DirectX::XMVector3Dot(DirectX::XMVectorSubtract(vTarget, DirectX::XMVectorZero()), DirectX::XMVectorSubtract(vEnemyTargetNormal, DirectX::XMVectorZero()));

		DirectX::XMStoreFloat(&normalDot,vdot);
		if (normalDot <= 0.0f)
		{
			continue;
		}

		// ビームと敵の角度を計算
		float rad;
		rad = acosf(normalDot);// ビームベクトルと敵ベクトルの角度

		float disFromBeam;
		DirectX::XMStoreFloat(&disFromBeam, DirectX::XMVector3Length(vEnemyTarget));
		disFromBeam *= sinf(rad);

		if (disFromBeam < m_maxSize)
		{
			(*itr)->OnCollisionTag(TAG_BEAM);
		}
		else if (disFromBeam < m_maxSize * 3)
		{
			(*itr)->OnCollisionTag(TAG_SHOCK);
		}

		if (m_debugOutput == false)
		{
			CDebugWindow::Print(ShimizuKeisuke, "FromBeam", disFromBeam);
			//CDebugWindow::Print(ShimizuKeisuke, "ToEnemy", disToEnemy);

		}

		m_debugOutput = true;

		//// ビームと敵との距離を計算
		//DirectX::XMVECTOR vEnemyToBeamDis = DirectX::XMVectorSubtract(vEnemyPos,vPos);
		//float EnemyToBeamDis;
		//DirectX::XMStoreFloat(&EnemyToBeamDis, vEnemyToBeamDis);
		//float distance = sinf(rad) * EnemyToBeamDis;

		//// 絶対値  
		//float AbsoluteValue_EnemyDis = fabsf(distance);
		//float AbsoluteValue_BeamPos = fabsf(m_size);
		//float AbsoluteValue_Shockwave = fabsf(m_size * 2.0f);

		//// 当たり判定を取るための計算
		//float DisResult = enemyParam.collisionData.sphire.sphireRadius - (AbsoluteValue_EnemyDis - AbsoluteValue_BeamPos);
		//float ShockwaveDisResult = enemyParam.collisionData.sphire.sphireRadius - (AbsoluteValue_EnemyDis - AbsoluteValue_Shockwave);

		// ビームと敵の当たり判定
		//if (DisResult > 0)
		//{
		//	(*itr)->OnCollisionTag(TAG_BEAM);
		//}
		//else if (ShockwaveDisResult > 0)	// 衝撃波と敵の当たり判定
		//{
		//	(*itr)->OnCollisionTag(TAG_SHOCK);
		//}
	}
}

void CBeam::SetPlayerPos(DirectX::XMFLOAT3 playerpos)
{
	m_playerPos = playerpos;
}

void CBeam::SetEffekseer(int selectnum)
{
	m_SelectEfk = selectnum;
}
