#include "CollisionBase.hpp"

bool Utility::IsCollision(TObjectParam obj1, TObjectParam obj2)
{
    // 引数として渡されたデータをもとに当たり判定をとる。
    // 当たっていたらTrue
    // 当たっていなかったらFalse

	switch (obj1.collisionType)
	{
	case COLLISION_SPHIRE:
		switch (obj2.collisionType)
		{
		case COLLISION_SPHIRE:
			return Utility::IsCollisionShpire(obj1, obj2);
			break;
		case COLLISION_RAY:
			return Utility::IsCollisionShpireRay(obj1, obj2);
			break;
		case COLLISION_PLANE:
			return Utility::IsCollisionShpirePlane(obj1, obj2);
			break;
		default:
			break;
		}
		break;
	case COLLISION_RAY:
		switch (obj2.collisionType)
		{
		case COLLISION_SPHIRE:
			return Utility::IsCollisionShpireRay(obj2, obj1);
			break;
		case COLLISION_RAY:
			////////////////////////////////////////////////
			break;
		case COLLISION_PLANE:
			return Utility::IsCollisionRayPlane(obj1, obj2);
			break;
		default:
			break;
		}
		break;
	case COLLISION_PLANE:
		switch (obj2.collisionType)
		{
		case COLLISION_SPHIRE:
			return Utility::IsCollisionShpirePlane(obj2, obj1);
			break;
		case COLLISION_RAY:
			return Utility::IsCollisionRayPlane(obj2, obj1);
			break;
		case COLLISION_PLANE:
			return Utility::IsCollisionPlane(obj1, obj2);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

bool Utility::IsCollisionShpire(TObjectParam obj1, TObjectParam obj2)
{
    if ((obj1.pos.x - obj2.pos.x) * (obj1.pos.x - obj2.pos.x) +
		(obj1.pos.y - obj2.pos.y) * (obj1.pos.y - obj2.pos.y) +
		(obj1.pos.z - obj2.pos.z) * (obj1.pos.z - obj2.pos.z)
		<= powf(obj1.collisionData.sphire.sphireRadius + obj2.collisionData.sphire.sphireRadius, 3))
	{
		return true;
	}

	return false;
}

// 未完成
bool Utility::IsCollisionShpireRay(TObjectParam obj1, TObjectParam obj2)
{
	float A; // (vRay)の長さ
	float B; // (vRayの始点 - Shpireの中心座標)の長さ
	float C; // (vB - vRay)の長さ

	DirectX::XMStoreFloat(&A, DirectX::XMVectorScale(obj2.collisionData.ray.rayDirection, obj2.collisionData.ray.rayLength));
	DirectX::XMStoreFloat(&B, DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&obj2.collisionData.ray.rayStart), DirectX::XMLoadFloat3(&obj1.pos)));
	DirectX::XMStoreFloat(&C, DirectX::XMVectorSubtract(DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&obj2.collisionData.ray.rayStart), DirectX::XMLoadFloat3(&obj1.pos)),DirectX::XMVectorScale(obj2.collisionData.ray.rayDirection, obj2.collisionData.ray.rayLength)));
	
	// 余弦
	float cosA = (B * B + C * C - A * A) / (2.0f * B * C);
	float sinA = sqrtf(1 - (cosA * cosA));

	// 面積
	float S = 0.5f * B * C * sinA;
	// 高さ
	float h = S * 2 / C; 

	if (h <= obj1.collisionData.sphire.sphireRadius)
	{
		return true;
	}

	return false;
}

/// 未実装
bool Utility::IsCollisionShpirePlane(TObjectParam obj1, TObjectParam obj2)
{
	return false;
}

/// 未実装
bool Utility::IsCollisionRay(TObjectParam obj1, TObjectParam obj2)
{
	return false;
}

