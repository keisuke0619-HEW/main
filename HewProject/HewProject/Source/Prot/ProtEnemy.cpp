#include "ProtEnemy.hpp"
#include <Easing.hpp>
#include <SceneBase.hpp>
#include <Controller.hpp>
// 当たり判定は後で付けます。

CProtEnemy::CProtEnemy()
	: CObjectBase("Assets/Box.fbx", 0.2f)
	, m_move(0.008f)
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
	if (Utility::GetKeyTrigger(Utility::Key_U))
		Destroy();
	// 移動るーちん
	Move();
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
		m_param.pos.x += movePos.x * m_move; // エネミーのposを使う
		m_param.pos.y += movePos.y * m_move;
		m_param.pos.z += movePos.z * m_move;
	}
	else
	{
		// ランダムで移動する
		if (m_cnt % 60 == 0)
		{
			m_randNum = rand() % 4;
		
		}
		switch (m_randNum)
		{
		case(0):
			m_param.pos.x += m_move * Utility::InOutSine(m_cnt / 60.f);
			break;
		case(1):
			m_param.pos.x -= m_move * Utility::InOutSine(m_cnt / 60.f);
			break;
		case(2):
			m_param.pos.z += m_move * Utility::InOutSine(m_cnt / 60.f);
			break;
		case(3):
			m_param.pos.z -= m_move * Utility::InOutSine(m_cnt / 60.f);
			break;
		default:
			break;
		}
	}

	// カウントを増やす
	
	m_cnt++;
	if (m_cnt > 60)
	{
		m_cnt = 0;
	}
}

// 死亡時に勝手に呼ばれます。
void CProtEnemy::Finalize()
{
	// マネージャに死んだことを伝える

}
