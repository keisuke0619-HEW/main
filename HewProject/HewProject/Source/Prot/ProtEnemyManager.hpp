#pragma once
#include <SceneBase.hpp>
#include <IObjectBase.hpp>
#include <ISceneBase.hpp>
#define PROT_ENEMY_MAX (30)
#define PROT_ENEMY_BOSS_MAX (1)

class CProtEnemyManager
{
public:
	CProtEnemyManager(Data* data, int enemy, int boss);
	void Update();

private:
	std::weak_ptr<IObjectBase> m_objects[PROT_ENEMY_MAX];
	std::weak_ptr<CObjectManager> m_objList;

	std::weak_ptr<IObjectBase> m_objectsBoss[PROT_ENEMY_BOSS_MAX];
	std::weak_ptr<CObjectManager> m_objListBoss;

	int m_frame;

	Data* m_data;

	int m_enemy_MAX;
	int m_boss_MAX;
};