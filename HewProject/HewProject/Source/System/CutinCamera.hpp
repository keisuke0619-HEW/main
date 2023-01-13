#pragma once

#include <Camera.hpp>

class CCutinCamera : public CCameraBase
{
public:
	CCutinCamera();
	~CCutinCamera();

	void Update()override;
	void SetData(DirectX::XMFLOAT3 startpos,  DirectX::XMFLOAT3 endpos, DirectX::XMFLOAT3 startrad, DirectX::XMFLOAT3 endrad);
private:
	DirectX::XMFLOAT3 m_startPos;
	DirectX::XMFLOAT3 m_endPos;
	DirectX::XMFLOAT3 m_startRad;
	DirectX::XMFLOAT3 m_endRad;
	float m_step;
};