#include "ProtEnemy.hpp"
#include <Easing.hpp>
#include <SceneBase.hpp>
#include <Controller.hpp>
#include <Camera.hpp>
#include <Blend.hpp>
// 当たり判定は後で付けます。

CProtEnemy::CProtEnemy()
	: CObjectBase("Assets/Box.fbx", 0.4f)
	, m_move(0.05f)
	, m_distance(4.f)
	, m_cnt(0)
	, m_randNum(0)
	, m_target(DirectX::XMFLOAT3(0,0,0))
{
	// オブジェクトのリストを取得
	auto objList = CSceneBase::GetObjList();
	// プレイヤーのオブジェクトを取得
	m_player = objList.lock()->FindTag(TAG_PLAYER);
	m_param.pos.x = (rand() % 100) / 10.0f;
	m_param.pos.y = 1.0f;
	m_param.pos.z = (rand() % 100) / 10.0f;
	m_param.collisionType = COLLISION_BOX;
	m_param.collisionData.boxScale = { 1,1,1 };
	m_startPos = m_param.pos;
}

CProtEnemy::~CProtEnemy()
{

}

void CProtEnemy::Update()
{
	// もしプレイヤーのオブジェクトが消えていたらもう一度取得
	if (m_player.expired() == true)
	{
		auto objList = CSceneBase::GetObjList();
		m_player = objList.lock()->FindTag(TAG_PLAYER);
	}
	// 移動るーちん
	Move();
}

void CProtEnemy::Draw()
{
	Utility::SetBlendState(BLEND_NONE);
	CObjectBase::Draw();
	Utility::SetBlendState(BLEND_ALPHA);
}

// 移動ルーチン。Excelを参考に作成
// いーじんぐを使用。
void CProtEnemy::Move()
{
	// いーじんぐ使用方法（例）
	// Easing::InOutSine(level);

	// プレイヤーとの距離を取得
	if(m_player.expired() == false)
		m_target = m_player.lock()->GetParam().pos;
	// プレイヤーとエネミーの位置情報
	DirectX::XMVECTOR enemy = DirectX::XMLoadFloat3(&m_param.pos);	// エネミーのposを入れる
	DirectX::XMVECTOR player = DirectX::XMLoadFloat3(&m_target);	// プレイヤーのposを入れる

	// 距離を計算
	DirectX::XMVECTOR distance = DirectX::XMVectorSubtract(player, enemy);

	// float3に変換して格納
	DirectX::XMFLOAT3 movePos;
	DirectX::XMStoreFloat3(&movePos, distance);


	// もしプレイヤーとの距離が一定以下だったら
	if (fabsf(movePos.x) <= m_distance && fabsf(movePos.y) <= m_distance && fabsf(movePos.z) <= m_distance)
	{
		// プレイヤーを目標にする
		m_param.pos.x += movePos.x * m_move / 2; // エネミーのposを使う
		m_param.pos.y += movePos.y * m_move / 2;
		m_param.pos.z += movePos.z * m_move / 2;
		m_param.frame = 0;
	}
	else
	{
		if (m_param.frame % 300 == 0)
		{
			m_randTarget = { (float)(rand() % 30), 0.5f, (float)(rand() % 30) };
			m_startPos = m_param.pos;
		}
		m_param.move = {
			(m_startPos.x + (m_randTarget.x - m_startPos.x) * Utility::InOutSine((m_param.frame % 300) / 300.0f)) - (m_startPos.x + (m_randTarget.x - m_startPos.x) * Utility::InOutSine(((m_param.frame % 300) - 1) / 300.0f)),
			(m_startPos.y + (m_randTarget.y - m_startPos.y) * Utility::InOutSine((m_param.frame % 300) / 300.0f)) - (m_startPos.y + (m_randTarget.y - m_startPos.y) * Utility::InOutSine(((m_param.frame % 300) - 1) / 300.0f)),
			(m_startPos.z + (m_randTarget.z - m_startPos.z) * Utility::InOutSine((m_param.frame % 300) / 300.0f)) - (m_startPos.z + (m_randTarget.z - m_startPos.z) * Utility::InOutSine(((m_param.frame % 300) - 1) / 300.0f)),
		};
	}
}

// 死亡時に勝手に呼ばれます。
void CProtEnemy::Finalize()
{
	// マネージャに死んだことを伝える

}

void CProtEnemy::OnCollision(Ptr obj)
{
	if (obj->GetParam().tag == TAG_PLAYER)
	{
		Destroy();
	}
}
