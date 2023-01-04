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

	// move�Ɏg���ϐ�
	float m_move;		// �G�l�~�[�̑��x
	float m_distance;	// �ǂ̂��炢�v���C���[�ƃG�l�~�[���߂Â�����ǔ����邩�̋���

	int m_cnt;			// �����_���ړ��Ŏg��(�ړ����������ς���Ԋu)
	int m_randNum;		// �����_���ړ��Ŏg��(�ړ�������������߂�)
	DirectX::XMFLOAT3 m_target;
	DirectX::XMFLOAT3 m_randTarget;
	std::unique_ptr<CBossUI> m_bossUI;	// �{�X��UI

};