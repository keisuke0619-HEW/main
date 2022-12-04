#include "ProtEnemyManager.hpp"
#include <ProtEnemy.hpp>
CProtEnemyManager::CProtEnemyManager()
{
	// �I�u�W�F�N�g���X�g���i�[
	m_objList = CSceneBase::GetObjList();
	// �I�u�W�F�N�g���X�g������ł��Ȃ�������
	if (m_objList.expired() == false)
	{
		// �ő吔�܂Ń��[�v
		for (int i = 0; i < PROT_ENEMY_MAX; i++)
		{
			// �G�𐶐�
			m_objects[i] = m_objList.lock()->Add(new CProtEnemy());
		}
	}

}

void CProtEnemyManager::Update()
{
	// ���݂̃I�u�W�F�N�g�̐����}�b�N�X�ȉ���������P�b��ɐV�����I�u�W�F�N�g�𐶐�

	// �I�u�W�F�N�g�O�Ԃ�����ł�����Ƃ���if��
	if (m_objects[0].expired() == true)
	{
		// ����ł����璆�ɓ���
	}
}
