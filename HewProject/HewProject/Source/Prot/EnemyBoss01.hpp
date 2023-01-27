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
	int m_Fream;	// �V�[���J�ڗp�̎���

	// move�Ɏg���ϐ�
	float m_move;		// �G�l�~�[�̑��x
	float m_distance;	// �ǂ̂��炢�v���C���[�ƃG�l�~�[���߂Â�����ǔ����邩�̋���

	int m_cnt;			// �����_���ړ��Ŏg��(�ړ����������ς���Ԋu)
	int m_randNum;		// �����_���ړ��Ŏg��(�ړ�������������߂�)
	DirectX::XMFLOAT3 m_target;
	DirectX::XMFLOAT3 m_randTarget;
	std::unique_ptr<CBossUI> m_bossUI;	// �{�X��UI

	DirectX::XMFLOAT3 m_oldPos;
	Data* m_data;

	float m_HP;

	CEffect::Ptr m_pEfk;
};