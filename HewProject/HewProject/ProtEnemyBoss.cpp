#include"ProtEnemyBoss.hpp"
#include <Easing.hpp>
#include <SceneBase.hpp>
#include <Controller.hpp>
#include <Camera.hpp>
#include <Blend.hpp>
// 当たり判定は後で付けます。

CProtEnemyBoss::CProtEnemyBoss()
	: CObjectBase("Assets/Box.fbx", 0.4f)
	, m_move(0.05f)
	, m_distance(4.0f)
	, m_cnt(0)
	, m_randNum(0)
	, m_target(DirectX::XMFLOAT3(0, 0, 0))
{
	// オブジェクトのリストを取得
	auto objList = CSceneBase::GetObjList();
	// プレイヤーのオブジェクトを取得
	m_player = objList.lock()->FindTag(TAG_PLAYER);
	m_param.pos.x = (rand() % 100) / 10.0f;
	m_param.pos.y = 1.0f;
	m_param.pos.z = (rand() % 100) / 10.0f;
	m_param.collisionType = COLLISION_BOX;
	m_param.collisionData.box.boxPos = m_param.pos;
	m_param.collisionData.box.boxScale = { 1,1,1 };
	m_param.tag = TAG_ENEMY;
	m_startPos = m_param.pos;

	m_bill = new CBillboard("Assets/Img/Boss.png");
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
	m_param.collisionData.box.boxPos = m_param.pos;
}

void CProtEnemyBoss::Draw()
{
	m_bill->SetPosViewProj(CCameraBase::GetPrimaryViewMatrix(), CCameraBase::GetPrimaryProjectionMatrix());
	m_bill->SetPos(m_param.pos);
	m_bill->Draw();
	Utility::SetBlendState(BLEND_NONE);
	CObjectBase::Draw();
	Utility::SetBlendState(BLEND_ALPHA);
}

// 移動ルーチン。Excelを参考に作成
// いーじんぐを使用。
void CProtEnemyBoss::Move()
{
	// いーじんぐ使用方法（例）
	// Easing::InOutSine(level);

	// プレイヤーとの距離を取得
	if (m_player.expired() == false)
		m_target = m_player.lock()->GetParam().pos;
	// プレイヤーとエネミーの位置情報
	DirectX::XMVECTOR enemy = DirectX::XMLoadFloat3(&m_param.pos);	// エネミーのposを入れる
	DirectX::XMVECTOR player = DirectX::XMLoadFloat3(&m_target);	// プレイヤーのposを入れる

	// 距離を計算
	DirectX::XMVECTOR distance = DirectX::XMVectorSubtract(player, enemy);
	//distance = DirectX::XMVector3Normalize(distance);
	// float3に変換して格納
	DirectX::XMFLOAT3 movePos;

	DirectX::XMStoreFloat3(&movePos, distance);

	//ボスに常に向かってくる
		m_param.pos.x += movePos.x * m_move / 2; // エネミーのposを使う
		m_param.pos.y += movePos.y * m_move / 2;
		m_param.pos.z += movePos.z * m_move / 2;
		m_param.frame = 0;
	
}

// 死亡時に勝手に呼ばれます。
void CProtEnemyBoss::Finalize()
{
	// マネージャに死んだことを伝える

}

void CProtEnemyBoss::OnCollision(Ptr obj)
{
	if (obj->GetParam().tag == TAG_PLAYER)
	{
		Destroy();
	}
}
