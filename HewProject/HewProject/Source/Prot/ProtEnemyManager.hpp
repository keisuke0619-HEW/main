#pragma once
#include <SceneBase.hpp>
#include <IObjectBase.hpp>
#define PROT_ENEMY_MAX (5)
class CProtEnemyManager
{
public:
	CProtEnemyManager();
	void Update();

private:
	std::weak_ptr<IObjectBase> m_objects[PROT_ENEMY_MAX];
	std::weak_ptr<CObjectManager> m_objList;


};