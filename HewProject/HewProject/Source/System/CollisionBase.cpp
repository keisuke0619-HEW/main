#include "CollisionBase.hpp"

// 完
// オブジェクト：オブジェクト
bool Utility::IsCollision(TObjectParam obj1, TObjectParam obj2)
{
	if (pow(obj1.pos.x - obj2.pos.x, 2) +
		pow(obj1.pos.z - obj2.pos.z, 2) >=
		35.0f)
	{
		return false;
	}

	switch (obj1.collisionType)
	{
	case COLLISION_CHARACTER:
		switch (obj2.collisionType)
		{
		case COLLISION_CHARACTER:
			return IsCollision_C_to_C(obj1, obj2);
		case COLLISION_OBSTACLES:
			return IsCollision_C_to_O(obj1, obj2);
		}
	case COLLISION_OBSTACLES:
		switch (obj2.collisionType)
		{
		case COLLISION_CHARACTER:
			return IsCollision_C_to_O(obj2, obj1);
		case COLLISION_OBSTACLES:
			return false;
		}
	case COLLISION_PLANE:
		switch (obj2.collisionType)
		{
		case COLLISION_CHARACTER:
			return IsCollision_C_to_P(obj1, obj2);
		case COLLISION_OBSTACLES:
			return false;
		}
	default:
		break;
	}
}

bool Utility::IsCollision_C_to_C(TObjectParam obj1, TObjectParam obj2)
{
	if (pow(obj1.collisionData.character.pos.x - obj2.collisionData.character.pos.x, 2) +
		pow(obj1.collisionData.character.pos.y - obj2.collisionData.character.pos.y, 2) +
		pow(obj1.collisionData.character.pos.z - obj2.collisionData.character.pos.z, 2) <=
		pow(obj1.collisionData.character.radius + obj2.collisionData.character.radius,3))
	{
		return true;
	}

	return false;
}

bool Utility::IsCollision_C_to_O(TObjectParam obj1, TObjectParam obj2)
{
	/// 回転しているか
	if (obj2.collisionData.obstacles.spin)
	{
		/// obj1の左とobj2の右
		if (obj1.collisionData.character.pos.x - obj1.collisionData.character.radius >=
			obj2.collisionData.obstacles.pos.x + obj2.collisionData.obstacles.size.y / 2.0f)
		{
			return false;
		}
		/// obj1の右とobj2の左
		if (obj1.collisionData.character.pos.x + obj1.collisionData.character.radius <=
			obj2.collisionData.obstacles.pos.x - obj2.collisionData.obstacles.size.y / 2.0f)
		{
			return false;
		}
		/// obj1の上とobj2の下
		if (obj1.collisionData.character.pos.z + obj1.collisionData.character.radius <=
			obj2.collisionData.obstacles.pos.z - obj2.collisionData.obstacles.size.x / 2.0f)
		{
			return false;
		}
		/// obj1の下とobj2の上
		if (obj1.collisionData.character.pos.z - obj1.collisionData.character.radius >=
			obj2.collisionData.obstacles.pos.z + obj2.collisionData.obstacles.size.x / 2.0f)
		{
			return false;
		}

		return true;
	}
	else
	{
		/// obj1の左とobj2の右
		if (obj1.collisionData.character.pos.x - obj1.collisionData.character.radius >=
			obj2.collisionData.obstacles.pos.x + obj2.collisionData.obstacles.size.x / 2.0f)
		{
			return false;
		}
		/// obj1の右とobj2の左
		if (obj1.collisionData.character.pos.x + obj1.collisionData.character.radius <=
			obj2.collisionData.obstacles.pos.x - obj2.collisionData.obstacles.size.x / 2.0f)
		{
			return false;
		}
		/// obj1の上とobj2の下
		if (obj1.collisionData.character.pos.z + obj1.collisionData.character.radius <=
			obj2.collisionData.obstacles.pos.z - obj2.collisionData.obstacles.size.y / 2.0f)
		{
			return false;
		}
		/// obj1の下とobj2の上
		if (obj1.collisionData.character.pos.z - obj1.collisionData.character.radius >=
			obj2.collisionData.obstacles.pos.z + obj2.collisionData.obstacles.size.y / 2.0f)
		{
			return false;
		}
		
		return true;
	}
}

