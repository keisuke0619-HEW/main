#pragma once
#include <DirectXMath.h>
#include "BaseClass/ObjectBase.hpp"
#include <OutputEffekseer.h>

class CBeam : public CObjectBase
{
public:
	CBeam(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 target, float size = 1.0f);
	~CBeam();

	void Update();
	void Draw();
	void Collision();
	void SetPlayerPos(DirectX::XMFLOAT3 playerpos);
private:
	float m_size;
	float m_maxSize;
	float m_time;
	DirectX::XMFLOAT3 m_playerPos;
	DirectX::XMFLOAT3 m_pos;
	DirectX::XMFLOAT3 m_target;

	float m_enemySize;
	DirectX::XMFLOAT3 m_enemyPos;
	DirectX::XMFLOAT3 m_enemyTarget;

	CEffect::Ptr m_pEfk;
	CEffect::Ptr m_pEfk2;

};