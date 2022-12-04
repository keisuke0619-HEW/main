#pragma once
#include <SceneBase.hpp>
#include <ObjectToManagerInterface.hpp>
#define PROT_ENEMY_MAX (3)
class CProtEnemyManager
{
public:
	CProtEnemyManager();
	void Update();

private:
	std::weak_ptr<IObjectBase> m_objects[PROT_ENEMY_MAX];
	std::weak_ptr<CObjectManager> m_objList;


};