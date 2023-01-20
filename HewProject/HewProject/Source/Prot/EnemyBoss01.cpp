#include"EnemyBoss01.hpp"
#include <Easing.hpp>
#include <SceneBase.hpp>
#include <Controller.hpp>
#include <Camera.hpp>
#include <Blend.hpp>
#include <SceneManager.hpp>
// 当たり判定は後で付けます。

CProtEnemyBoss::CProtEnemyBoss()
	: CObjectBase("Assets/Model/bosu.fbx", 0.1f)
	, m_move(0.015f)
	, m_distance(4.0f)
	, m_cnt(0)
	, m_randNum(0)
	, m_target(DirectX::XMFLOAT3(0, 0, 0))
{
	// オブジェクトのリストを取得
	auto objList = CSceneBase::GetObjList();
	// プレイヤーのオブジェクトを取得
	m_player = objList.lock()->FindTag(TAG_PLAYER);
	// 初期座標を設定
	m_param.pos.x = (rand() % 100) / 10.0f;
	m_param.pos.y = 1.0f;
	m_param.pos.z = (rand() % 100) / 10.0f;
	// 当たり判定の情報設定
	m_param.collisionType = COLLISION_SPHIRE;	// 球の当たり判定を使用
	m_param.collisionData.sphire.sphirePos = m_param.pos;	// 当たり判定の中心座標
	m_param.collisionData.sphire.sphireRadius = m_param.scale.x / 2.0f;	// 当たり判定の半径
	// 種類を識別するタグを設定
	m_param.tag = TAG_ENEMY;
	// UIを設定
	m_bossUI.reset(new CBossUI());
	// 描画のオフセットを指定（内部的な"Pos"と描画のギャップを埋める）
	m_param.drawOffset = { 0,0.8f,0 };
}

CProtEnemyBoss::~CProtEnemyBoss()
{

}

void CProtEnemyBoss::Update()
{
	// もしプレイヤーのオブジェクトが消えていたらもう一度取得
	if (m_player.expired() == true)
	{
		auto objList = CSceneBase::GetObjList();
		m_player = objList.lock()->FindTag(TAG_PLAYER);
	}
	// 移動るーちん
	Move();
	// 当たり判定の中心を更新
	m_param.collisionData.sphire.sphirePos = m_param.pos;

	m_param.pos.y -= 0.08f;
	// 疑似床判定
	if(m_param.pos.y < 0)
		m_param.pos.y = 0;
	// ボスUIの更新
	m_bossUI->Update();
}

void CProtEnemyBoss::Draw()
{
	CObjectBase::Draw();
	
	// ボスUIの描画
	m_bossUI->SetLife(m_param.hp);
}

void CProtEnemyBoss::Move()
{
	// プレイヤーとの距離を取得
	if (m_player.expired() == false)
		m_target = m_player.lock()->GetParam().pos;
	// プレイヤーとエネミーの位置情報
	DirectX::XMVECTOR enemy = DirectX::XMLoadFloat3(&m_param.pos);	// エネミーのposを入れる
	DirectX::XMVECTOR player = DirectX::XMLoadFloat3(&m_target);	// プレイヤーのposを入れる

	// 距離を計算
	DirectX::XMVECTOR distance = DirectX::XMVectorSubtract(player, enemy);
	distance = DirectX::XMVector3Normalize(distance);
	// float3に変換して格納
	DirectX::XMFLOAT3 movePos;

	DirectX::XMStoreFloat3(&movePos, distance);

	//ボスに常に向かってくる
	m_param.pos.x += movePos.x * m_move; // エネミーのposを使う
	m_param.pos.y += movePos.y * m_move;
	m_param.pos.z += movePos.z * m_move;
	m_param.frame = 0;

	DirectX::XMFLOAT3 Move;
	DirectX::XMStoreFloat3(&Move, distance);
	Move.y = 0.0f;
	if (fabsf(Move.x) + fabsf(Move.z) > 0.0f)
	{
		float rot = atan2f(Move.z, Move.x);
		m_param.rot.y = DirectX::XMConvertToRadians(90.f) - rot;
	}
	
}

// 死亡時に勝手に呼ばれます。
void CProtEnemyBoss::Finalize()
{
	// マネージャに死んだことを伝える

}

void CProtEnemyBoss::OnCollision(Ptr obj)
{
}

void CProtEnemyBoss::OnCollisionTag(EObjectTag tag)
{
	if (tag == TAG_BEAM)
	{
		m_param.hp -= 0.005f;
		if (m_param.hp <= 0.0f)
		{
			CSceneManager::SetScene(SCENE_RESULT);
		}
	}
}