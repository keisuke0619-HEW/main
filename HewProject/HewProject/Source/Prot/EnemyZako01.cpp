#include "EnemyZako01.hpp"
#include <Easing.hpp>
#include <SceneBase.hpp>
#include <Controller.hpp>
#include <Camera.hpp>
#include <Blend.hpp>

TModelData CProtEnemy::sModel;

CProtEnemy::CProtEnemy(Data* data)
	: CObjectBase()	// クラス全体で使いまわす場合は引数なし
	, m_move(0.05f)
	, m_distance(8.0f)
	, m_homing(false)
	, m_cnt(0)
	, m_randNum(0)
	, m_target(DirectX::XMFLOAT3(0,0,0))
	, m_dontMove(false)
	, m_blowAwayCountDown(0)
	, m_moveDirection({0.f, 0.f, 0.f})
	, m_blowAwayMove({0.f, 0.f, 0.f})
	, m_ActionNum(rand() % 4 + 1)
{
	// もしモデルデータが存在しなかったらロード
	static Model::AnimeNo animeNo;
	if (!sModel.model)
	{
		LoadModel("Assets/Model/zako/ani.fbx", 0.13f, false, &sModel);
		animeNo = sModel.model->AddAnimation("Assets/Model/zako/bone.fbx");
		if (animeNo == Model::ANIME_NONE)
			MessageBox(nullptr, "walk.fbx", "Error", MB_OK);
	}
	// 自身のモデルデータにStaticモデルデータをロード
	m_modelData = sModel;
	// モデルをクラス全体で使いまわすならここまでが必須。
	m_modelData.model->Play(animeNo, true);

	// オブジェクトのリストを取得
	auto objList = CSceneBase::GetObjList();

	// プレイヤーのオブジェクトを取得
	m_player = objList.lock()->FindTag(TAG_PLAYER);
	m_param.pos.x = (rand() % 100) / 10.0f;
	m_param.pos.y = 1.0f;
	m_param.pos.z = ((rand() % 100) / 10.0f)+23.f;

	m_startPos = m_param.pos;
	m_param.tag = TAG_ENEMY;

	m_param.frame = 300.0f;

	// ここで描画をずらす
	m_param.drawOffset = { 0, 0.2f, 0 };

	// 当たり判定の設定
	m_param.collisionType = COLLISION_CHARACTER;
	m_param.collisionData.character.pos = m_param.pos;
	m_param.collisionData.character.pos.y += m_param.drawOffset.y + 0.08f;
	m_param.collisionData.character.radius = 0.6f;

	//m_pEfk.reset(new CEffect(u"Assets/Effect/bakuhatu.efkefc"));

	m_data = data;
}

CProtEnemy::~CProtEnemy()
{

}

void CProtEnemy::Update()
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

	if (m_param.pos.y < 0)
	{
		m_param.pos.y = 0;
	}

	AddVector3(m_param.move, m_param.accel);
	AddVector3(m_param.pos, m_param.move);

	// 当たり判定の更新
	m_param.collisionData.character.pos = m_param.pos;
	m_param.pos.y -= 0.08f;	
}

