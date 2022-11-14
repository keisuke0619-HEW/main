#pragma once
#include <DirectXMath.h>
class CCameraBase
{
public:
	CCameraBase();
	virtual ~CCameraBase();
	
	virtual void Update() = 0;
	DirectX::XMFLOAT4X4 GetViewMatrix();
	DirectX::XMFLOAT4X4 GetProjectionMatrix();
	DirectX::XMFLOAT3 GetPos();
	DirectX::XMFLOAT3 GetLook();

protected:
	DirectX::XMFLOAT3 m_pos;
	DirectX::XMFLOAT3 m_look;
	float m_distance;
	float m_radXZ;
	float m_radY;
	DirectX::XMFLOAT3 m_up;
	float m_fovY;
	float m_aspect;
	float m_near;
	float m_far;
};