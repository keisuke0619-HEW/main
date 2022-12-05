#pragma once
#include <list>
#include <IObjectBase.hpp>
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
	std::weak_ptr<IObjectBase> Add(IObjectBase* obj);
	IObjectBase::Ptr FindTag(EObjectTag tag);
	IObjectBase::Ptr FindName(std::string name);
	
private:
	std::list<IObjectBase::Ptr> m_obj;
};