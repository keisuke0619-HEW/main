#include "ObjectManager.hpp"
#include <CollisionBase.hpp>

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
		// 当たり判定を使用しないオブジェクトならここで次へ
		if (collisionType == COLLISION_NONE)
			continue;

		// 自身より後ろをすべて探索
		for (auto colItr = itr; colItr != m_obj.end(); colItr++)
		{
			auto colObjType = (*colItr)->GetParam().collisionType;
			// 当たり判定を使用しないなら次へ
			if (colObjType == COLLISION_NONE)
				continue;

			// ここで当たり判定をとる。
			bool isCollision = Utility::IsCollision((*itr)->GetParam(), (*colItr)->GetParam());
			if (isCollision)
			{
				// 当たっていたらそれぞれの仮想関数
				(*itr)->OnCollision((*colItr));
				(*colItr)->OnCollision((*itr));
			}
		}
	}

	//(仮)
	//for (auto itr = m_obj.begin(); itr != m_obj.end(); itr++)
	//{
	//	auto collisionType = (*itr)->GetParam().collisionType;
	//	// 当たり判定を使用しないオブジェクトならここで次へ
	//	if (collisionType == COLLISION_NONE)
	//		continue;
	//	bool isCollision = Utility::IsCollision((*itr)->GetParam(), CameraRay);
	//	if (isCollision)
	//	{
	//		// DirectX::XMFLOAT3 target = Utility::GetTargetBox((*itr)->GetParam(), CameraRay);
	//		//
	//		//	当たっていたらプレイヤーのビームにtargetを送る(未実装)
	//		//
	//	}
	//}
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
