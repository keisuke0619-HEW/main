#include "Player.hpp"
#include <Input.h>
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
	if (IsKeyTrigger('U'))
		Destroy();
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

	if (Utility::GetKeyPress(Utility::UP))
		vMove = DirectX::XMVectorAdd(vMove, vFront);
	if (Utility::GetKeyPress(Utility::DOWN))
		vMove = DirectX::XMVectorSubtract(vMove, vFront);
	if (Utility::GetKeyPress(Utility::LEFT))
		vMove = DirectX::XMVectorSubtract(vMove, vSide);
	if (Utility::GetKeyPress(Utility::RIGHT))
		vMove = DirectX::XMVectorAdd(vMove, vSide);

	if (Utility::GetKeyPress(Utility::Key_W))
		vMove = DirectX::XMVectorAdd(vMove, vFront);
	if (Utility::GetKeyPress(Utility::Key_S))
		vMove = DirectX::XMVectorSubtract(vMove, vFront);
	if (Utility::GetKeyPress(Utility::Key_A))
		vMove = DirectX::XMVectorSubtract(vMove, vSide);
	if (Utility::GetKeyPress(Utility::Key_D))
		vMove = DirectX::XMVectorAdd(vMove, vSide);
	/*if (IsKeyPress('W'))
		vMove = DirectX::XMVectorAdd(vMove, vFront);
	if (IsKeyPress('S'))
		vMove = DirectX::XMVectorSubtract(vMove, vFront);
	if (IsKeyPress('A'))
		vMove = DirectX::XMVectorSubtract(vMove, vSide);
	if (IsKeyPress('D'))
		vMove = DirectX::XMVectorAdd(vMove, vSide);*/

	if (IsKeyPress(VK_CONTROL))
		vMove = DirectX::XMVectorScale(vMove, 5.0f);
	// è„â∫èàóù
	DirectX::XMFLOAT3 up = { 0, 1, 0 };
	auto vUp = DirectX::XMLoadFloat3(&up);
	if (IsKeyPress(VK_SHIFT))vMove = DirectX::XMVectorSubtract(vMove, vUp);
	vMove = DirectX::XMVectorScale(vMove, MOVE_SPEED);

	DirectX::XMStoreFloat3(&m_param.move, vMove);

	// ã^éóè∞ìñÇΩÇËîªíË
	if (m_param.pos.y < 0.5f)
	{
		m_param.pos.y = 0.5f;
		m_param.move.y = 0;
		m_gra = 0;
		CDebugWindow::Print(ShimizuKeisuke, "param", m_param.frame);
		m_isGround = true;
	}
	if (m_isGround)
	{
		if (IsKeyTrigger(VK_SPACE))m_gra = -2;
		m_isGround = false;
	}

}