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

	// move�Ɏg���ϐ�
	float m_move;		// �G�l�~�[�̑��x
	float m_distance;	// �ǂ̂��炢�v���C���[�ƃG�l�~�[���߂Â�����ǔ����邩�̋���
	bool m_homing;		// �ǔ�����

	int m_ActionNum;		//	�ړ������p�̕ϐ�

	int m_cnt;			// �����_���ړ��Ŏg��(�ړ����������ς���Ԋu)
	int m_randNum;		// �����_���ړ��Ŏg��(�ړ�������������߂�)
	bool m_dontMove;	// �G�l�~�[�̓������~�߂�
	const int m_blowAwayCount = 20;	// ������Ԏ���
	int m_blowAwayCountDown;		// �������ł��鎞�Ԃ̃J�E���g 
	DirectX::XMFLOAT3 m_target;
	DirectX::XMFLOAT3 m_randTarget;
	DirectX::XMFLOAT3 m_startPos;
	DirectX::XMFLOAT3 m_moveDirection;	// �ړ�����
	DirectX::XMFLOAT3 m_blowAwayMove;	// ������ԕ���
	//GeometoryPolyline* m_pPolyline;
	CPlayer* m_pPlayer;
	CCameraBase*m_Pcamera;

	// �N���X�S�̂Ŏg�����f���f�[�^
	static TModelData sModel;

	DirectX::XMFLOAT3 m_oldPos;

	CEffect::Ptr m_pEfk;
	Data* m_data;
};