bool Utility::IsCollisionRayPlane(TObjectParam obj1, TObjectParam obj2)
{
	DirectX::XMVECTOR vRayStart = DirectX::XMLoadFloat3(&obj1.collisionData.ray.rayStart);
	DirectX::XMVECTOR vRayN = obj1.collisionData.ray.rayDirection;
	DirectX::XMVECTOR vPlaneN = DirectX::XMLoadFloat3(&obj2.collisionData.plane.planeNormal);
	DirectX::XMVECTOR vPlanePos = DirectX::XMLoadFloat3(&obj2.collisionData.plane.planeVtx[0]);
	vRayN = DirectX::XMVector3Normalize(vRayN);
	vPlaneN = DirectX::XMVector3Normalize(vPlaneN);

	//	1)平面から始点までの距離
	float P1;
	DirectX::XMVECTOR vToStart = DirectX::XMVectorSubtract(vRayStart, vPlanePos);
	DirectX::XMStoreFloat(&P1, DirectX::XMVector3Dot(vPlaneN, vToStart));

	//	2)終点から平面までの距離
	float P2;
	DirectX::XMVECTOR vToEnd = DirectX::XMVectorScale(vRayN, obj1.collisionData.ray.rayLength);
	vToEnd = DirectX::XMVectorAdd(vToEnd, vToStart);
	DirectX::XMStoreFloat(&P2, DirectX::XMVector3Dot(vPlaneN, vToEnd));

	//	3)レイが面を貫通しているか
	if (P1 >= 0 && P2 <= 0)
	{
		DirectX::XMFLOAT3 point;
		float dist = obj1.collisionData.ray.rayLength *(P1 / (P1 - P2));
		DirectX::XMStoreFloat3(&point, DirectX::XMVectorAdd(DirectX::XMVectorScale(vRayN, dist), vRayStart));

		// 外積
		DirectX::XMVECTOR vCross[3];
		DirectX::XMVECTOR vPoint = DirectX::XMLoadFloat3(&point);
		DirectX::XMVECTOR vTriStart = DirectX::XMLoadFloat3(&obj2.collisionData.plane.planeVtx[0]);
		DirectX::XMVECTOR vTriEnd;
		DirectX::XMVECTOR vTriEdge;
		DirectX::XMVECTOR vToPoint;
		DirectX::XMVECTOR vDot[3];
		float match[3];

		// 1つ目
		for (int i = 0; i < 3; ++i)
		{
			vTriEnd = DirectX::XMLoadFloat3(&obj2.collisionData.plane.planeVtx[(i + 1) % 3]);
			vTriEdge = DirectX::XMVectorSubtract(vTriEnd, vTriStart);
			vToPoint = DirectX::XMVectorSubtract(vPoint, vTriStart);
			vCross[i] = DirectX::XMVector3Cross(vTriEdge, vToPoint);
			vCross[i] = DirectX::XMVector3Normalize(vCross[i]);
			vTriStart = vTriEnd;
		}

		vDot[0] = DirectX::XMVector3Dot(vCross[0], vCross[1]);
		vDot[1] = DirectX::XMVector3Dot(vCross[1], vCross[2]);
		vDot[2] = DirectX::XMVector3Dot(vCross[0], vCross[2]);

		for (int i = 0; i < 3; i++)
		{
			DirectX::XMStoreFloat(&match[i], vDot[i]);
		}

		if ((match[0] >= 0.98f) && (match[1] >= 0.98f) && (match[2] >= 0.98f))
		{
			return true;
		}

		// 2つ目
		vTriStart = DirectX::XMLoadFloat3(&obj2.collisionData.plane.planeVtx[1]);
		for (int i = 0; i < 3; ++i)
		{
			vTriEnd = DirectX::XMLoadFloat3(&obj2.collisionData.plane.planeVtx[3 - i]);
			vTriEdge = DirectX::XMVectorSubtract(vTriEnd, vTriStart);
			vToPoint = DirectX::XMVectorSubtract(vPoint, vTriStart);
			vCross[i] = DirectX::XMVector3Cross(vTriEdge, vToPoint);
			vCross[i] = DirectX::XMVector3Normalize(vCross[i]);
			vTriStart = vTriEnd;
		}

		vDot[0] = DirectX::XMVector3Dot(vCross[0], vCross[1]);
		vDot[1] = DirectX::XMVector3Dot(vCross[1], vCross[2]);
		vDot[2] = DirectX::XMVector3Dot(vCross[0], vCross[2]);

		for (int i = 0; i < 3; i++)
		{
			DirectX::XMStoreFloat(&match[i], vDot[i]);
		}

		if ((match[0] >= 0.98f) && (match[1] >= 0.98f) && (match[2] >= 0.98f))
		{
			return true;
		}
	}

	return false;
}

/// 未実装
bool Utility::IsCollisionPlane(TObjectParam obj1, TObjectParam obj2)
{
	return false;
}

DirectX::XMFLOAT3 Utility::GetTargetPlane(TObjectParam obj1, TObjectParam obj2)
{
	DirectX::XMVECTOR vRayStart = DirectX::XMLoadFloat3(&obj1.collisionData.ray.rayStart);
	DirectX::XMVECTOR vRayN = obj1.collisionData.ray.rayDirection;
	DirectX::XMVECTOR vPlaneN = DirectX::XMLoadFloat3(&obj2.collisionData.plane.planeNormal);
	DirectX::XMVECTOR vPlanePos = DirectX::XMLoadFloat3(&obj2.collisionData.plane.planeVtx[0]);
	vRayN = DirectX::XMVector3Normalize(vRayN);
	vPlaneN = DirectX::XMVector3Normalize(vPlaneN);

	//	1)平面から始点までの距離
	float P1;
	DirectX::XMVECTOR vToStart = DirectX::XMVectorSubtract(vRayStart, vPlanePos);
	DirectX::XMStoreFloat(&P1, DirectX::XMVector3Dot(vPlaneN, vToStart));

	//	2)終点から平面までの距離
	float P2;
	DirectX::XMVECTOR vToEnd = DirectX::XMVectorScale(vRayN, obj1.collisionData.ray.rayLength);
	vToEnd = DirectX::XMVectorAdd(vToEnd, vToStart);
	DirectX::XMStoreFloat(&P2, DirectX::XMVector3Dot(vPlaneN, vToEnd));

	DirectX::XMFLOAT3 point;
	float dist = obj1.collisionData.ray.rayLength *(P1 / (P1 - P2));
	DirectX::XMStoreFloat3(&point, DirectX::XMVectorAdd(DirectX::XMVectorScale(vRayN, dist), vRayStart));

	return point;
}