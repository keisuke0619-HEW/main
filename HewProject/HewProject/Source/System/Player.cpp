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
	auto camData = CCameraBase::GetPrimaryData();
	auto camPos = camData.pos;
	auto camLook = camData.look;
	camPos.y = 0;
	camLook.y = 0;
	auto vCamPos = DirectX::XMLoadFloat3(&camPos);
	auto vCamLook = DirectX::XMLoadFloat3(&camLook);

	DirectX::XMVECTOR vFront;
	vFront = DirectX::XMVectorSubtract(vCamPos, vCamLook);
	vFront = DirectX::XMVector3Normalize(vFront);

	auto matRotSide = DirectX::XMMatrixRotationY(3.14f / 180 * 90);
	auto vSide = DirectX::XMVector3TransformCoord(vFront, matRotSide);


	auto vMove = DirectX::XMVectorZero();
	if (IsKeyPress('W'))vMove = DirectX::XMVectorSubtract(vMove, vFront);
	if (IsKeyPress('S'))vMove = DirectX::XMVectorAdd(vMove, vFront);
	if (IsKeyPress('A'))vMove = DirectX::XMVectorAdd(vMove, vSide);
	if (IsKeyPress('D'))vMove = DirectX::XMVectorSubtract(vMove, vSide);

	// è„â∫èàóù
	DirectX::XMFLOAT3 up = { 0, 1, 0 };
	auto vUp = DirectX::XMLoadFloat3(&up);
	if (IsKeyPress(VK_SPACE))vMove = DirectX::XMVectorAdd(vMove, vUp);
	if (IsKeyPress(VK_SHIFT))vMove = DirectX::XMVectorSubtract(vMove, vUp);

	vMove = DirectX::XMVectorScale(vMove, MOVE_SPEED);


	DirectX::XMStoreFloat3(&m_param.move, vMove);
}


