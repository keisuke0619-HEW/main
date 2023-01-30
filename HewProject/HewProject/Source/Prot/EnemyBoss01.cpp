#include"EnemyBoss01.hpp"
#include <Easing.hpp>
#include <SceneBase.hpp>
#include <Controller.hpp>
#include <Camera.hpp>
#include <Blend.hpp>
#include <SceneManager.hpp>
#include <SceneResult.hpp>
#include <SE.h>
#include <Player.hpp>
// 当たり判定は後で付けます。

CProtEnemyBoss::CProtEnemyBoss(Data* data, float bossHP)
	: CObjectBase("Assets/Model/boss/ani.fbx", 0.2f)
	, m_move(0.023f)
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
	m_param.pos.z = ((rand() % 100) / 10.0f)+23.f;

	// 種類を識別するタグを設定
	m_param.tag = TAG_ENEMY_BOSS;
	// UIを設定
	m_bossUI.reset(new CBossUI());
	// 描画のオフセットを指定（内部的な"Pos"と描画のギャップを埋める）
	m_param.drawOffset = { 0,0,0 };

	// 当たり判定の情報設定
	m_param.collisionType = COLLISION_CHARACTER;
	m_param.collisionData.character.pos = m_param.pos;
	m_param.collisionData.character.pos.y = m_param.drawOffset.y + 0.08f;
	m_param.collisionData.character.radius = 1.0f;

	Model::AnimeNo no = m_modelData.model->AddAnimation("Assets/Model/boss/bone.fbx");
	if (no == Model::ANIME_NONE)
		MessageBox(nullptr, "walk.fbx", "Error", MB_OK);
	m_modelData.model->Play(no, true);

	m_HP = bossHP;

	m_param.hp *= m_HP;

	m_Fream = 0;

	m_Damage = 0.005f;
	m_isPlayerPowerUp = false;
	m_pEfk.reset(new CEffect(u"Assets/Effect/zirai.efkefc"));
	CSoundSE::BoolStop();
	CSoundSE::CountReset();
}

CProtEnemyBoss::~CProtEnemyBoss()
{

}

void CProtEnemyBoss::Update()
{
	if (m_param.hp <= 0.3f && CSoundSE::GetCount() == 0)
	{
		CSoundSE::Start(CSoundSE::SE_VOICE_FIGHT_WIN);
		CSoundSE::CountUp();
	}
	// ボスが死んでいたら
	if (m_param.hp <= 0.0f)
	{
		if (m_Fream == 0)
		{
			CSoundSE::Start(CSoundSE::SE_EXPLOTION);
		}
		
		CSoundSE::BoolPlay();
		m_Fream++;
		m_pEfk->SetScale(m_param.scale.x, m_param.scale.y, m_param.scale.z);
		m_pEfk->SetPos(m_param.pos.x + (rand() % 3), m_param.pos.y + (rand() % 3), m_param.pos.z + (rand() % 3));
		m_pEfk->PlayOnce();
		m_bossUI->Update();
		m_cnt++;
		if (m_cnt >= 20)
		{
			m_pEfk->End();
			m_cnt = 0;
		}
		// ３秒たったら
		if (m_Fream >= 120)//要調整
		{
			CSoundSE::BoolStop();
			CSceneResult::SetClear();
			CSceneManager::SetScene(SCENE_RESULT);
		}
	}
	else
	{
		m_oldPos = m_param.pos;
		// もしプレイヤーのオブジェクトが消えていたらもう一度取得
		if (m_player.expired() == true)
		{
			auto objList = CSceneBase::GetObjList();
			m_player = objList.lock()->FindTag(TAG_PLAYER);
		}

		// 移動るーちん
		Move();

		m_param.pos.y -= 0.08f;
		// 疑似床判定
		if (m_param.pos.y < 0)
			m_param.pos.y = 0;

		AddVector3(m_param.move, m_param.accel);
		AddVector3(m_param.pos, m_param.move);

		// 当たり判定の更新
		m_param.collisionData.character.pos = m_param.pos;
		m_param.collisionData.character.pos.y += m_param.drawOffset.y + 0.1f;
		m_param.collisionData.character.radius = 1.4f;

		// ボスUIの更新
		m_bossUI->Update();

	}

	m_isPlayerPowerUp = CPlayer::isGetPlayerBuff();
}

void CProtEnemyBoss::Draw()
{
	m_modelData.model->Step(1.0f / 60.0f);
	CObjectBase::Draw();
	
	// ボスUIの描画
	m_bossUI->SetLife(m_param.hp / m_HP);
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
	switch (obj->GetParam().tag)
	{
	case TAG_NONE:
		break;
	case TAG_PLAYER:
		break;
	case TAG_CAMERA:
		break;
	case TAG_ENEMY:
		break;
	case TAG_BEAM:
		break;
	case TAG_SHOCK:
		break;
	case TAG_STATIC_OBJECT:
		m_param.pos.x = m_oldPos.x;
		m_param.pos.z = m_oldPos.z;
		m_param.move = { 0.f,0.f,0.f };
		break;
	default:
		break;
	}
}

void CProtEnemyBoss::OnCollisionTag(EObjectTag tag)
{
	if (tag == TAG_BEAM)
	{
		if (m_isPlayerPowerUp == true)
		{
			m_param.hp -= m_Damage * 1.5f;
		}
		else
		{
			m_param.hp -= m_Damage;
		}
	}
}