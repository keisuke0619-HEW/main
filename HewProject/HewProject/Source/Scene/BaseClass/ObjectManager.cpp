#include "ObjectManager.hpp"
#include <CollisionBase.hpp>
#include <Camera.hpp>

bool CObjectManager::m_isCallDestroy;

void CObjectManager::CallDestroy()
{
	m_isCallDestroy = true;
}

CObjectManager::CObjectManager()
{
#ifdef CRITICAL_LOW_FPS_TEMPORARY_RESPONSE
	m_frame = 0;
#endif // CRITICAL_LOW_FPS_TEMPORARY_RESPONSE

}

CObjectManager::~CObjectManager()
{
}

void CObjectManager::UpdateAll()
{
	//TObjectParam CameraRay;
	//CameraRay.collisionType = COLLISION_RAY;
	//CameraRay.collisionData.ray.rayStart = CCameraBase::GetDataFromTag("Player").pos;
	//DirectX::XMFLOAT3 cameraLook = CCameraBase::GetDataFromTag("Player").look;
	//CameraRay.collisionData.ray.rayDirection = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&cameraLook),DirectX::XMLoadFloat3(&CameraRay.collisionData.ray.rayStart)));
	//CameraRay.collisionData.ray.rayLength = 100;

	for (auto itr = m_obj.begin(); itr != m_obj.end(); itr++)
	{
		(*itr)->BaseUpdate();
#ifdef CRITICAL_LOW_FPS_TEMPORARY_RESPONSE
		if (m_frame % 5 != 0)
			continue;
#endif // CRITICAL_LOW_FPS_TEMPORARY_RESPONSE

		auto collisionType = (*itr)->GetParam().collisionType;
		auto param = (*itr)->GetParam();
		int aaaaa = 0;
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

	// 未実装
	//for (auto itr = m_obj.begin(); itr != m_obj.end(); itr++)
	//{
	//	auto collisionType = (*itr)->GetParam().collisionType;
	//	// 当たり判定を使用しないオブジェクトならここで次へ
	//	if (collisionType == COLLISION_NONE)
	//		continue;
	//	bool isCollision = Utility::IsCollision((*itr)->GetParam(), CameraRay);
	//	if (isCollision)
	//	{
	//		DirectX::XMFLOAT3 target = Utility::GetTargetBox((*itr)->GetParam(), CameraRay);
	//		
	//		CObjectManager::FindTag(TAG_PLAYER)->GetParam().target = target;
	//	}
	//}

	//CObjectManager::FindTag(TAG_PLAYER)->GetParam().target = cameraLook;
#ifdef CRITICAL_LOW_FPS_TEMPORARY_RESPONSE
	m_frame++;
#endif // CRITICAL_LOW_FPS_TEMPORARY_RESPONSE

}

void CObjectManager::DrawAll()
{
	for (auto itr = m_obj.begin(); itr != m_obj.end(); itr++)
	{
		(*itr)->BaseDraw();
	}
}

void CObjectManager::NoDestroy()
{
	m_isCallDestroy = false;
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

std::list<IObjectBase::Ptr> CObjectManager::FindTagAll(EObjectTag tag)
{
	std::list<IObjectBase::Ptr> obj;
	for (auto itr = m_obj.begin(); itr != m_obj.end(); itr++)
	{
		if ((*itr)->GetParam().tag == tag)
		{
			obj.push_back((*itr));
		}
	}
	return obj;
}