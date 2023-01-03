#include "ProtEnemyManager.hpp"
#include <EnemyZako01.hpp>
#include<EnemyBoss01.hpp>
CProtEnemyManager::CProtEnemyManager()
{
	// �I�u�W�F�N�g���X�g���i�[
	m_objList = CSceneBase::GetObjList();
	m_objListBoss = CSceneBase::GetObjList();

	m_frame = 0;
	// �I�u�W�F�N�g���X�g������ł��Ȃ�������(NULL�`�F�b�N���ǂ�����.expired)
	if (m_objList.expired() == false)
	{
		// �ő吔�܂Ń��[�v
		for (int i = 0; i < PROT_ENEMY_MAX; i++)
		{
			// �G�𐶐�
			m_objects[i] = m_objList.lock()->Add(new CProtEnemy());
		}
	}
	//�{�X����
	if (m_objListBoss.expired() == false)
	{
		// �ő吔�܂Ń��[�v
		for (int i = 0; i < PROT_ENEMY_BOSS_MAX; i++)
		{
			// �G�𐶐�
			m_objectsBoss[i] = m_objListBoss.lock()->Add(new CProtEnemyBoss());
		}
	}

}

void CProtEnemyManager::Update()
{
	// ���݂̃I�u�W�F�N�g�̐����}�b�N�X�ȉ���������P�b��ɐV�����I�u�W�F�N�g�𐶐�
	if (m_objList.expired() ==true)
	{
		return;
	}
	if (m_frame % (60 * 5) == 0)
	{
		// �I�u�W�F�N�g�O�Ԃ�����ł�����Ƃ���if��
		for (int i = 0; i < PROT_ENEMY_MAX; i++)
		{
			if (m_objects[i].expired() == true)
			{
				// ����ł����璆�ɓ���
				m_objects[i] = m_objList.lock()->Add(new CProtEnemy());
			}
		}
	}
	//�{�X����
	// ���݂̃I�u�W�F�N�g�̐����}�b�N�X�ȉ���������P�b��ɐV�����I�u�W�F�N�g�𐶐�
	if (m_objListBoss.expired() == true)
	{
		return;
	}
	for (int i = 0; i < PROT_ENEMY_BOSS_MAX; i++)
	{
		if (m_objectsBoss[i].expired() == true)
		{
			// ����ł����璆�ɓ���
			m_objectsBoss[i] = m_objListBoss.lock()->Add(new CProtEnemyBoss());
		}
	}

	m_frame++;
}
