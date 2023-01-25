#pragma once
#include <ObjectBase.hpp>
#include <IObjectBase.hpp>
#include <memory>

#include <Billboard.h>
#include<Polyline.h>
#include<PlayerCamera.hpp>
#include<Camera.hpp>
#include<Player.hpp>

#include <OutputEffekseer.h>
#include <ISceneBase.hpp>
class CProtEnemy : public CObjectBase
{
public:
	CProtEnemy(Data* data);
	~CProtEnemy();

	void Update() override;
	void Draw() override;
private:
	void Move();
	void Finalize() override;
	void OnCollisionTag(EObjectTag obj) override;
	void OnCollision(IObjectBase::Ptr obj) override;

	IObjectBase::Ref m_player;

	// moveに使う変数
	float m_move;		// エネミーの速度
	float m_distance;	// どのくらいプレイヤーとエネミーが近づいたら追尾するかの距離
	bool m_homing;		// 追尾中か

	int m_ActionNum;		//	移動乱数用の変数

	int m_cnt;			// ランダム移動で使う(移動する方向を変える間隔)
	int m_randNum;		// ランダム移動で使う(移動する方向を決める)
	bool m_dontMove;	// エネミーの動きを止める
	const int m_blowAwayCount = 20;	// 吹っ飛ぶ時間
	int m_blowAwayCountDown;		// 吹っ飛んでいる時間のカウント 
	DirectX::XMFLOAT3 m_target;
	DirectX::XMFLOAT3 m_randTarget;
	DirectX::XMFLOAT3 m_startPos;
	DirectX::XMFLOAT3 m_moveDirection;	// 移動方向
	DirectX::XMFLOAT3 m_blowAwayMove;	// 吹っ飛ぶ方向
	//GeometoryPolyline* m_pPolyline;
	CPlayer* m_pPlayer;
	CCameraBase*m_Pcamera;

	// クラス全体で使うモデルデータ
	static TModelData sModel;

	DirectX::XMFLOAT3 m_oldPos;

	CEffect::Ptr m_pEfk;
	Data* m_data;
};