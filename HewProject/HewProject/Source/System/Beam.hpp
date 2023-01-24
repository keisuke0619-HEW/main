#pragma once
#include <DirectXMath.h>
#include "BaseClass/ObjectBase.hpp"
#include <OutputEffekseer.h>
#include <ISceneBase.hpp>

class CBeam : public CObjectBase
{
public:
	CBeam(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 target, float size,Data* data);
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

	Data* m_data;
	int m_killCnt;
};