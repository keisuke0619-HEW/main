#include "ProtEnemyManager.hpp"
#include <ProtEnemy.hpp>
CProtEnemyManager::CProtEnemyManager()
{
	// オブジェクトリストを格納
	m_objList = CSceneBase::GetObjList();
	// オブジェクトリストが死んでいなかったら(NULLチェックもどきだよ.expired)
	if (m_objList.expired() == false)
	{
		// 最大数までループ
		for (int i = 0; i < PROT_ENEMY_MAX; i++)
		{
			// 敵を生成
			m_objects[i] = m_objList.lock()->Add(new CProtEnemy());
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
	// オブジェクト０番が死んでいたらというif文
	for (int i = 0; i < PROT_ENEMY_MAX; i++)
	{
		if (m_objects[i].expired() == true)
		{
			// 死んでいたら中に入る
			m_objects[i] = m_objList.lock()->Add(new CProtEnemy());
		}
	}
	
	

}
