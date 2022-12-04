#include "ProtEnemy.hpp"
#include <Easing.hpp>
#include <SceneBase.hpp>
// �����蔻��͌�ŕt���܂��B

CProtEnemy::CProtEnemy()
	: CObjectBase("Assets/MagicaBoxelModel/PlaneBox.obj")
{
	// �I�u�W�F�N�g�̃��X�g���擾
	auto objList = CSceneBase::GetObjList();
	// �v���C���[�̃I�u�W�F�N�g���擾
	m_player = objList.lock()->FindTag(TAG_PLAYER);
	m_param.pos.x = (rand() % 100) / 10.0f;
	m_param.pos.y = 1.0f;
	m_param.pos.z = (rand() % 100) / 10.0f;
}

CProtEnemy::~CProtEnemy()
{

}

void CProtEnemy::Update()
{
	// �����v���C���[�̃I�u�W�F�N�g�������Ă����������x�擾
	if (m_player.expired() == true)
	{
		auto objList = CSceneBase::GetObjList();
		m_player = objList.lock()->FindTag(TAG_PLAYER);
	}
	// �ړ���[����
	Move();
}

// �ړ����[�`���BExcel���Q�l�ɍ쐬
// ���[���񂮂��g�p�B
void CProtEnemy::Move()
{
	// ���[���񂮎g�p���@�i��j
	// Easing::InOutSine(level);

	// �v���C���[�Ƃ̋������擾
	
	// �����v���C���[�Ƃ̋��������ȉ���������

	// �v���C���[��ڕW�ɂ���

	// �������

	// �����_���ړ�
}

// ���S���ɏ���ɌĂ΂�܂��B
void CProtEnemy::Finalize()
{
	// �}�l�[�W���Ɏ��񂾂��Ƃ�`����

}
