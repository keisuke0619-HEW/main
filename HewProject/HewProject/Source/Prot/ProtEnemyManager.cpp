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

	// オブジェクトリストを格納
	m_objList = CSceneBase::GetObjList();
	m_objListBoss = CSceneBase::GetObjList();

	m_frame = 0;
	// オブジェクトリストが死んでいなかったら(NULLチェックもどきだよ.expired)
	if (m_objList.expired() == false)
	{
		// 最大数までループ
		for (int i = 0; i < m_enemy_MAX; i++)
		{
			// 敵を生成
			m_objects[i] = m_objList.lock()->Add(new CProtEnemy(m_data));
		}
	}
	//ボス生成
	if (m_objListBoss.expired() == false)
	{
		// 最大数までループ
		for (int i = 0; i < m_boss_MAX; i++)
		{
			// 敵を生成
			m_objectsBoss[i] = m_objListBoss.lock()->Add(new CProtEnemyBoss(m_data, bossHP));
		}
	}
}

void CProtEnemyManager::Update()
{
	// 現在のオブジェクトの数がマックス以下だったら１秒後に新しいオブジェクトを生成
	if (m_objList.expired() ==true)
	{
		return;
	}
	if (m_frame % (60 * 5) == 0)
	{
		// オブジェクト０番が死んでいたらというif文
		for (int i = 0; i < m_enemy_MAX; i++)
		{
			if (m_objects[i].expired() == true)
			{
				// 死んでいたら中に入る
				m_objects[i] = m_objList.lock()->Add(new CProtEnemy(m_data));
			}
		}
	}
	//ボス生成
	// 現在のオブジェクトの数がマックス以下だったら１秒後に新しいオブジェクトを生成
	//if (m_objListBoss.expired() == true)
	//{
	//	return;
	//}
	//for (int i = 0; i < m_boss_MAX; i++)
	//{
	//	if (m_objectsBoss[i].expired() == true)
	//	{
	//		// 死んでいたら中に入る
	//		m_objectsBoss[i] = m_objListBoss.lock()->Add(new CProtEnemyBoss(m_data));
	//	}
	//}

	m_frame++;
}
