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
	m_size = 0;

	m_maxSize = size;
	m_time = 2.0f;

	// エフェクシアの初期化　読み込み
	m_pEfk.reset(new CEffect(u"Assets/Effect/Laser01.efkefc"));
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
	m_pEfk->SetRotation(0, -60, 0);
	m_pEfk->SetScale(1, 1, 1);
	m_pEfk->SetPos(m_pos.x, m_pos.y, m_pos.z);//(m_param.pos.x, m_param.pos.y + 1.5f, m_param.pos.z);
}

void CBeam::Draw()
{
	// 発射起点がm_posに、ターゲット座標がm_targetに入っています。
	// それらの変数から軸の回転を求めてrotにぶち込みました。
	SetGeometoryVPMatrix(CCameraBase::GetPrimaryViewMatrix(), CCameraBase::GetPrimaryProjectionMatrix());

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

	SetColorPS(true, 0.3f, 0.56f, 1.0f, 0.5f, 1, 1);
	DrawCapsule();

	// 毎回エフェクシアを描画するため処理が重くなる
	// 新しく関数を作るなど改善の余地あり
	//m_pEfk->Play();
	
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
		DirectX::XMVECTOR vEnemyTarget = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(vEnemyPos, vPos)); // ビームの開始地から敵の位置の単位ベクトル

		// 内積の計算
		DirectX::XMVECTOR vdot = DirectX::XMVector3Dot(vTarget, vEnemyTarget);
		float A;
		DirectX::XMStoreFloat(&A,vdot);
		if (A < 0.0f)
		{
			continue;
		}
		
		// ビームと敵の角度を計算
		float rad;
		DirectX::XMStoreFloat(&rad, vdot);
		rad = acosf(rad);

		// ビームと敵との距離を計算
		DirectX::XMVECTOR vEnemyToBeamDis = DirectX::XMVectorSubtract(vEnemyPos,vPos);
		float EnemyToBeamDis;
		DirectX::XMStoreFloat(&EnemyToBeamDis, vEnemyToBeamDis);
		float distance = sinf(rad) * EnemyToBeamDis;

		// 絶対値  
		float AbsoluteValue_EnemyDis = fabsf(distance);
		float AbsoluteValue_BeamPos = fabsf(m_size);
		float AbsoluteValue_Shockwave = fabsf(m_size * 2.0f);

		// 当たり判定を取るための計算
		float DisResult = enemyParam.collisionData.sphire.sphireRadius - (AbsoluteValue_EnemyDis - AbsoluteValue_BeamPos);
		float ShockwaveDisResult = enemyParam.collisionData.sphire.sphireRadius - (AbsoluteValue_EnemyDis - AbsoluteValue_Shockwave);

		// ビームと敵の当たり判定
		if (DisResult > 0)
		{
			(*itr)->OnCollisionTag(TAG_BEAM);
		}
		else if (ShockwaveDisResult > 0)	// 衝撃波と敵の当たり判定
		{
			(*itr)->OnCollisionTag(TAG_SHOCK);
		}
	}
}
