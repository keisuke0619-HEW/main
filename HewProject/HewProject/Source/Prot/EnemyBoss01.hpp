#pragma once
#include <ObjectBase.hpp>
#include <IObjectBase.hpp>
#include <memory>

#include <Billboard.h>
#include "BossUI.h"
#include <ISceneBase.hpp>

#include <OutputEffekseer.h>

class CProtEnemyBoss : public CObjectBase
{
public:
	CProtEnemyBoss(Data* data, float bossHP);
	~CProtEnemyBoss();

	void Update() override;
	void Draw() override;
private:
	void Move();
	void Finalize() override;
	void OnCollision(Ptr obj) override;
	void OnCollisionTag(EObjectTag tag);
	IObjectBase::Ref m_player;
	int m_Fream;	// シーン遷移用の時間

	// moveに使う変数
	float m_move;		// エネミーの速度
	float m_distance;	// どのくらいプレイヤーとエネミーが近づいたら追尾するかの距離

	int m_cnt;			// ランダム移動で使う(移動する方向を変える間隔)
	int m_randNum;		// ランダム移動で使う(移動する方向を決める)
	DirectX::XMFLOAT3 m_target;
	DirectX::XMFLOAT3 m_randTarget;
	std::unique_ptr<CBossUI> m_bossUI;	// ボスのUI

	DirectX::XMFLOAT3 m_oldPos;
	Data* m_data;

	float m_HP;

	CEffect::Ptr m_pEfk;
};