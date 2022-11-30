#pragma once
#include <list>
#include <ObjectToManagerInterface.hpp>
class CObjectManager
{
public:
	static void CallDestroy();
private:
	static bool m_isCallDestroy;
public:
	CObjectManager();
	~CObjectManager();

	void UpdateAll();
	void DrawAll();

	void DestroyUpdate();
	void Add(IObjectToManager* obj);
	IObjectToManager::Ptr FindTag(EObjectTag tag);
	IObjectToManager::Ptr FindName(std::string name);
	
private:
	std::list<IObjectToManager::Ptr> m_obj;
};