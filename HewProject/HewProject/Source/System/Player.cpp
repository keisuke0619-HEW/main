#include "Player.hpp"
#include <Camera.hpp>
#include <DebugWindow.hpp>
#include <Controller.hpp>
#include <Camera.hpp>
#include <SceneBase.hpp>
#include <Billboard.h>
CPlayer::CPlayer()
	: CObjectBase("Assets/unitychan/unitychan.fbx", 0.01f, false, "Player")
{
	m_param.tag = TAG_PLAYER;
	m_gra = 0;
	m_isGround = true;
	m_beamSize = 0;
	m_param.collisionType = COLLISION_SPHIRE;
	m_param.collisionData.sphire.sphirePos = m_param.pos;
	m_param.collisionData.sphire.sphireRadius = m_param.scale.x / 2.0f;
	m_playerUI.reset(new CPlayerUI());
}

CPlayer::~CPlayer()
{
}

void CPlayer::Update()
{
	Move();
	Beam();
	//m_param.rot.y = CCameraBase::GetPrimaryRadXZ() + 3.14f;
	m_param.collisionData.sphire.sphirePos = m_param.pos;
	m_playerUI->Update();
	//if (IsKeyTrigger('U'))
	//	Destroy();
}

void CPlayer::Draw()
{
	CObjectBase::Draw();
	//m_playerUI->Draw();
	//if(m_beam)
	//	m_beam->Draw();
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
	// ã‰ºˆ—
	DirectX::XMFLOAT3 up = { 0, 1, 0 };
	auto vUp = DirectX::XMLoadFloat3(&up);
	vMove = DirectX::XMVectorScale(vMove, MOVE_SPEED);

	DirectX::XMStoreFloat3(&m_param.move, vMove);

	// ‹^Ž—°“–‚½‚è”»’è
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
}

void CPlayer::Beam()
{
	const float maxBeamSize = 3.0f;
	const float addBeamSize = 0.05f;
	// RT‚É•ÏX
	if (Utility::GetKeyPress(RT) || Utility::GetKeyPress(Key_B))
	{
		m_beamSize += m_beamSize < maxBeamSize ? addBeamSize : 0;
	}
	else
	{
		if (m_beamSize > 1.0f)
		{
			// ‚Æ‚è‚ ‚¦‚¸Œ©‚Ä‚¢‚é•ûŒü‚É‘Å‚Â
			DirectX::XMFLOAT3 CameraPos = CCameraBase::GetDataFromTag("Player").pos;
			DirectX::XMFLOAT3 CameraLook = CCameraBase::GetDataFromTag("Player").look;
			DirectX::XMVECTOR CameraRay = DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&CameraLook), DirectX::XMLoadFloat3(&CameraPos));
			CameraRay = DirectX::XMVectorScale(CameraRay, 2.0f);
			DirectX::XMStoreFloat3(&m_beamTarget,DirectX::XMVectorAdd(CameraRay, DirectX::XMLoadFloat3(&CameraLook)));
			m_beamTarget.y -= CameraPos.y - CameraLook.y;
			
			// ƒr[ƒ€¶¬
			auto beamPos = m_param.pos;
			beamPos.y += 1.0f;
			CSceneBase::GetObjList().lock()->Add(new CBeam(beamPos, m_beamTarget, m_beamSize));
			//m_beam.reset(new CBeam(m_param.pos, m_beamTarget, m_beamSize));
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
