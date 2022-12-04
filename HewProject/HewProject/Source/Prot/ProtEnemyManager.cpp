#include "ProtEnemyManager.hpp"
#include <ProtEnemy.hpp>
CProtEnemyManager::CProtEnemyManager()
{
	// オブジェクトリストを格納
	m_objList = CSceneBase::GetObjList();
	// オブジェクトリストが死んでいなかったら
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

	// オブジェクト０番が死んでいたらというif文
	if (m_objects[0].expired() == true)
	{
		// 死んでいたら中に入る
	}
}
