#include "Player.hpp"
#include <Camera.hpp>
#include <DebugWindow.hpp>
#include <Controller.hpp>
CPlayer::CPlayer()
	: CObjectBase("Assets/unitychan/unitychan.fbx", 0.01f, false, "Player")
{
	m_param.tag = TAG_PLAYER;
	m_gra = 0;
	m_isGround = true;
}

CPlayer::~CPlayer()
{
}

void CPlayer::Update()
{
	Move();
	m_param.rot.y = CCameraBase::GetPrimaryRadXZ() + 3.14f;
	//if (IsKeyTrigger('U'))
	//	Destroy();
}

void CPlayer::Move()
{
	const float MOVE_SPEED = 0.1f;
	const float MOVE_GRAVITY = 0.05f;

	auto vFront = CCameraBase::GetPrimaryFrontHorizontal();
	auto vSide = CCameraBase::GetPrimaryRightHorizontal();
	auto fGra = DirectX::XMFLOAT3(0, -m_gra, 0);
	auto vGra = DirectX::XMLoadFloat3(&fGra);
	auto vMove = DirectX::XMVectorZero();
	
	m_gra += MOVE_GRAVITY;
	vMove = DirectX::XMVectorAdd(vMove, vGra);
	if (Utility::GetKeyPress(Utility::Key_W))
		vMove = DirectX::XMVectorAdd(vMove, vFront);
	if (Utility::GetKeyPress(Utility::Key_S))
		vMove = DirectX::XMVectorSubtract(vMove, vFront);
	if (Utility::GetKeyPress(Utility::Key_A))
		vMove = DirectX::XMVectorSubtract(vMove, vSide);
	if (Utility::GetKeyPress(Utility::Key_D))
		vMove = DirectX::XMVectorAdd(vMove, vSide);
	vFront = DirectX::XMVectorScale(vFront, Utility::GetStickLeft().y);
	vSide = DirectX::XMVectorScale(vSide, Utility::GetStickLeft().x);
	vMove = DirectX::XMVectorAdd(vMove, vFront);
	vMove = DirectX::XMVectorAdd(vMove, vSide);
#ifdef _DEBUG
	if (IsKeyPress(VK_CONTROL))
		vMove = DirectX::XMVectorScale(vMove, 5.0f);
#endif // _DEBUG
	// è„â∫èàóù
	DirectX::XMFLOAT3 up = { 0, 1, 0 };
	auto vUp = DirectX::XMLoadFloat3(&up);
	vMove = DirectX::XMVectorScale(vMove, MOVE_SPEED);

	DirectX::XMStoreFloat3(&m_param.move, vMove);

	// ã^éóè∞ìñÇΩÇËîªíË
	if (m_param.pos.y < 0.5f)
	{
		m_param.pos.y = 0.5f;
		m_param.move.y = 0;
		m_gra = 0;
		m_isGround = true;
	}
	if (m_isGround)
	{
#ifdef _USE_KEYBOARD_
		if (IsKeyPress(VK_SPACE))
		{
			m_gra = -2;
			m_isGround = false;
		}
#endif // _USE_KEYBOARD_
		if (Utility::GetKeyPress(Utility::A))
		{
			m_gra = -2;
			m_isGround = false;
		}
	}
}