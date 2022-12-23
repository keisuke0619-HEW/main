#include "Player.hpp"
#include <Camera.hpp>
#include <DebugWindow.hpp>
#include <Controller.hpp>
#include <Camera.hpp>
#include <SceneBase.hpp>
#include <Billboard.h>
#include <SceneManager.hpp>
CPlayer::CPlayer()
	: CObjectBase("Assets/Model/player.fbx", 0.08f, false, "Player")
	//: CObjectBase("Assets/unitychan/unitychan.fbx", 0.01f, false, "Player")
{
	m_param.tag = TAG_PLAYER;
	m_gra = 0;
	m_isGround = true;
	m_beamSize = 0;
	m_InvincibleTime = 0;
	m_param.collisionType = COLLISION_SPHIRE;
	m_param.collisionData.sphire.sphirePos = m_param.pos;
	m_param.collisionData.sphire.sphireRadius = m_param.scale.x / 2.0f;
	m_playerUI.reset(new CPlayerUI());
	Model::AnimeNo no = m_model->AddAnimation("Assets/unitychan/walk.fbx");
	if (no == Model::ANIME_NONE)
		MessageBox(nullptr, "walk.fbx", "Error", MB_OK);
	m_model->Play(no, true);

	// 音データの読み込み
	m_pChargeSE = CreateSound("Assets/Sound/Charge.wav", true);
	if (m_pChargeSE == nullptr)
	{

	}
	m_pBeamSE = CreateSound("Assets/Sound/Beam.wav", false);
	m_isSE = false;
	

}

CPlayer::~CPlayer()
{
}

void CPlayer::Update()
{
	Move();
	Beam();
	m_InvincibleTime--;
	//m_param.rot.y = CCameraBase::GetPrimaryRadXZ() + 3.14f;
	m_param.collisionData.sphire.sphirePos = m_param.pos;
	m_playerUI->Update();
	
	//if (IsKeyTrigger('U'))
	//	Destroy();
}

void CPlayer::Draw()
{
	auto param = m_param;
	m_param.pos.y += 1.0f;
	m_model->Step(1.0f / 60.0f);
	CObjectBase::Draw();
	//m_playerUI->Draw();
	//if(m_beam)
	//	m_beam->Draw();
	m_playerUI->SetLife(m_param.hp);
	m_param = param;
}

void CPlayer::Move()
{
	const float MOVE_SPEED = 0.1f;
	const float MOVE_GRAVITY = 0.05f;
	const float GRAVITY_MAX = 0.4f;
	auto vFront = CCameraBase::GetPrimaryFrontHorizontal();
	auto vSide = CCameraBase::GetPrimaryRightHorizontal();
	auto fGra = DirectX::XMFLOAT3(0, -m_gra, 0);
	auto vGra = DirectX::XMLoadFloat3(&fGra);
	auto vMove = DirectX::XMVectorZero();
	
	m_gra += m_gra < GRAVITY_MAX ? MOVE_GRAVITY : 0;

	if (Utility::GetKeyPress(Key_W))
		vMove = DirectX::XMVectorAdd(vMove, vFront);
	if (Utility::GetKeyPress(Key_S))
		vMove = DirectX::XMVectorSubtract(vMove, vFront);
	if (Utility::GetKeyPress(Key_A))
		vMove = DirectX::XMVectorSubtract(vMove, vSide);
	if (Utility::GetKeyPress(Key_D))
		vMove = DirectX::XMVectorAdd(vMove, vSide);
	vMove = DirectX::XMVector3Normalize(vMove);
	vMove = DirectX::XMVectorAdd(vMove, vGra);
	vFront = DirectX::XMVectorScale(vFront, Utility::GetStickLeft().y);
	vSide = DirectX::XMVectorScale(vSide, Utility::GetStickLeft().x);
	vMove = DirectX::XMVectorAdd(vMove, vFront);
	vMove = DirectX::XMVectorAdd(vMove, vSide);
#ifdef _DEBUG
	if (IsKeyPress(VK_CONTROL))
		vMove = DirectX::XMVectorScale(vMove, 5.0f);
#endif // _DEBUG

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

	// 疑似床当たり判定
	if (m_param.pos.y < 0.5f)
	{
		m_param.pos.y = 0.5f;
		m_param.move.y = 0;
		m_gra = 0;
		m_isGround = true;
	}
	if (m_isGround)
	{
		if (Utility::GetKeyPress(Key_SPACE))
		{
			m_gra = -2;
			m_isGround = false;
		}
		if (Utility::GetKeyPress(A))
		{
			m_gra = -2;
			m_isGround = false;
		}
	}

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
	if (Utility::GetKeyPress(RT) || Utility::GetKeyPress(Key_B))
	{
		m_beamSize += m_beamSize < maxBeamSize ? addBeamSize : 0;
		// se再生
		if (m_isSE == false)
		{
			m_pSESource = StartSound(m_pChargeSE);
			m_pSESource->SetVolume(0.3f);
			m_isSE = true;
		}
		
	}
	else
	{
		if (m_beamSize > 1.0f)
		{
			// とりあえず見ている方向に打つ
			DirectX::XMFLOAT3 CameraPos = CCameraBase::GetDataFromTag("Player").pos;
			DirectX::XMFLOAT3 CameraLook = CCameraBase::GetDataFromTag("Player").look;
			DirectX::XMVECTOR CameraRay = DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&CameraLook), DirectX::XMLoadFloat3(&CameraPos));
			CameraRay = DirectX::XMVectorScale(CameraRay, 2.0f);
			DirectX::XMStoreFloat3(&m_beamTarget,DirectX::XMVectorAdd(CameraRay, DirectX::XMLoadFloat3(&CameraLook)));
			m_beamTarget.y -= CameraPos.y - CameraLook.y;
			
			// ビーム生成
			auto beamPos = m_param.pos;
			beamPos.y += 1.0f;
			CSceneBase::GetObjList().lock()->Add(new CBeam(beamPos, m_beamTarget, m_beamSize));
			//m_beam.reset(new CBeam(m_param.pos, m_beamTarget, m_beamSize));
			// se再生
			if (m_isSE == true)
			{
				m_pSESource->Stop();
				m_pSESource = StartSound(m_pBeamSE);
				m_pSESource->SetVolume(0.3f);
				m_isSE = false;
			}
			
		}
		m_beamSize = 0.0f;
	}
	//if (m_beam)
	//{
	//	m_beam->Update();
	//}
}

void CPlayer::SetTarget(DirectX::XMFLOAT3 target)
{
	m_beamTarget = target;
}

void CPlayer::OnCollision(IObjectBase::Ptr obj)
{
	if (m_InvincibleTime < 0)
	{

		if (obj->GetParam().tag == TAG_ENEMY)
		{
			m_InvincibleTime = 120;

			m_param.hp -= 0.1f;
			if (m_param.hp <= 0.0f)
			{
				CSceneManager::SetScene(SCENE_RESULT);
				//Destroy();
			}
		}
	}
}
