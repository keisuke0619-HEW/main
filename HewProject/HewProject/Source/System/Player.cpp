#include "Player.hpp"
#include <Camera.hpp>
#include <DebugWindow.hpp>
#include <Controller.hpp>
#include <Camera.hpp>
#include <SceneBase.hpp>
#include <Billboard.h>
#include <SceneManager.hpp>
#include <CutinCamera.hpp>
#include <PlayerCamera.hpp>
#include <SceneResult.hpp>

CPlayer::CPlayer(Data* data)
	: CObjectBase("Assets/Model/player.fbx", 0.08f, false, "Player")
{
	m_param.tag = TAG_PLAYER;
	m_gra = 0;
	m_isGround = true;
	m_beamSize = 0;
	m_isBeamStore = false;
	m_InvincibleTime = 0;
	m_isCancel = false;
	m_CancelTime = 0;
	m_Fream = 0;

	// ここで描画をずらす
	m_param.drawOffset = { 0, 0, 0 };

	// 当たり判定の設定
	m_param.collisionType = COLLISION_CHARACTER;
	m_param.collisionData.character.pos = m_param.pos;
	m_param.collisionData.character.pos.y += m_param.drawOffset.y + 0.1f;
	m_param.collisionData.character.radius = 0.2f;

	m_playerUI.reset(new CPlayerUI());
	Model::AnimeNo no = m_modelData.model->AddAnimation("Assets/unitychan/walk.fbx");
	if (no == Model::ANIME_NONE)
		MessageBox(nullptr, "walk.fbx", "Error", MB_OK);
	m_modelData.model->Play(no, true);

	// 音データの読み込み
	m_pChargeSE = CreateSound("Assets/Sound/Charge.wav", false);
	if (m_pChargeSE == nullptr)
	{

	}
	m_pBeamSE = CreateSound("Assets/Sound/Beam.wav", false);
	m_isSE = false;
	

	m_bill.reset(new CBillboard("Assets/Img/number.png"));
	m_bill->SetSize({ 2.0f, 0.25f });

	m_isChargeContinue = false;
	m_ChargeTime = 0;
	m_pEfk.reset(new CEffect(u"Assets/Effect/Beamtame.efkefc"));
	m_pEfk2.reset(new CEffect(u"Assets/Effect/damage.efkefc"));
	m_pEfk3.reset(new CEffect(u"Assets/Effect/zirai.efkefc"));

	m_data = data;
}

CPlayer::~CPlayer()
{
}

void CPlayer::Update()
{
	m_oldPos = m_param.pos;
	

	if (m_isCancel == false)
	{
		Move();
		Beam();
		m_playerUI->SetReticleAlpha(1);
	}
	else
	{
		CancelMove();
		m_playerUI->SetReticleAlpha(0);
	}
	m_InvincibleTime--;

	if (m_InvincibleTime < 0)
	{
		m_pEfk2->End();
	}
	AddVector3(m_param.move, m_param.accel);
	AddVector3(m_param.pos, m_param.move);

	// 当たり判定の更新
	m_param.collisionData.character.pos = m_param.pos;
	m_param.collisionData.character.pos.y += m_param.drawOffset.y + 0.1f;

	m_playerUI->Update();

	m_bill->SetPos({ m_param.pos.x, m_param.pos.y + 100.0f, m_param.pos.z });
	m_bill->SetPosViewProj(CCameraBase::GetPrimaryViewMatrix(), CCameraBase::GetPrimaryProjectionMatrix());
	//if (IsKeyTrigger('U'))
	//	Destroy();

	//m_param.hp = 1;

	m_pEfk->SetScale(m_param.scale.x, m_param.scale.y, m_param.scale.z);
	m_pEfk->SetPos(m_param.pos.x, m_param.pos.y, m_param.pos.z);
	m_pEfk->SetRotation(m_param.rot.x, m_param.rot.y, m_param.rot.z);
	m_pEfk->AddPos(m_param.pos.x, m_param.pos.y, m_param.pos.z);

	if (m_param.hp <= 0.0f)
	{
		m_Fream++;
	
		m_pEfk3->SetScale(1.0f, 1.0f, 1.0f);
		m_pEfk3->SetPos(m_param.pos.x, m_param.pos.y, m_param.pos.z);
		m_pEfk3->PlayOnce();
		if (m_Fream >= 180)
		{
			CSceneResult::SetOver();
			CSceneManager::SetScene(SCENE_RESULT);
			Destroy();
		}
	}
	else
	{

	}
}

