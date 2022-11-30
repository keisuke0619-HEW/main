#pragma once
#include <list>
#include <ObjectToManagerInterface.hpp>
class CObjectManager
{
public:
	CObjectManager();
	~CObjectManager();

	void UpdateAll();
	void DrawAll();

	void DestroyUpdate();
	
private:
	std::list<IObjectToManager::Ptr> m_obj;
};