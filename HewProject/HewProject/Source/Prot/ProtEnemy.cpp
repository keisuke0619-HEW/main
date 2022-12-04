#include "ProtEnemy.hpp"
#include <Easing.hpp>
#include <SceneBase.hpp>
// 当たり判定は後で付けます。

CProtEnemy::CProtEnemy()
	: CObjectBase("Assets/MagicaBoxelModel/PlaneBox.obj")
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
	
	// もしプレイヤーとの距離が一定以下だったら

	// プレイヤーを目標にする

	// 違ったら

	// ランダム移動
}

// 死亡時に勝手に呼ばれます。
void CProtEnemy::Finalize()
{
	// マネージャに死んだことを伝える

}
