#include "ObjectManager.hpp"

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
	auto itr = m_obj.begin();
	while (itr != m_obj.end())
	{
		if ((*itr)->GetParam().isDestroy == true)
			itr = m_obj.erase(itr);
		else
			itr++;
	}

}