void CProtEnemy::Draw()
{
	m_modelData.model->Step(1.0f / 60.0f);
	//Utility::SetBlendState(BLEND_NONE);
	CObjectBase::Draw();
	//Utility::SetBlendState(BLEND_ALPHA);
	//奇跡の追加
	//GeometoryPolyline::Point point = {};
	////ポリライン
	//auto fCamPos = CCameraBase::GetPrimaryData().pos;
	//
	//DirectX::XMVECTOR vCamPos = DirectX::XMLoadFloat3(&fCamPos);
	//DirectX::XMVECTOR vPos = DirectX::XMLoadFloat3(&CProtEnemy::m_param.pos);
	//DirectX::XMStoreFloat3(&point.normal, DirectX::XMVectorSubtract(vCamPos, vPos));
	//point.pos = CProtEnemy::m_param.pos;
	//point.width = 200.0f;
	//m_pPolyline->PushPoint(point);
	//m_pPolyline->SetView(CCameraBase::GetPrimaryViewMatrix());
	//m_pPolyline->SetProjection(CCameraBase::GetPrimaryProjectionMatrix());
	//m_pPolyline->Draw();

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
		if (m_player.expired() == false)
			m_target = m_player.lock()->GetParam().pos;

		if (pow(m_target.x - m_param.pos.x, 2) + pow(m_target.z - m_param.pos.z, 2) <= pow(m_distance, 2))
		{
			m_homing = true;
		}
		else
		{
			m_homing = false;
		}

		if (m_homing == true)
		{
			// プレイヤーとエネミーの位置情報
			DirectX::XMVECTOR enemy = DirectX::XMLoadFloat3(&m_param.pos);	// エネミーのposを入れる
			DirectX::XMVECTOR player = DirectX::XMLoadFloat3(&m_target);	// プレイヤーのposを入れる

			// 方向を計算
			DirectX::XMVECTOR direction = DirectX::XMVectorSubtract(player, enemy);

			// 正規化して速さを一定にする
			direction = DirectX::XMVector3Normalize(direction);

			// スピード変更
			m_move = 0.05f;

			// float3に変換して格納
			DirectX::XMStoreFloat3(&m_moveDirection, direction);

			// 回転
			if (fabsf(m_moveDirection.x) + fabsf(m_moveDirection.z) > 0.0f)
			{
				float rot = atan2f(m_moveDirection.z, m_moveDirection.x);
				m_param.rot.y = DirectX::XMConvertToRadians(90.f) - rot;
			}
		}
		else
		{
			// 移動種類切り替え
			if (m_param.frame > 300)
			{
				// プレイヤーとの距離を取得
				if (m_player.expired() == false)
					m_target = m_player.lock()->GetParam().pos;

				// プレイヤーとエネミーの位置情報
				DirectX::XMVECTOR enemy = DirectX::XMLoadFloat3(&m_param.pos);	// エネミーのposを入れる
				DirectX::XMVECTOR player = DirectX::XMLoadFloat3(&m_target);	// プレイヤーのposを入れる

				// 方向を計算
				DirectX::XMVECTOR direction = DirectX::XMVectorSubtract(player, enemy);

				// 正規化して速さを一定にする
				direction = DirectX::XMVector3Normalize(direction);

				// float3に変換して格納
				DirectX::XMStoreFloat3(&m_moveDirection, direction);

				// 回転処理(A)
				float rot = 0.0f;

				if (fabsf(m_moveDirection.x) + fabsf(m_moveDirection.z) > 0.0f)
				{
					rot = atan2f(m_moveDirection.z, m_moveDirection.x);
				}

				m_ActionNum = rand() % 100;

				if (0 <= m_ActionNum && m_ActionNum < 40)
				{
					m_ActionNum = 1;										// 40%でプレイヤーへ
				}
				else
				{
					if (40 <= m_ActionNum && m_ActionNum < 60)
					{
						m_ActionNum = 2;									// 20%で45°
					}
					else
					{
						if (60 <= m_ActionNum && m_ActionNum < 80)
						{
							m_ActionNum = 3;								// 20%で-45°	
						}
						else
						{
							if (80 <= m_ActionNum && m_ActionNum < 90)	
							{
								m_ActionNum = 4;							// 10%で90°	
							}
							else
							{
								m_ActionNum = 5;							// 10%で-90°
							}
						}
					}
				}

				DirectX::XMVECTOR move;

				switch (m_ActionNum)
				{
				case 1:
					// 回転処理(B)
					m_param.rot.y = DirectX::XMConvertToRadians(90.0f) - rot;

					// 移動方向設定
					move = direction;

					DirectX::XMStoreFloat3(&m_moveDirection, move);
					m_moveDirection.y = 0.0f;

					// スピード変更
					m_move = 0.05f;
					break;
				case 2:
					// 回転処理(B)
					m_param.rot.y = DirectX::XMConvertToRadians(135.0f) - rot;

					// 移動方向設定
					move = DirectX::XMVector3TransformCoord(direction, DirectX::XMMatrixRotationY(45.0f * 3.14f / 180.0f));
					DirectX::XMStoreFloat3(&m_moveDirection, move);
					m_moveDirection.y = 0.0f;

					// スピード変更
					m_move = 0.05f;
					break;
				case 3:
					// 回転処理(B)
					m_param.rot.y = DirectX::XMConvertToRadians(45.0f) - rot;

					// 移動方向設定
					move = DirectX::XMVector3TransformCoord(direction, DirectX::XMMatrixRotationY(-45.0f * 3.14f / 180.0f));
					DirectX::XMStoreFloat3(&m_moveDirection, move);
					m_moveDirection.y = 0.0f;

					// スピード変更
					m_move = 0.05f;
					break;
				case 4:
					// 回転処理(B)
					m_param.rot.y = DirectX::XMConvertToRadians(180.0f) - rot;

					// 移動方向設定
					move = DirectX::XMVector3TransformCoord(direction, DirectX::XMMatrixRotationY(90.0f * 3.14f / 180.0f));
					DirectX::XMStoreFloat3(&m_moveDirection, move);
					m_moveDirection.y = 0.0f;

					// スピード変更
					m_move = 0.05f;
					break;
				case 5:
					// 回転処理(B)
					m_param.rot.y = DirectX::XMConvertToRadians(0.0f) - rot;

					// 移動方向設定
					move = DirectX::XMVector3TransformCoord(direction, DirectX::XMMatrixRotationY(-90.0f * 3.14f / 180.0f));
					DirectX::XMStoreFloat3(&m_moveDirection, move);
					m_moveDirection.y = 0.0f;

					// スピード変更
					m_move = 0.05f;
					break;
				default:
					break;
				}

				m_param.frame = rand() % 3 * 50;
			}
		}
		// 移動
		m_param.pos.x += m_moveDirection.x * m_move; // エネミーのposを使う
		m_param.pos.z += m_moveDirection.z * m_move;
	}

	// 境界処理
	if (m_param.pos.x > 34.0f)
	{
		m_param.pos.x = 34.0f;
	}
	if (m_param.pos.x < -34.0f)
	{
		m_param.pos.x = -34.0f;
	}
	if (m_param.pos.z > 34.0f)
	{
		m_param.pos.z = 34.0f;
	}
	if (m_param.pos.z < -34.0f)
	{
		m_param.pos.z = -34.0f;
	}
}

// 死亡時に勝手に呼ばれます。
void CProtEnemy::Finalize()
{
	// マネージャに死んだことを伝える

}

void CProtEnemy::OnCollisionTag(EObjectTag tag)
{
	if (tag == TAG_BEAM || tag == TAG_PLAYER)
	{
		m_pEfk.reset(new CEffect(u"Assets/Effect/bakuhatu.efkefc"));
		m_pEfk->SetScale(m_param.scale.x, m_param.scale.y, m_param.scale.z);
		m_pEfk->SetPos(m_param.pos.x, m_param.pos.y, m_param.pos.z);
		m_pEfk->Play();
		m_data->MAX_cnt++;
		Destroy();
	}
	if (tag == TAG_SHOCK)
	{
		if (m_dontMove == false)
		{
			// 衝撃波に当たったら敵の移動を消す
			m_dontMove = true;

			// 吹っ飛ぶカウントを開始
			m_blowAwayCountDown = m_blowAwayCount;

			// カメラの向いてる方向を取得
			DirectX::XMStoreFloat3(&m_blowAwayMove, CCameraBase::GetFrontHorizontal("Player"));
		}
	}
}

void CProtEnemy::OnCollision(IObjectBase::Ptr obj)
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


