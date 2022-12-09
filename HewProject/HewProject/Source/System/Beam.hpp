#pragma once
#include <DirectXMath.h>
#include "BaseClass/ObjectBase.hpp"
class CBeam : public CObjectBase
{
public:
	CBeam(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 target, float size = 1.0f);
	~CBeam();

	void Update();
	void Draw();
	bool GetIsDestroy();
private:
	float m_size;
	float m_time;
	DirectX::XMFLOAT3 m_pos;
	DirectX::XMFLOAT3 m_target;


};