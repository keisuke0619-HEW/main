#pragma once
#include <ObjectBase.hpp>
#include <IObjectBase.hpp>
#include <memory>

#include <Billboard.h>
#include "BossUI.h"

class CProtEnemyBoss : public CObjectBase
{
public:
	CProtEnemyBoss();
	~CProtEnemyBoss();

	void Update() override;
	void Draw() override;
private:
	void Move();
	void Finalize() override;
	void OnCollision(Ptr obj) override;
	void OnCollisionTag(EObjectTag tag);
	IObjectBase::Ref m_player;

	// moveに使う変数
	float m_move;		// エネミーの速度
	float m_distance;	// どのくらいプレイヤーとエネミーが近づいたら追尾するかの距離

	int m_cnt;			// ランダム移動で使う(移動する方向を変える間隔)
	int m_randNum;		// ランダム移動で使う(移動する方向を決める)
	DirectX::XMFLOAT3 m_target;
	DirectX::XMFLOAT3 m_randTarget;
	std::unique_ptr<CBossUI> m_bossUI;	// ボスのUI

};