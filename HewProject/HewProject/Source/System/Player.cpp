#include "Player.hpp"
#include <Input.h>
#include <Camera.hpp>
#include <DebugWindow.hpp>
#include <Controller.hpp>
CPlayer::CPlayer()
	: CObjectBase("Assets/unitychan/unitychan.fbx", 0.01f, false, "Player")
{
	m_param.tag = TAG_PLAYER;
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

	auto vFront = CCameraBase::GetPrimaryFrontHorizontal();
	auto vSide = CCameraBase::GetPrimaryRightHorizontal();
	auto vMove = DirectX::XMVectorZero();
	if (Controller::GetKeyPress(Controller::UP))vMove = DirectX::XMVectorAdd(vMove, vFront);
	if (Controller::GetKeyPress(Controller::DOWN))vMove = DirectX::XMVectorSubtract(vMove, vFront);
	if (Controller::GetKeyPress(Controller::LEFT))vMove = DirectX::XMVectorSubtract(vMove, vSide);
	if (Controller::GetKeyPress(Controller::RIGHT))vMove = DirectX::XMVectorAdd(vMove, vSide);

	if (IsKeyPress(VK_CONTROL))
		vMove = DirectX::XMVectorScale(vMove, 5.0f);
	// è„â∫èàóù
	DirectX::XMFLOAT3 up = { 0, 1, 0 };
	auto vUp = DirectX::XMLoadFloat3(&up);
	if (IsKeyPress(VK_SPACE))vMove = DirectX::XMVectorAdd(vMove, vUp);
	if (IsKeyPress(VK_SHIFT))vMove = DirectX::XMVectorSubtract(vMove, vUp);
	vMove = DirectX::XMVectorScale(vMove, MOVE_SPEED);

	DirectX::XMStoreFloat3(&m_param.move, vMove);
}