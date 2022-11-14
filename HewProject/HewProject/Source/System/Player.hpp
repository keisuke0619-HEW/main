#pragma once
#include <Camera.hpp>
#include <Model.h>
#include <ConstantBuffer.h>
#include <memory>
class CPlayer
{
public:
	CPlayer();
	~CPlayer();
	void Update();
	void Draw();

	void SetCamera(CCameraBase* pCam);
	DirectX::XMFLOAT3 GetPos();

private:
	DirectX::XMFLOAT3 m_pos;
	CCameraBase *m_cam;
	std::unique_ptr<Model> m_model;
	std::unique_ptr<VertexShader> m_vs;
	std::unique_ptr<ConstantBuffer> m_wvp;
};