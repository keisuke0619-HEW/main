#include "ObjectManager.hpp"

bool CObjectManager::m_isCallDestroy;

void CObjectManager::CallDestroy()
{
	m_isCallDestroy = true;
}

CObjectManager::CObjectManager()
{

}

CObjectManager::~CObjectManager()
{
}

void CObjectManager::UpdateAll()
{
	for (auto itr = m_obj.begin(); itr != m_obj.end(); itr++)
	{
		(*itr)->BaseUpdate();
	}
}

void CObjectManager::DrawAll()
{
	for (auto itr = m_obj.begin(); itr != m_obj.end(); itr++)
	{
		(*itr)->BaseDraw();
	}
}

void CObjectManager::DestroyUpdate()
{
	if (m_isCallDestroy == false)
		return;
	auto itr = m_obj.begin();
	while (itr != m_obj.end())
	{
		if ((*itr)->GetParam().isDestroy == true)
			itr = m_obj.erase(itr);
		else
			itr++;
	}
	m_isCallDestroy = false;
}

void CObjectManager::Add(IObjectToManager* obj)
{
	m_obj.push_back(std::shared_ptr<IObjectToManager>(obj));
}

IObjectToManager::Ptr CObjectManager::FindTag(EObjectTag tag)
{
	for (auto itr = m_obj.begin(); itr != m_obj.end(); itr++)
	{
		if((*itr)->GetParam().tag == tag)
			return (*itr);
	}
	return nullptr;
}

IObjectToManager::Ptr CObjectManager::FindName(std::string name)
{
	for (auto itr = m_obj.begin(); itr != m_obj.end(); itr++)
	{
		if ((*itr)->GetParam().name == name)
			return (*itr);
	}
	return nullptr;

}
