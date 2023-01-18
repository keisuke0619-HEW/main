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

	m_pEfk2.reset(new CEffect(u"Assets/Effect/Beamhassya.efkefc"));
}

CBeam::~CBeam()
{
	/*m_pEfk->~CEffect();
	m_pEfk2->~CEffect();*/
	//m_pEfk->End();
	//m_pEfk2->End();
}

void CBeam::Update()
{
	const int beamGrowFrame = 60 * 1;
	const int beamDeadFrame = 60 * 3;
	if (m_param.frame < beamGrowFrame)
	{
		m_size = m_maxSize * Utility::OutQuad((float)m_param.frame / beamGrowFrame);// += m_maxSize / beamGrowFrame;
		if (m_SelectEfk == 2)
		{
			Collision();
		}
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
		DirectX::XMVECTOR vEnemyTarget = DirectX::XMVectorSubtract(vEnemyPos, vPos); // ビームの開始地点から敵の位置のベクトル
		DirectX::XMVECTOR vEnemyTargetNormal = DirectX::XMVector3Normalize(vEnemyTarget); // ビームの開始地点から敵の位置の単位ベクトル

		// 内積の計算１（角度をとるための計算。単位ベクトル×単位ベクトルからAcosで角度取得可能）
		float normalDot;	// 内積の結果を保存する変数
		DirectX::XMVECTOR vdot = DirectX::XMVector3Dot(vTarget, vEnemyTargetNormal);	// 内積を計算
		DirectX::XMStoreFloat(&normalDot, vdot);	// float型の変数に格納
		if (normalDot <= 0.0f)	// 後ろは判定しない
		{
			continue;
		}
		// 内積の計算２（ビームのどの地点が一番近いかを取得。単位ベクトル×ベクトルでベクトルが単位ベクトルに落とす影の長さに等しいのを利用。）
		float disToEnemy;	// ビームベクトルに落ちる影の長さを格納する
		vdot = DirectX::XMVector3Dot(vTarget, vEnemyTarget);	// ビーム単位ベクトルと敵ベクトルの内積。（＝ビームベクトルに落ちる影の長さ）
		DirectX::XMStoreFloat(&disToEnemy, vdot);	// floatに格納

		// ビームと敵の角度を計算
		float rad = acosf(normalDot);// ビームベクトルと敵ベクトルの角度

		float disFromBeam = tanf(rad) * disToEnemy;	// ビームから敵の距離
		disFromBeam = fabsf(disFromBeam);			// 絶対値をとる

		// 以下当たり判定
		if (disFromBeam < m_maxSize * 3)
		{
			(*itr)->OnCollisionTag(TAG_BEAM);

		}
		else if (disFromBeam < m_maxSize * 6)
		{
			(*itr)->OnCollisionTag(TAG_SHOCK);
		}
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