void CPlayer::Draw()
{
	
	m_modelData.model->Step(1.0f / 60.0f);
	if (m_InvincibleTime > 0 && m_InvincibleTime % 30 < 10)
	{
		// 被ダメージ時点滅処理
	}
	else
	{
		CObjectBase::Draw();
	}
	
	//m_playerUI->Draw();
	//if(m_beam)
	//	m_beam->Draw();
	m_playerUI->SetLife(m_param.hp);
	
	// チャージし始めて最初に入る
	if (m_isBeamStore == true && m_isChargeContinue == false)
	{
		m_pEfk->PlayOnce();
		m_ChargeTime++;
	}
	// チャージしてから一定時間経過後入る
	if (m_ChargeTime >= 100)
	{
		m_isChargeContinue = true;
		m_pEfk->End();					// 今まで出していたエフェクトを終了
		m_pEfk->ContinuePlay(30.0f);	// 途中からエフェクトを描画
		m_ChargeTime = 0;
	}
	// チャージ満タン状態の時に入る
	if (m_isChargeContinue == true)
	{
		m_ChargeTime++;
		// 途中から描画していたエフェクトが終わる前に入る
		if (m_ChargeTime >= 60)
		{
			m_pEfk->End();
			m_pEfk->ContinuePlay(30.0f);
			m_ChargeTime = 0;
		}
	}
}

