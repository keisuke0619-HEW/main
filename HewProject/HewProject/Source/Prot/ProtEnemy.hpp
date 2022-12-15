#pragma once
#include <ObjectBase.hpp>
#include <IObjectBase.hpp>
#include <memory>

#include <Billboard.h>

class CProtEnemy : public CObjectBase
{
public:
	CProtEnemy();
	~CProtEnemy();

	void Update() override;
	void Draw() override;
private:
	void Move();
	void Finalize() override;
	void OnCollisionTag(EObjectTag obj) override;

	IObjectBase::Ref m_player;

	// moveに使う変数
	float m_move;		// エネミーの速度
	float m_distance;	// どのくらいプレイヤーとエネミーが近づいたら追尾するかの距離

	int m_cnt;			// ランダム移動で使う(移動する方向を変える間隔)
	int m_randNum;		// ランダム移動で使う(移動する方向を決める)
	bool m_dontMove;	// エネミーの動きを止める
	const int m_blowAwayCount = 2;	// 吹っ飛ぶ時間
	int m_blowAwayCountDown;		// 吹っ飛んでいる時間のカウント 
	DirectX::XMFLOAT3 m_target;
	DirectX::XMFLOAT3 m_randTarget;
	DirectX::XMFLOAT3 m_startPos;
	DirectX::XMFLOAT3 m_blowAwayMove;	// 吹っ飛ぶ方向

	CBillboard* m_bill;
};