bool Utility::IsCollision_C_to_P(TObjectParam obj1, TObjectParam obj2)
{
	/// 
	DirectX::XMMATRIX mRot = DirectX::XMMatrixRotationX(obj2.collisionData.plane.rot.x) * DirectX::XMMatrixRotationY(obj2.collisionData.plane.rot.y) *  DirectX::XMMatrixRotationZ(obj2.collisionData.plane.rot.z);
	DirectX::XMFLOAT3 Vtx[4] =
	{
		DirectX::XMFLOAT3(-1, 0,  1),
		DirectX::XMFLOAT3(1, 0,  1),
		DirectX::XMFLOAT3(-1 ,0, -1),
		DirectX::XMFLOAT3(1, 0, -1)
	};
	for (int i = 0; i < 4; i++)
	{
		DirectX::XMVECTOR vVtx = DirectX::XMVector3TransformCoord(DirectX::XMLoadFloat3(&Vtx[i]), mRot);
		vVtx = DirectX::XMVectorScale(vVtx, sqrtf(powf(obj2.collisionData.plane.size.x / 2.0f, 2) + powf(obj2.collisionData.plane.size.y / 2.0f, 2)));
		DirectX::XMStoreFloat3(&Vtx[i], vVtx);
	}

	DirectX::XMVECTOR vRayStart = DirectX::XMLoadFloat3(&obj1.collisionData.ray.start);
	DirectX::XMVECTOR vRayN = obj1.collisionData.ray.direction;
	DirectX::XMVECTOR vPlaneN = { 0.0f,1.0f,0.0f };

	vPlaneN = DirectX::XMVector3TransformCoord(vPlaneN, mRot);
	DirectX::XMVECTOR vPlanePos = DirectX::XMLoadFloat3(&Vtx[0]);
	vRayN = DirectX::XMVector3Normalize(vRayN);
	vPlaneN = DirectX::XMVector3Normalize(vPlaneN);

	//	1)平面から始点までの距離
	float P1;
	DirectX::XMVECTOR vToStart = DirectX::XMVectorSubtract(vRayStart, vPlanePos);
	DirectX::XMStoreFloat(&P1, DirectX::XMVector3Dot(vPlaneN, vToStart));

	//	2)終点から平面までの距離
	float P2;
	DirectX::XMVECTOR vToEnd = DirectX::XMVectorScale(vRayN, obj1.collisionData.ray.length);
	vToEnd = DirectX::XMVectorAdd(vToEnd, vToStart);
	DirectX::XMStoreFloat(&P2, DirectX::XMVector3Dot(vPlaneN, vToEnd));

	DirectX::XMFLOAT3 point;
	float dist = obj1.collisionData.ray.length *(P1 / (P1 - P2));
	DirectX::XMStoreFloat3(&point, DirectX::XMVectorAdd(DirectX::XMVectorScale(vRayN, dist), vRayStart));

	return false;
}

// 未
// レイ：面
DirectX::XMFLOAT3 Utility::GetTargetPlane(TObjectParam obj1, TObjectParam obj2)
{
	DirectX::XMMATRIX mRot = DirectX::XMMatrixRotationX(obj2.collisionData.plane.rot.x) * DirectX::XMMatrixRotationY(obj2.collisionData.plane.rot.y) *  DirectX::XMMatrixRotationZ(obj2.collisionData.plane.rot.z);
	DirectX::XMFLOAT3 Vtx[4] =
	{
		DirectX::XMFLOAT3(-1, 0,  1),
		DirectX::XMFLOAT3(1, 0,  1),
		DirectX::XMFLOAT3(-1 ,0, -1),
		DirectX::XMFLOAT3(1, 0, -1)
	};
	for (int i = 0; i < 4; i++)
	{
		DirectX::XMVECTOR vVtx = DirectX::XMVector3TransformCoord(DirectX::XMLoadFloat3(&Vtx[i]), mRot);
		vVtx = DirectX::XMVectorScale(vVtx, sqrtf(powf(obj2.collisionData.plane.size.x / 2.0f, 2) + powf(obj2.collisionData.plane.size.y / 2.0f, 2)));
		DirectX::XMStoreFloat3(&Vtx[i], vVtx);
	}

	DirectX::XMVECTOR vRayStart = DirectX::XMLoadFloat3(&obj1.collisionData.ray.start);
	DirectX::XMVECTOR vRayN = obj1.collisionData.ray.direction;
	DirectX::XMVECTOR vPlaneN = { 0.0f,1.0f,0.0f };
	
	vPlaneN = DirectX::XMVector3TransformCoord(vPlaneN, mRot);
	DirectX::XMVECTOR vPlanePos = DirectX::XMLoadFloat3(&Vtx[0]);
	vRayN = DirectX::XMVector3Normalize(vRayN);
	vPlaneN = DirectX::XMVector3Normalize(vPlaneN);

	//	1)平面から始点までの距離
	float P1;
	DirectX::XMVECTOR vToStart = DirectX::XMVectorSubtract(vRayStart, vPlanePos);
	DirectX::XMStoreFloat(&P1, DirectX::XMVector3Dot(vPlaneN, vToStart));

	//	2)終点から平面までの距離
	float P2;
	DirectX::XMVECTOR vToEnd = DirectX::XMVectorScale(vRayN, obj1.collisionData.ray.length);
	vToEnd = DirectX::XMVectorAdd(vToEnd, vToStart);
	DirectX::XMStoreFloat(&P2, DirectX::XMVector3Dot(vPlaneN, vToEnd));

	DirectX::XMFLOAT3 point;
	float dist = obj1.collisionData.ray.length *(P1 / (P1 - P2));
	DirectX::XMStoreFloat3(&point, DirectX::XMVectorAdd(DirectX::XMVectorScale(vRayN, dist), vRayStart));

	return point;
}