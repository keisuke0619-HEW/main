#include "ProtEnemyManager.hpp"
#include <EnemyZako01.hpp>
#include<EnemyBoss01.hpp>
CProtEnemyManager::CProtEnemyManager(Data* data, int enemy, int boss, float bossHP)
{
	m_data = data;

	if (m_enemy_MAX > PROT_ENEMY_MAX)
	{
		m_enemy_MAX = PROT_ENEMY_MAX;
	}
	else
	{
		m_enemy_MAX = enemy;
	}
	
	if (m_boss_MAX > PROT_ENEMY_BOSS_MAX)
	{
		m_boss_MAX = PROT_ENEMY_BOSS_MAX;
	}
	else
	{
		m_boss_MAX = boss;
	}

	// �I�u�W�F�N�g���X�g���i�[
	m_objList = CSceneBase::GetObjList();
	m_objListBoss = CSceneBase::GetObjList();

	m_frame = 0;
	// �I�u�W�F�N�g���X�g������ł��Ȃ�������(NULL�`�F�b�N���ǂ�����.expired)
	if (m_objList.expired() == false)
	{
		// �ő吔�܂Ń��[�v
		for (int i = 0; i < m_enemy_MAX; i++)
		{
			// �G�𐶐�
			m_objects[i] = m_objList.lock()->Add(new CProtEnemy(m_data));
		}
	}
	//�{�X����
	if (m_objListBoss.expired() == false)
	{
		// �ő吔�܂Ń��[�v
		for (int i = 0; i < m_boss_MAX; i++)
		{
			// �G�𐶐�
			m_objectsBoss[i] = m_objListBoss.lock()->Add(new CProtEnemyBoss(m_data, bossHP));
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
		for (int i = 0; i < m_enemy_MAX; i++)
		{
			if (m_objects[i].expired() == true)
			{
				// ����ł����璆�ɓ���
				m_objects[i] = m_objList.lock()->Add(new CProtEnemy(m_data));
			}
		}
	}
	//�{�X����
	// ���݂̃I�u�W�F�N�g�̐����}�b�N�X�ȉ���������P�b��ɐV�����I�u�W�F�N�g�𐶐�
	//if (m_objListBoss.expired() == true)
	//{
	//	return;
	//}
	//for (int i = 0; i < m_boss_MAX; i++)
	//{
	//	if (m_objectsBoss[i].expired() == true)
	//	{
	//		// ����ł����璆�ɓ���
	//		m_objectsBoss[i] = m_objListBoss.lock()->Add(new CProtEnemyBoss(m_data));
	//	}
	//}

	m_frame++;
}
