#include "CollisionBase.hpp"

// 完
// オブジェクト：オブジェクト
bool Utility::IsCollision(TObjectParam obj1, TObjectParam obj2)
{
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

// 完
// 球：球
bool Utility::IsCollisionShpire(TObjectParam obj1, TObjectParam obj2)
{
    if ((obj1.collisionData.sphire.sphirePos.x - obj2.collisionData.sphire.sphirePos.x) * (obj1.collisionData.sphire.sphirePos.x - obj2.collisionData.sphire.sphirePos.x) +
		(obj1.collisionData.sphire.sphirePos.y - obj2.collisionData.sphire.sphirePos.y) * (obj1.collisionData.sphire.sphirePos.y - obj2.collisionData.sphire.sphirePos.y) +
		(obj1.collisionData.sphire.sphirePos.z - obj2.collisionData.sphire.sphirePos.z) * (obj1.collisionData.sphire.sphirePos.z - obj2.collisionData.sphire.sphirePos.z)
		<= powf(obj1.collisionData.sphire.sphireRadius + obj2.collisionData.sphire.sphireRadius, 3))
	{
		return true;
	}

	return false;
}

// 未
// 球：レイ
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

// 未
// 球：面
bool Utility::IsCollisionShpirePlane(TObjectParam obj1, TObjectParam obj2)
{
	DirectX::XMVECTOR vPlaneN = { 0.0f,1.0f,0.0f };
	DirectX::XMMATRIX mRot = DirectX::XMMatrixRotationX(obj2.collisionData.plane.planeRot.x) * DirectX::XMMatrixRotationY(obj2.collisionData.plane.planeRot.y) *  DirectX::XMMatrixRotationZ(obj2.collisionData.plane.planeRot.z);
	vPlaneN = DirectX::XMVector3Normalize(DirectX::XMVector3TransformCoord(vPlaneN, mRot));

	// 球のレイ作成
	DirectX::XMVECTOR vRayN = DirectX::XMVectorScale(vPlaneN, -1.0f);
	RayData ray = { obj1.collisionData.sphire.sphirePos, vRayN, obj1.collisionData.sphire.sphireRadius};

	TObjectParam Ray;
	Ray.collisionData.ray = ray;

	return Utility::IsCollisionRayPlane(Ray, obj2);
}

// 未実
// レイ：レイ
bool Utility::IsCollisionRay(TObjectParam obj1, TObjectParam obj2)
{
	return false;
}

// 完
// レイ：面
bool Utility::IsCollisionRayPlane(TObjectParam obj1, TObjectParam obj2)
{
	DirectX::XMMATRIX mRot = DirectX::XMMatrixRotationX(obj2.collisionData.plane.planeRot.x) * DirectX::XMMatrixRotationY(obj2.collisionData.plane.planeRot.y) *  DirectX::XMMatrixRotationZ(obj2.collisionData.plane.planeRot.z);
	DirectX::XMFLOAT3 Vtx[4] = 
	{
		DirectX::XMFLOAT3(-1, 0,  1),
		DirectX::XMFLOAT3( 1, 0,  1),
		DirectX::XMFLOAT3(-1 ,0, -1),
		DirectX::XMFLOAT3( 1, 0, -1)
	};
	for (int i = 0; i < 4; i++)
	{
		DirectX::XMVECTOR vVtx = DirectX::XMVector3TransformCoord(DirectX::XMLoadFloat3(&Vtx[i]), mRot);
		vVtx = DirectX::XMVectorScale(vVtx, sqrtf(powf(obj2.collisionData.plane.planeSize.x / 2.0f, 2) + powf(obj2.collisionData.plane.planeSize.y / 2.0f, 2)));
		DirectX::XMStoreFloat3(&Vtx[i],vVtx);
	}
	DirectX::XMVECTOR vRayStart = DirectX::XMLoadFloat3(&obj1.collisionData.ray.rayStart);
	DirectX::XMVECTOR vRayN = obj1.collisionData.ray.rayDirection;
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
		DirectX::XMVECTOR vTriStart = DirectX::XMLoadFloat3(&Vtx[0]);
		DirectX::XMVECTOR vTriEnd;
		DirectX::XMVECTOR vTriEdge;
		DirectX::XMVECTOR vToPoint;
		DirectX::XMVECTOR vDot[3];
		float match[3];

		// 1つ目
		for (int i = 0; i < 3; ++i)
		{
			vTriEnd = DirectX::XMLoadFloat3(&Vtx[(i + 1) % 3]);
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
		vTriStart = DirectX::XMLoadFloat3(&Vtx[1]);
		for (int i = 0; i < 3; ++i)
		{
			vTriEnd = DirectX::XMLoadFloat3(&Vtx[3 - i]);
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

// 未実
// 面：面
bool Utility::IsCollisionPlane(TObjectParam obj1, TObjectParam obj2)
{
	return false;
}

// 未
// レイ：面
DirectX::XMFLOAT3 Utility::GetTargetPlane(TObjectParam obj1, TObjectParam obj2)
{
	DirectX::XMMATRIX mRot = DirectX::XMMatrixRotationX(obj2.collisionData.plane.planeRot.x) * DirectX::XMMatrixRotationY(obj2.collisionData.plane.planeRot.y) *  DirectX::XMMatrixRotationZ(obj2.collisionData.plane.planeRot.z);
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
		vVtx = DirectX::XMVectorScale(vVtx, sqrtf(powf(obj2.collisionData.plane.planeSize.x / 2.0f, 2) + powf(obj2.collisionData.plane.planeSize.y / 2.0f, 2)));
		DirectX::XMStoreFloat3(&Vtx[i], vVtx);
	}

	DirectX::XMVECTOR vRayStart = DirectX::XMLoadFloat3(&obj1.collisionData.ray.rayStart);
	DirectX::XMVECTOR vRayN = obj1.collisionData.ray.rayDirection;
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
	DirectX::XMVECTOR vToEnd = DirectX::XMVectorScale(vRayN, obj1.collisionData.ray.rayLength);
	vToEnd = DirectX::XMVectorAdd(vToEnd, vToStart);
	DirectX::XMStoreFloat(&P2, DirectX::XMVector3Dot(vPlaneN, vToEnd));

	DirectX::XMFLOAT3 point;
	float dist = obj1.collisionData.ray.rayLength *(P1 / (P1 - P2));
	DirectX::XMStoreFloat3(&point, DirectX::XMVectorAdd(DirectX::XMVectorScale(vRayN, dist), vRayStart));

	return point;
}