void CPlayer::Move()
{
	const float MOVE_SPEED = 0.1f;
	const float MOVE_GRAVITY = 0.05f;
	const float GRAVITY_MAX = 0.4f * 1.4f;
	auto vFront = CCameraBase::GetPrimaryFrontHorizontal();
	auto vSide = CCameraBase::GetPrimaryRightHorizontal();
	//auto fGra = DirectX::XMFLOAT3(0, -m_gra, 0);
	//auto vGra = DirectX::XMLoadFloat3(&fGra);
	auto vMove = DirectX::XMVectorZero();
	
	m_gra += m_gra < GRAVITY_MAX ? MOVE_GRAVITY : 0;

	if (Utility::GetKeyPress(KEY_MOVE_W))
		vMove = DirectX::XMVectorAdd(vMove, vFront);
	if (Utility::GetKeyPress(KEY_MOVE_S))
		vMove = DirectX::XMVectorSubtract(vMove, vFront);
	if (Utility::GetKeyPress(KEY_MOVE_A))
		vMove = DirectX::XMVectorSubtract(vMove, vSide);
	if (Utility::GetKeyPress(KEY_MOVE_D))
		vMove = DirectX::XMVectorAdd(vMove, vSide);
	vMove = DirectX::XMVector3Normalize(vMove);
	//vMove = DirectX::XMVectorAdd(vMove, vGra);
	vFront = DirectX::XMVectorScale(vFront, Utility::GetStickLeft().y);
	vSide = DirectX::XMVectorScale(vSide, Utility::GetStickLeft().x);
	vMove = DirectX::XMVectorAdd(vMove, vFront);
	vMove = DirectX::XMVectorAdd(vMove, vSide);

	// 上下処理
	DirectX::XMFLOAT3 up = { 0, 1, 0 };
	auto vUp = DirectX::XMLoadFloat3(&up);

	// 回転処理
	DirectX::XMFLOAT3 Move;
	DirectX::XMStoreFloat3(&Move, vMove);
	Move.y = 0.0f;
	
	if (fabsf(Move.x) + fabsf(Move.z) > 0.0f)
	{
		float rot = atan2f(Move.z, Move.x);
		m_param.rot.y = (90.0f * 3.14159f / 180.0f) - rot;
	}

	vMove = DirectX::XMVectorScale(vMove, MOVE_SPEED);

	DirectX::XMStoreFloat3(&m_param.move, vMove);
	KnockBack();
	m_param.move.y -= m_gra * 0.1f;

	// 疑似床当たり判定
	if (m_param.pos.y < 0.0f)
	{
		m_param.pos.y = 0.0f;
		m_param.move.y = 0;
		m_gra = 0;
		m_isGround = true;
	}
	if (m_isGround)
	{
		if (Utility::GetKeyPress(KEY_JUMP))
		{
			m_gra = -1.4;
			m_isGround = false;
		}
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

void CPlayer::Beam()
{
	const float maxBeamSize = 3.0f;
	const float addBeamSize = 0.025f;
	
	m_playerUI->SetCharge(m_beamSize / maxBeamSize);
	// RTに変更
	if (Utility::GetKeyPress(KEY_BEAM))
	{		
		m_isBeamStore = true;

		m_beamSize += m_beamSize < maxBeamSize ? addBeamSize : 0;
		// se再生
		if (m_isSE == false)
		{
			m_pSESource = StartSound(m_pChargeSE);
			// 音量
			m_pSESource->SetVolume(0.3f);
			// 再生スピード
			m_pSESource->SetFrequencyRatio(1.f);
			// 再生したか判定
			m_isSE = true;
		}
		
	}
	else
	{
		m_isBeamStore = false;
		m_isChargeContinue = false;
		m_ChargeTime = 0;
		m_pEfk->End();
		CCutinCamera::SetCutinBlur();

		if (m_beamSize > 1.0f)
		{
			// とりあえず見ている方向に打つ
			DirectX::XMFLOAT3 CameraPos = CCameraBase::GetDataFromTag("Player").pos;
			DirectX::XMFLOAT3 CameraLook = CCameraBase::GetDataFromTag("Player").look;

			auto beam = new CBeam(CameraPos, CameraLook, m_beamSize, m_data);
			beam->SetPlayerPos(m_param.pos);
			CSceneBase::GetObjList().lock()->Add(beam);
			

			// se再生
			if (m_isSE == true)
			{
				// チャージ音を止める
				m_pSESource->Stop();
				m_pSESource = StartSound(m_pBeamSE);
				// 音量
				m_pSESource->SetVolume(0.3f);
				// 再生スピード
				m_pSESource->SetFrequencyRatio(1.f);
				// 再生判定
				m_isSE = false;
			}
			
			// プレイヤーを硬直
			m_isCancel = true;
			DirectX::XMFLOAT3 Front;
			DirectX::XMStoreFloat3(&Front, CCameraBase::GetFrontHorizontal("Player"));
			float rot = (90.0f * 3.14159f / 180.0f) - atan2f(Front.z, Front.x);
			auto cutin = new CCutinCamera();
			cutin->SetData(m_param.pos, CCameraBase::GetDataFromTag("Player").look , rot);
			CCameraBase::CreateCamera(cutin, "Cutin");
			CCameraBase::SetPrimaryCamera("Cutin");
		}
		else
		{
			// 一定以下のチャージの時でやめたときにもチャージ音が消えるようにする
			if (m_isSE == true)
			{
				m_pSESource->Stop();
				m_isSE = false;
			}
		}
		m_beamSize = 0.0f;
	}
	
}

void CPlayer::CancelMove()
{
	if (m_CancelTime < 60)
	{
		m_CancelTime++;
		// プレイヤーの動きを止める
		m_param.move = { 0.0f, 0.0f, 0.0f }; 
		m_gra = 0;
		DirectX::XMFLOAT3 Front;
		DirectX::XMStoreFloat3(&Front, CCameraBase::GetFrontHorizontal("Player"));
		// プレイヤーの視点をカメラと同じにする
		m_param.rot.y = (90.0f * 3.14159f / 180.0f) - atan2f(Front.z, Front.x);
		
	}
	else
	{
		m_CancelTime = 0;
		m_isCancel = false;
		CCameraBase::SetPrimaryCamera("Player");	// カメラ戻す
		CCameraBase::DeleteCamera("Cutin");			// カットインカメラ削除s
	}
}

void CPlayer::KnockBack()
{
	if (m_knockBackFrame > 0)
	{
		DirectX::XMFLOAT3 fKnock;
		DirectX::XMStoreFloat3(&fKnock, m_vKnockBack);
		m_vKnockBack = DirectX::XMVectorScale(m_vKnockBack, 0.8f);
		m_param.move = fKnock;
	}
	m_knockBackFrame--;
}

void CPlayer::SetTarget(DirectX::XMFLOAT3 target)
{
	m_beamTarget = target;
}

void CPlayer::OnCollision(IObjectBase::Ptr obj)
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
		if (m_InvincibleTime < 0)
		{
			m_pEfk2->SetScale(m_param.scale.x / 2, m_param.scale.y / 2, m_param.scale.z / 2);
			m_pEfk2->SetPos(m_param.pos.x, m_param.pos.y + 1.0f, m_param.pos.z);
			m_pEfk2->SetRotation(m_param.rot.x, m_param.rot.y, m_param.rot.z);
			m_pEfk2->PlayOnce();

			m_InvincibleTime = 120;

			m_param.hp -= 0.18f;

			// ノックバック
			const float knockBackPower = 0.6f;
			const int knockBackFrame = 30;
			DirectX::XMFLOAT3 Enemypos = obj->GetParam().pos;
			DirectX::XMVECTOR vEnemy = DirectX::XMLoadFloat3(&Enemypos);
			auto pos = m_param.pos;
			pos.y += 0.5f;
			DirectX::XMVECTOR vPos = DirectX::XMLoadFloat3(&pos);

			m_vKnockBack = DirectX::XMVectorSubtract(vPos, vEnemy);
			DirectX::XMVector3Normalize(m_vKnockBack);

			m_vKnockBack = DirectX::XMVectorScale(m_vKnockBack, knockBackPower);
			m_knockBackFrame = knockBackFrame;
			
			if (!(m_param.hp <= 0.0f))
			{
				CPlayerCamera::SetBlur();
			}
		}
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