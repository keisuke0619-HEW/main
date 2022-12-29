#include "ProtEnemy.hpp"
#include <Easing.hpp>
#include <SceneBase.hpp>
#include <Controller.hpp>
#include <Camera.hpp>
#include <Blend.hpp>

std::shared_ptr<Model> CProtEnemy::sModel;
std::shared_ptr<ConstantBuffer> CProtEnemy::sWVP;
std::shared_ptr<VertexShader> CProtEnemy::sVS;

// 当たり判定は後で付けます。

CProtEnemy::CProtEnemy()
	: CObjectBase()
	, m_move(0.05f)
	, m_distance(8.0f)
	, m_cnt(0)
	, m_randNum(0)
	, m_target(DirectX::XMFLOAT3(0,0,0))
	, m_dontMove(false)
	, m_blowAwayCountDown(0)
	, m_blowAwayMove({0.f, 0.f, 0.f})
	, m_ActionNum(rand() % 4 + 1)
{
	if (!sModel)
	{
		LoadModel("Assets/Model/zako.fbx", 0.1f, false, &sModel, &sVS, &sWVP);
	}
	m_model = sModel;
	m_vs = sVS;
	m_wvp = sWVP;

	// オブジェクトのリストを取得
	auto objList = CSceneBase::GetObjList();
	// プレイヤーのオブジェクトを取得
	m_player = objList.lock()->FindTag(TAG_PLAYER);
	m_param.pos.x = (rand() % 100) / 10.0f;
	m_param.pos.y = 1.0f;
	m_param.pos.z = (rand() % 100) / 10.0f;
	m_param.collisionType = COLLISION_SPHIRE;
	m_param.collisionData.sphire.sphirePos = m_param.pos;
	m_param.collisionData.sphire.sphireRadius = m_param.scale.x / 2.0f;
	m_startPos = m_param.pos;
	m_param.tag = TAG_ENEMY;
	m_pPolyline = new GeometoryPolyline(30);

	// ここで描画をずらす
	m_param.drawOffset = { 0, 1.2f, 0 };
}

CProtEnemy::~CProtEnemy()
{

}

void CProtEnemy::Update()
{
	m_param.frame++;

	// もしプレイヤーのオブジェクトが消えていたらもう一度取得
	if (m_player.expired() == true)
	{
		auto objList = CSceneBase::GetObjList();
		m_player = objList.lock()->FindTag(TAG_PLAYER);
	}
	// 移動るーちん
	Move();
	m_param.collisionData.sphire.sphirePos = m_param.pos;
	if (m_param.pos.y < 1.3f)
	{
		m_param.pos.y = 1.3f;
	}
}

void CProtEnemy::Draw()
{

	//Utility::SetBlendState(BLEND_NONE);
	CObjectBase::Draw();
	//Utility::SetBlendState(BLEND_ALPHA);
	//奇跡の追加
	GeometoryPolyline::Point point = {};
	//ポリライン
	auto fCamPos = CCameraBase::GetPrimaryData().pos;
	
	DirectX::XMVECTOR vCamPos = DirectX::XMLoadFloat3(&fCamPos);
	DirectX::XMVECTOR vPos = DirectX::XMLoadFloat3(&CProtEnemy::m_param.pos);
	DirectX::XMStoreFloat3(&point.normal, DirectX::XMVectorSubtract(vCamPos, vPos));
	point.pos = CProtEnemy::m_param.pos;
	point.width = 200.0f;
	m_pPolyline->PushPoint(point);
	m_pPolyline->SetView(CCameraBase::GetPrimaryViewMatrix());
	m_pPolyline->SetProjection(CCameraBase::GetPrimaryProjectionMatrix());
	m_pPolyline->Draw();

}

