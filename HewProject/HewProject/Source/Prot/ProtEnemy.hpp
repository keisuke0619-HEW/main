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

	// move�Ɏg���ϐ�
	float m_move;		// �G�l�~�[�̑��x
	float m_distance;	// �ǂ̂��炢�v���C���[�ƃG�l�~�[���߂Â�����ǔ����邩�̋���

	int m_cnt;			// �����_���ړ��Ŏg��(�ړ����������ς���Ԋu)
	int m_randNum;		// �����_���ړ��Ŏg��(�ړ�������������߂�)
	bool m_dontMove;	// �G�l�~�[�̓������~�߂�
	const int m_blowAwayCount = 2;	// ������Ԏ���
	int m_blowAwayCountDown;		// �������ł��鎞�Ԃ̃J�E���g 
	DirectX::XMFLOAT3 m_target;
	DirectX::XMFLOAT3 m_randTarget;
	DirectX::XMFLOAT3 m_startPos;
	DirectX::XMFLOAT3 m_blowAwayMove;	// ������ԕ���

	CBillboard* m_bill;
};