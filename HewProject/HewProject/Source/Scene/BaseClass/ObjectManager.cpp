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
		auto collisionType = (*itr)->GetParam().collisionType;
		// �����蔻����g�p����Ȃ�
		if (collisionType != COLLISION_NONE)
		{
			// ���g���������ׂĒT��
			for (auto colItr = itr; itr != m_obj.end(); colItr++)
			{
				auto colObjType = (*colItr)->GetParam().collisionType;
				// ���̃I�u�W�F�N�g�������蔻����g�p����Ȃ�
				if (colObjType != COLLISION_NONE)
				{
					// �����œ����蔻����Ƃ�B

				}

			}
		}
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

std::weak_ptr<IObjectBase> CObjectManager::Add(IObjectBase* obj)
{
	auto smartObj = std::shared_ptr<IObjectBase>(obj);
	m_obj.push_back(smartObj);
	return smartObj;
}

IObjectBase::Ptr CObjectManager::FindTag(EObjectTag tag)
{
	for (auto itr = m_obj.begin(); itr != m_obj.end(); itr++)
	{
		if((*itr)->GetParam().tag == tag)
			return (*itr);
	}
	return nullptr;
}

IObjectBase::Ptr CObjectManager::FindName(std::string name)
{
	for (auto itr = m_obj.begin(); itr != m_obj.end(); itr++)
	{
		if ((*itr)->GetParam().name == name)
			return (*itr);
	}
	return nullptr;

}