// 移動ルーチン。Excelを参考に作成
// いーじんぐを使用。
void CProtEnemy::Move()
{
	// いーじんぐ使用方法（例）
	// Easing::InOutSine(level);

	// 衝撃波に当たって吹っ飛ぶときの移動
	if (m_dontMove)
	{
		m_param.pos.x += m_blowAwayMove.x * m_move * m_blowAwayCountDown; // この後ろにさらにビームの強さを付け加える
		m_param.pos.y += m_blowAwayMove.y * m_move * m_blowAwayCountDown;
		m_param.pos.z += m_blowAwayMove.z * m_move * m_blowAwayCountDown;

		// カウントが0になっていたら吹っ飛びをやめる
		if (m_blowAwayCountDown < 0)
		{
			m_dontMove = false;
		}

		// 吹っ飛ぶカウントダウン
		m_blowAwayCountDown--;
	}

	// 衝撃波に当たってないときの移動(通常時の移動)
	else
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
		
		DirectX::XMVECTOR move;

		// 回転処理
		DirectX::XMFLOAT3 Move;
		DirectX::XMStoreFloat3(&Move, distance);
		Move.y = 0.0f;

		if (fabsf(Move.x) + fabsf(Move.z) > 0.0f)
		{
			float rot = atan2f(Move.z, Move.x);
			m_param.rot.y = DirectX::XMConvertToRadians(90.f) - rot;
		}

		// 移動方向切り替え
		if (m_param.frame / 300 > 0)
		{
			m_ActionNum = rand() % 100;

			if (0 <= m_ActionNum && m_ActionNum <= 39)	//	40%でプレイヤーへ
			{
				m_ActionNum = 1;
			}
			else
			{
				if (40 <= m_ActionNum && m_ActionNum <= 64)	//	25%で右
				{
					m_ActionNum = 2;
				}
				else
				{
					if (65 <= m_ActionNum && m_ActionNum <= 89)	//	25%で左
					{
						m_ActionNum = 3;
					}
					else	//残りの10%でプレイヤーとは逆へ
					{
						m_ActionNum = 4;
					}
				}
			}
			
			switch (m_ActionNum)
			{
			case 1:
				// 正規化して速さを一定にする
				distance = DirectX::XMLoadFloat3(&movePos);
				distance = DirectX::XMVector3Normalize(distance);
				DirectX::XMStoreFloat3(&movePos, distance);
				break;
			case 2:
				distance = DirectX::XMVector3Normalize(distance);
				move = DirectX::XMVector3TransformCoord(distance, DirectX::XMMatrixRotationY(90.0f * 3.14f / 180.0f));
				DirectX::XMStoreFloat3(&movePos, move);
				break;
			case 3:
				distance = DirectX::XMVector3Normalize(distance);
				move = DirectX::XMVector3TransformCoord(distance, DirectX::XMMatrixRotationY(-90.0f * 3.14f / 180.0f));
				DirectX::XMStoreFloat3(&movePos, move);
				break;
			case 4:
				// 正規化して速さを一定にする
				distance = DirectX::XMLoadFloat3(&movePos);
				distance = DirectX::XMVector3Normalize(distance);
				DirectX::XMStoreFloat3(&movePos, distance);
				break;
			default:
				break;
			}

			m_param.frame = 0;
		}		

		// 移動
		m_param.pos.x += movePos.x * m_move; // エネミーのposを使う
		m_param.pos.z += movePos.z * m_move;

		//// もしプレイヤーとの距離が一定以下だったら
		//if (fabsf(movePos.x) <= m_distance && fabsf(movePos.y) <= m_distance && fabsf(movePos.z) <= m_distance)
		//{
		//	// 正規化して速さを一定にする
		//	distance = DirectX::XMLoadFloat3(&movePos);
		//	distance = DirectX::XMVector3Normalize(distance);
		//	DirectX::XMStoreFloat3(&movePos, distance);
		//	// プレイヤーを目標にする
		//	m_param.pos.x += movePos.x * m_move / 2; // エネミーのposを使う
		//	m_param.pos.y += movePos.y * m_move / 2;
		//	m_param.pos.z += movePos.z * m_move / 2;
		//	m_param.frame = 0;
		//}
		//else
		//{
		//	if (m_param.frame % 300 == 0)
		//	{
		//		m_randTarget = { (float)(rand() % 30), 0.5f, (float)(rand() % 30) };
		//		m_startPos = m_param.pos;
		//	}
		//	m_param.move = {
		//		(m_startPos.x + (m_randTarget.x - m_startPos.x) * Utility::InOutSine((m_param.frame % 300) / 300.0f)) - (m_startPos.x + (m_randTarget.x - m_startPos.x) * Utility::InOutSine(((m_param.frame % 300) - 1) / 300.0f)),
		//		(m_startPos.y + (m_randTarget.y - m_startPos.y) * Utility::InOutSine((m_param.frame % 300) / 300.0f)) - (m_startPos.y + (m_randTarget.y - m_startPos.y) * Utility::InOutSine(((m_param.frame % 300) - 1) / 300.0f)),
		//		(m_startPos.z + (m_randTarget.z - m_startPos.z) * Utility::InOutSine((m_param.frame % 300) / 300.0f)) - (m_startPos.z + (m_randTarget.z - m_startPos.z) * Utility::InOutSine(((m_param.frame % 300) - 1) / 300.0f)),
		//	};
		//}
	}
}

// 死亡時に勝手に呼ばれます。
void CProtEnemy::Finalize()
{
	// マネージャに死んだことを伝える

}

void CProtEnemy::OnCollisionTag(EObjectTag tag)
{
	
	if (tag == TAG_BEAM)
	{
		Destroy();
	}

	if (tag == TAG_SHOCK && m_dontMove == false)
	{
		// 衝撃波に当たったら敵の移動を消す
		m_dontMove = true;

		// 吹っ飛ぶカウントを開始
		m_blowAwayCountDown = m_blowAwayCount;

		// カメラの向いてる方向を取得
		DirectX::XMStoreFloat3(&m_blowAwayMove, CCameraBase::GetPrimaryFront());
	}
}

void CProtEnemy::OnCollision(IObjectBase::Ptr obj)
{
	if (obj->GetParam().tag == TAG_PLAYER)
	{
		Destroy();
	}
}


