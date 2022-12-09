#include "Beam.hpp"
#include <Geometory.h>
#include <DebugWindow.hpp>
CBeam::CBeam(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 target, float size)
	: CObjectBase("Assets/Box.fbx")
{
	m_pos = pos;
	m_target = target;
	m_size = size;
}

CBeam::~CBeam()
{
}

void CBeam::Update()
{
}

void CBeam::Draw()
{
	// 発射起点がm_posに、ターゲット座標がm_targetに入っています。
	// それらの変数から軸の回転を求めてrotにぶち込んでください。
	DirectX::XMFLOAT3 rot = {};

	// よくわかんないやつ

	//DirectX::XMVECTOR vPos = DirectX::XMLoadFloat3(&m_pos);
	//DirectX::XMVECTOR vTarget = DirectX::XMLoadFloat3(&m_target);

	//DirectX::XMVECTOR vPosToTarget = DirectX::XMVectorSubtract(vTarget, vPos);

	//DirectX::XMFLOAT3 PosToTarget;

	//DirectX::XMStoreFloat3(&PosToTarget, vPosToTarget);

	//
	//DirectX::XMFLOAT3 base = PosToTarget;

	//
	//
	////base.x = 0.f;

	//base.y = 0.f;
	//base.z = 0.f;
	//
	//DirectX::XMVECTOR vBase = DirectX::XMLoadFloat3(&base);

	//vPosToTarget = DirectX::XMVector3Normalize(vPosToTarget);
	//vBase = DirectX::XMVector3Normalize(vBase);

	//DirectX::XMStoreFloat(&rot.x, DirectX::XMVector3Dot(vPosToTarget, vBase));

	//
	//base = PosToTarget;

	//
	//base.x = 0.f;
	////base.y = 0.f;
	//base.z = 0.f;
	//
	//vBase = DirectX::XMLoadFloat3(&base);
	//vBase = DirectX::XMVector3Normalize(vBase);

	//DirectX::XMStoreFloat(&rot.y, DirectX::XMVector3Dot(vPosToTarget, vBase));

	//
	//base = PosToTarget;

	//
	//base.x = 0.f;
	//base.y = 0.f;
	////base.z = 0.f;


	// へんなやつ
	//vBase = DirectX::XMLoadFloat3(&base);
	//vBase = DirectX::XMVector3Normalize(vBase);

	//DirectX::XMStoreFloat(&rot.z, DirectX::XMVector3Dot(vPosToTarget, vBase));
	//
	//rot.x = acosf(rot.x);
	//rot.y = acosf(rot.y);
	//rot.z = acosf(rot.z);
	
	/*DirectX::XMVECTOR vPos = DirectX::XMLoadFloat3(&m_pos);
	DirectX::XMVECTOR vTarget = DirectX::XMLoadFloat3(&m_target);

	DirectX::XMFLOAT3 vx = { 1.f, 0.f, 0.f };
	DirectX::XMFLOAT3 vy = { 0.f, 1.f, 0.f };
	DirectX::XMFLOAT3 vz = { 0.f, 0.f, 1.f };

	DirectX::XMVECTOR vPosToTarget = DirectX::XMVectorSubtract(vTarget, vPos);
	DirectX::XMVECTOR vNormal = DirectX::XMLoadFloat3(&vx);

	vNormal = DirectX::XMVector3Normalize(vNormal);
	vNormal = DirectX::XMVector3Dot(vNormal, vPosToTarget);

	DirectX::XMVECTOR vDot= DirectX::XMVector3Normalize(vPosToTarget);


	
	vNormal = DirectX::XMVector3Normalize(vNormal);
	DirectX::XMStoreFloat(&rot.x, DirectX::XMVector3Dot(vDot, vNormal));
	

	vNormal = DirectX::XMLoadFloat3(&vy);

	vNormal = DirectX::XMVector3Normalize(vNormal);
	vNormal = DirectX::XMVector3Dot(vNormal, vPosToTarget);

	

	vDot = DirectX::XMVector3Normalize(vPosToTarget);

	vNormal = DirectX::XMVector3Normalize(vNormal);
	DirectX::XMStoreFloat(&rot.y, DirectX::XMVector3Dot(vDot, vNormal));

	vNormal = DirectX::XMLoadFloat3(&vy);

	vNormal = DirectX::XMVector3Normalize(vNormal);
	vNormal = DirectX::XMVector3Dot(vNormal, vPosToTarget);

	

	vDot = DirectX::XMVector3Normalize(vPosToTarget);

	vNormal = DirectX::XMVector3Normalize(vNormal);
	DirectX::XMStoreFloat(&rot.z, DirectX::XMVector3Dot(vDot, vNormal));
	rot.x = acosf(rot.x);
	rot.y = acosf(rot.y);
	rot.z = acosf(rot.z);*/

	// ai
	
	/*DirectX::XMFLOAT3 vPos;
	vPos.x = m_pos.x / sqrtf(powf(m_pos.x, 2) + powf(m_pos.y, 2) + powf(m_pos.z, 2));
	vPos.y = m_pos.y / sqrtf(powf(m_pos.x, 2) + powf(m_pos.y, 2) + powf(m_pos.z, 2));
	vPos.z = m_pos.z / sqrtf(powf(m_pos.x, 2) + powf(m_pos.y, 2) + powf(m_pos.z, 2));
	rot.x = atan2f(vPos.y, vPos.z);
	rot.y = atan2f(vPos.z, vPos.x);
	rot.z = atan2f(vPos.x, vPos.y);*/


	// ヤバ計算式
	/*rot.x = -((m_target.z * m_target.z) - (m_pos.x * m_pos.x) - (m_target.x * m_target.x) + (m_pos.z * m_pos.z)) /
		2 * m_target.x * sqrtf((m_target.x * m_target.x) + (m_pos.z * m_pos.z));

	rot.y = -(((m_target.y * m_target.y) - ((m_pos.x * m_pos.x) + (m_target.z * m_target.z)) -
		((m_pos.x * m_pos.x) + (m_target.z * m_target.z) + (m_pos.y * m_pos.y))) /
		2 * sqrtf((m_target.x * m_target.x) + (m_target.z * m_target.z)) * sqrtf((m_target.x * m_target.x) + (m_target.z * m_target.z) + (m_target.y * m_target.y)));

	rot.z = -((m_target.y * m_target.y) - (m_pos.z * m_pos.z) - ((m_pos.y * m_pos.y) + (m_target.z * m_target.z))) /
		2 * m_target.z * sqrtf((m_pos.y * m_pos.y) + (m_target.z * m_target.z));*/
		

	SetGeometoryTranslate(m_pos.x, m_pos.y, m_pos.z);
	SetGeometoryRotation(rot.x, rot.y, rot.z);
	SetGeometoryScaling(m_size, 10000, m_size);



	DrawCapsule();
}

bool CBeam::GetIsDestroy()
{
	return m_time <= 0.0f;
}
