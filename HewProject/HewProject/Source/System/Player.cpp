#include "Player.hpp"
#include <Input.h>
#include <Camera.hpp>

CPlayer::CPlayer()
	: CObjectBase("Assets/unitychan/unitychan.fbx", 0.01f)
{
	m_param.tag = TAG_PLAYER;
}

CPlayer::~CPlayer()
{
}

void CPlayer::Update()
{
	Move();
}

void CPlayer::Move()
{
	const float MOVE_SPEED = 0.1f;

	auto vFront = CCameraBase::GetPrimaryFrontHorizontal();
	auto vSide = CCameraBase::GetPrimaryRightHorizontal();
	auto vMove = DirectX::XMVectorZero();
	if (IsKeyPress('W'))vMove = DirectX::XMVectorAdd(vMove, vFront);
	if (IsKeyPress('S'))vMove = DirectX::XMVectorSubtract(vMove, vFront);
	if (IsKeyPress('A'))vMove = DirectX::XMVectorSubtract(vMove, vSide);
	if (IsKeyPress('D'))vMove = DirectX::XMVectorAdd(vMove, vSide);

	// è„â∫èàóù
	DirectX::XMFLOAT3 up = { 0, 1, 0 };
	auto vUp = DirectX::XMLoadFloat3(&up);
	if (IsKeyPress(VK_SPACE))vMove = DirectX::XMVectorAdd(vMove, vUp);
	if (IsKeyPress(VK_SHIFT))vMove = DirectX::XMVectorSubtract(vMove, vUp);
	vMove = DirectX::XMVectorScale(vMove, MOVE_SPEED);

	DirectX::XMStoreFloat3(&m_param.move, vMove);
}