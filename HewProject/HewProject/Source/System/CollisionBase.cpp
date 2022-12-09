#include "CollisionBase.hpp"

/// 完了
bool Utility::IsCollision(TObjectParam obj1, TObjectParam obj2)
{
    // 引数として渡されたデータをもとに当たり判定をとる。
    // 当たっていたらTrue
    // 当たっていなかったらFalse

	switch (obj1.collisionType)
	{
	case COLLISION_BOX:
		switch (obj2.collisionType)
		{
		case COLLISION_BOX:
			return Utility::IsCollisionBox(obj1, obj2);
			break;
		case COLLISION_SPHIRE:
			return Utility::IsCollisionBoxShpire(obj1, obj2);
			break;
		case COLLISION_RAY:
			return Utility::IsCollisionBoxRay(obj1, obj2);
			break;
		case COLLISION_PLANE:
			return Utility::IsCollisionBoxPlane(obj1, obj2);
			break;
		default:
			break;
		}
		break;
	case COLLISION_SPHIRE:
		switch (obj2.collisionType)
		{
		case COLLISION_BOX:
			return Utility::IsCollisionBoxShpire(obj2, obj1);
			break;
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
		case COLLISION_BOX:
			return Utility::IsCollisionBoxRay(obj2, obj1);
			break;
		case COLLISION_SPHIRE:
			return Utility::IsCollisionShpireRay(obj2, obj1);
			break;
		case COLLISION_RAY:
			///
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
		case COLLISION_BOX:
			return Utility::IsCollisionBoxPlane(obj2, obj1);
			break;
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

/// 完了
bool Utility::IsCollisionBoxNoRotation(TObjectParam obj1, TObjectParam obj2)
{
	Box Box1 = { obj1.pos, obj1.collisionData.boxScale };
	Box Box2 = { obj2.pos, obj2.collisionData.boxScale };

	// AとBを使って０８番「当たり判定」プリントを参考に。

	if (Box1.pos.x + Box1.size.x * 0.5f >= Box2.pos.x - Box2.size.x * 0.5f &&
		Box1.pos.x - Box1.size.x * 0.5f <= Box2.pos.x + Box2.size.x * 0.5f)
	{
		if (Box1.pos.y + Box1.size.y * 0.5f >= Box2.pos.y - Box2.size.y * 0.5f &&
			Box1.pos.y - Box1.size.y * 0.5f <= Box2.pos.y + Box2.size.y * 0.5f)
		{
			if (Box1.pos.z + Box1.size.z * 0.5f >= Box2.pos.z - Box2.size.z * 0.5f &&
				Box1.pos.z - Box1.size.z * 0.5f <= Box2.pos.z + Box2.size.z * 0.5f)
			{
				return true;
			}
		}
	}

	return false;
}

/// 完了
bool Utility::IsIncludPoint(DirectX::XMFLOAT3 point, TObjectParam obj)
{
	/// レイの作成
	TObjectParam ray;

	switch (obj.collisionType)
	{
	case COLLISION_BOX:
		ray.collisionType = COLLISION_RAY;
		ray.collisionData.ray.rayStart = point;
		ray.collisionData.ray.rayDirection = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&obj.pos), DirectX::XMLoadFloat3(&ray.collisionData.ray.rayStart)));
		DirectX::XMStoreFloat(&ray.collisionData.ray.rayLength, DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&obj.pos), DirectX::XMLoadFloat3(&ray.collisionData.ray.rayStart)));

		if (Utility::IsCollisionBoxRay(obj, ray))
		{
			return true;
		}
		break;
	case COLLISION_SPHIRE:
		if ((point.x - obj.pos.x) * (point.x - obj.pos.x) +
			(point.y - obj.pos.y) * (point.y - obj.pos.y) +
			(point.z - obj.pos.z) * (point.z - obj.pos.z)
			<= powf(obj.collisionData.sphireRadius, 3))
		{
			return true;
		}
		break;
	}

	return false;
}

/// 完了
bool Utility::IsCollisionBox(TObjectParam obj1, TObjectParam obj2)
{
	DirectX::XMFLOAT3 half[2] =
	{
		{
			obj1.collisionData.boxScale.x * 0.5f,
			obj1.collisionData.boxScale.y * 0.5f,
			obj1.collisionData.boxScale.z * 0.5f
		},
		{
			obj2.collisionData.boxScale.x * 0.5f,
			obj2.collisionData.boxScale.y * 0.5f,
			obj2.collisionData.boxScale.z * 0.5f
		}
	};

	DirectX::XMFLOAT3 vtx[2][8] =
	{
		{
			DirectX::XMFLOAT3(-1,1,1),DirectX::XMFLOAT3(1,1,1),DirectX::XMFLOAT3(-1,1,-1),
			DirectX::XMFLOAT3(1,1,-1),DirectX::XMFLOAT3(-1,-1,1),DirectX::XMFLOAT3(1,-1,1),
			DirectX::XMFLOAT3(-1,-1,-1),DirectX::XMFLOAT3(1,-1,-1)
		},
		{
			DirectX::XMFLOAT3(-1,1,1),DirectX::XMFLOAT3(1,1,1),DirectX::XMFLOAT3(-1,1,-1),
			DirectX::XMFLOAT3(1,1,-1),DirectX::XMFLOAT3(-1,-1,1),DirectX::XMFLOAT3(1,-1,1),
			DirectX::XMFLOAT3(-1,-1,-1),DirectX::XMFLOAT3(1,-1,-1)
		}
	};

	TObjectParam ray[2][8];

	for (int i = 0; i < 8; i++)
	{
		ray[0][i] = obj1;
		ray[1][i] = obj2;

		ray[0][i].collisionType = COLLISION_RAY;
		ray[1][i].collisionType = COLLISION_RAY;

		DirectX::XMVECTOR pos = DirectX::XMVectorSet(
			half[0].x * 0.5f * vtx[0][i].x,
			half[0].y * 0.5f * vtx[0][i].y,
			half[0].z * 0.5f * vtx[0][i].z,
			0.0f
		);

		pos = DirectX::XMVector3TransformCoord(pos, DirectX::XMMatrixRotationX(obj1.rot.x) * DirectX::XMMatrixRotationY(obj1.rot.y) *  DirectX::XMMatrixRotationZ(obj1.rot.z));
		DirectX::XMStoreFloat3(&vtx[0][i], DirectX::XMVectorAdd(pos, DirectX::XMLoadFloat3(&obj1.pos)));

		pos = DirectX::XMVectorSet(
			half[1].x * 0.5f * vtx[1][i].x,
			half[1].y * 0.5f * vtx[1][i].y,
			half[1].z * 0.5f * vtx[1][i].z,
			0.0f
		);

		pos = DirectX::XMVector3TransformCoord(pos, DirectX::XMMatrixRotationX(obj2.rot.x) * DirectX::XMMatrixRotationY(obj2.rot.y) *  DirectX::XMMatrixRotationZ(obj2.rot.z));
		DirectX::XMStoreFloat3(&vtx[1][i], DirectX::XMVectorAdd(pos, DirectX::XMLoadFloat3(&obj2.pos)));

		ray[0][i].collisionData.ray.rayStart = obj1.pos;
		ray[1][i].collisionData.ray.rayStart = obj2.pos;

		ray[0][i].collisionData.ray.rayDirection = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&vtx[0][i]), DirectX::XMLoadFloat3(&obj1.pos)));
		ray[1][i].collisionData.ray.rayDirection = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&vtx[1][i]), DirectX::XMLoadFloat3(&obj2.pos)));

		DirectX::XMStoreFloat(&ray[0][i].collisionData.ray.rayLength, DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&vtx[0][i]), DirectX::XMLoadFloat3(&obj1.pos)));
		DirectX::XMStoreFloat(&ray[1][i].collisionData.ray.rayLength, DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&vtx[1][i]), DirectX::XMLoadFloat3(&obj2.pos)));
	}

	for (int i = 0; i < 8; i++)
	{

		if (Utility::IsCollisionBoxRay(obj2, ray[0][i]))
		{
			return true;
		}

		if (Utility::IsCollisionBoxRay(obj1, ray[1][i]))
		{
			return true;
		}
	}

	return false;
}

/// 完了
bool Utility::IsCollisionBoxShpire(TObjectParam obj1, TObjectParam obj2)
{
	TObjectParam ray;
	ray.collisionType = COLLISION_RAY;
	ray.collisionData.ray.rayStart = obj2.collisionData.ray.rayStart;
	ray.collisionData.ray.rayDirection = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&obj1.pos), DirectX::XMLoadFloat3(&obj2.pos)));
	ray.collisionData.ray.rayLength = obj2.collisionData.sphireRadius;

	if (Utility::IsCollisionBoxRay(obj1, ray))
	{
		return true;
	}

	DirectX::XMFLOAT3 vtx[8] =
	{
		DirectX::XMFLOAT3(-1,1,1),DirectX::XMFLOAT3(1,1,1),DirectX::XMFLOAT3(-1,1,-1),
		DirectX::XMFLOAT3(1,1,-1),DirectX::XMFLOAT3(-1,-1,1),DirectX::XMFLOAT3(1,-1,1),
		DirectX::XMFLOAT3(-1,-1,-1),DirectX::XMFLOAT3(1,-1,-1)
	};

	for (int i = 0; i < 8; i++)
	{
		DirectX::XMVECTOR pos = DirectX::XMVectorSet(
			obj1.collisionData.boxScale.x * 0.5f * vtx[i].x,
			obj1.collisionData.boxScale.y * 0.5f * vtx[i].y,
			obj1.collisionData.boxScale.z * 0.5f * vtx[i].z,
			0.0f
		);
		pos = DirectX::XMVector3TransformCoord(pos, DirectX::XMMatrixRotationX(obj1.rot.x) * DirectX::XMMatrixRotationY(obj1.rot.y) *  DirectX::XMMatrixRotationZ(obj1.rot.z));
		DirectX::XMStoreFloat3(&vtx[i], DirectX::XMVectorAdd(pos, DirectX::XMLoadFloat3(&obj1.pos)));
	}

	// 1
	ray.collisionData.ray.rayStart = vtx[0];
	ray.collisionData.ray.rayDirection = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&vtx[1]), DirectX::XMLoadFloat3(&vtx[0])));
	DirectX::XMStoreFloat(&ray.collisionData.ray.rayLength, DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&vtx[1]), DirectX::XMLoadFloat3(&vtx[0])));
	if (Utility::IsCollisionShpireRay(obj2, ray))
	{
		return true;
	}

	// 2
	ray.collisionData.ray.rayStart = vtx[0];
	ray.collisionData.ray.rayDirection = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&vtx[2]), DirectX::XMLoadFloat3(&vtx[0])));
	DirectX::XMStoreFloat(&ray.collisionData.ray.rayLength, DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&vtx[2]), DirectX::XMLoadFloat3(&vtx[0])));
	if (Utility::IsCollisionShpireRay(obj2, ray))
	{
		return true;
	}

	// 3
	ray.collisionData.ray.rayStart = vtx[0];
	ray.collisionData.ray.rayDirection = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&vtx[4]), DirectX::XMLoadFloat3(&vtx[0])));
	DirectX::XMStoreFloat(&ray.collisionData.ray.rayLength, DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&vtx[4]), DirectX::XMLoadFloat3(&vtx[0])));
	if (Utility::IsCollisionShpireRay(obj2, ray))
	{
		return true;
	}

	// 4
	ray.collisionData.ray.rayStart = vtx[3];
	ray.collisionData.ray.rayDirection = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&vtx[1]), DirectX::XMLoadFloat3(&vtx[3])));
	DirectX::XMStoreFloat(&ray.collisionData.ray.rayLength, DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&vtx[1]), DirectX::XMLoadFloat3(&vtx[3])));
	if (Utility::IsCollisionShpireRay(obj2, ray))
	{
		return true;
	}

	// 5
	ray.collisionData.ray.rayStart = vtx[3];
	ray.collisionData.ray.rayDirection = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&vtx[2]), DirectX::XMLoadFloat3(&vtx[3])));
	DirectX::XMStoreFloat(&ray.collisionData.ray.rayLength, DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&vtx[2]), DirectX::XMLoadFloat3(&vtx[3])));
	if (Utility::IsCollisionShpireRay(obj2, ray))
	{
		return true;
	}

	// 6
	ray.collisionData.ray.rayStart = vtx[3];
	ray.collisionData.ray.rayDirection = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&vtx[7]), DirectX::XMLoadFloat3(&vtx[3])));
	DirectX::XMStoreFloat(&ray.collisionData.ray.rayLength, DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&vtx[7]), DirectX::XMLoadFloat3(&vtx[3])));
	if (Utility::IsCollisionShpireRay(obj2, ray))
	{
		return true;
	}

	// 7
	ray.collisionData.ray.rayStart = vtx[6];
	ray.collisionData.ray.rayDirection = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&vtx[4]), DirectX::XMLoadFloat3(&vtx[6])));
	DirectX::XMStoreFloat(&ray.collisionData.ray.rayLength, DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&vtx[4]), DirectX::XMLoadFloat3(&vtx[6])));
	if (Utility::IsCollisionShpireRay(obj2, ray))
	{
		return true;
	}

	// 8
	ray.collisionData.ray.rayStart = vtx[6];
	ray.collisionData.ray.rayDirection = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&vtx[7]), DirectX::XMLoadFloat3(&vtx[6])));
	DirectX::XMStoreFloat(&ray.collisionData.ray.rayLength, DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&vtx[7]), DirectX::XMLoadFloat3(&vtx[6])));
	if (Utility::IsCollisionShpireRay(obj2, ray))
	{
		return true;
	}

	// 9
	ray.collisionData.ray.rayStart = vtx[6];
	ray.collisionData.ray.rayDirection = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&vtx[2]), DirectX::XMLoadFloat3(&vtx[6])));
	DirectX::XMStoreFloat(&ray.collisionData.ray.rayLength, DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&vtx[2]), DirectX::XMLoadFloat3(&vtx[6])));
	if (Utility::IsCollisionShpireRay(obj2, ray))
	{
		return true;
	}

	// 10
	ray.collisionData.ray.rayStart = vtx[5];
	ray.collisionData.ray.rayDirection = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&vtx[4]), DirectX::XMLoadFloat3(&vtx[5])));
	DirectX::XMStoreFloat(&ray.collisionData.ray.rayLength, DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&vtx[4]), DirectX::XMLoadFloat3(&vtx[5])));
	if (Utility::IsCollisionShpireRay(obj2, ray))
	{
		return true;
	}

	// 11
	ray.collisionData.ray.rayStart = vtx[5];
	ray.collisionData.ray.rayDirection = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&vtx[7]), DirectX::XMLoadFloat3(&vtx[5])));
	DirectX::XMStoreFloat(&ray.collisionData.ray.rayLength, DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&vtx[7]), DirectX::XMLoadFloat3(&vtx[5])));
	if (Utility::IsCollisionShpireRay(obj2, ray))
	{
		return true;
	}

	// 12
	ray.collisionData.ray.rayStart = vtx[5];
	ray.collisionData.ray.rayDirection = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&vtx[1]), DirectX::XMLoadFloat3(&vtx[5])));
	DirectX::XMStoreFloat(&ray.collisionData.ray.rayLength, DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&vtx[1]), DirectX::XMLoadFloat3(&vtx[5])));
	if (Utility::IsCollisionShpireRay(obj2, ray))
	{
		return true;
	}

	return false;
}

/// 完了
bool Utility::IsCollisionBoxRay(TObjectParam obj1, TObjectParam obj2)
{
	DirectX::XMFLOAT3 vtx[8] =
	{
		DirectX::XMFLOAT3(-1,1,1),DirectX::XMFLOAT3(1,1,1),DirectX::XMFLOAT3(-1,1,-1),
		DirectX::XMFLOAT3(1,1,-1),DirectX::XMFLOAT3(-1,-1,1),DirectX::XMFLOAT3(1,-1,1),
		DirectX::XMFLOAT3(-1,-1,-1),DirectX::XMFLOAT3(1,-1,-1)
	};

	for (int i = 0; i < 8; i++)
	{
		DirectX::XMVECTOR pos = DirectX::XMVectorSet(
			obj1.collisionData.boxScale.x * 0.5f * vtx[i].x,
			obj1.collisionData.boxScale.y * 0.5f * vtx[i].y,
			obj1.collisionData.boxScale.z * 0.5f * vtx[i].z,
			0.0f
		);
		pos = DirectX::XMVector3TransformCoord(pos, DirectX::XMMatrixRotationX(obj1.rot.x) * DirectX::XMMatrixRotationY(obj1.rot.y) *  DirectX::XMMatrixRotationZ(obj1.rot.z));
		DirectX::XMStoreFloat3(&vtx[i], DirectX::XMVectorAdd(pos, DirectX::XMLoadFloat3(&obj1.pos)));
	}

	DirectX::XMVECTOR v;
	DirectX::XMMATRIX Rx;
	DirectX::XMMATRIX Ry;
	DirectX::XMMATRIX Rz;

	TObjectParam plane;
	plane = obj1;
	plane.collisionType = COLLISION_PLANE;

	// 上
	plane.collisionData.plane.planeNormal = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
	v = DirectX::XMLoadFloat3(&plane.collisionData.plane.planeNormal);
	Rx = DirectX::XMMatrixRotationX(obj1.rot.x);
	Ry = DirectX::XMMatrixRotationY(obj1.rot.y);
	Rz = DirectX::XMMatrixRotationZ(obj1.rot.z);
	v = DirectX::XMVector3TransformCoord(v, Rx * Ry * Rz);
	v = DirectX::XMVector3Normalize(v);
	DirectX::XMStoreFloat3(&plane.collisionData.plane.planeNormal, v);

	plane.collisionData.plane.planeVtx[0] = vtx[0];
	plane.collisionData.plane.planeVtx[1] = vtx[1];
	plane.collisionData.plane.planeVtx[2] = vtx[2];
	plane.collisionData.plane.planeVtx[3] = vtx[3];

	if (Utility::IsCollisionRayPlane(obj2, plane))
	{
		return true;
	}

	// 下
	plane.collisionData.plane.planeNormal = DirectX::XMFLOAT3(0.0f, -1.0f, 0.0f);
	v = DirectX::XMLoadFloat3(&plane.collisionData.plane.planeNormal);
	Rx = DirectX::XMMatrixRotationX(obj1.rot.x);
	Ry = DirectX::XMMatrixRotationY(obj1.rot.y);
	Rz = DirectX::XMMatrixRotationZ(obj1.rot.z);
	v = DirectX::XMVector3TransformCoord(v, Rx * Ry * Rz);
	v = DirectX::XMVector3Normalize(v);
	DirectX::XMStoreFloat3(&plane.collisionData.plane.planeNormal, v);

	plane.collisionData.plane.planeVtx[0] = vtx[6];
	plane.collisionData.plane.planeVtx[1] = vtx[7];
	plane.collisionData.plane.planeVtx[2] = vtx[4];
	plane.collisionData.plane.planeVtx[3] = vtx[5];

	if (Utility::IsCollisionRayPlane(obj2, plane))
	{
		return true;
	}

	// 前
	plane.collisionData.plane.planeNormal = DirectX::XMFLOAT3(0.0f, 0.0f, -1.0f);
	v = DirectX::XMLoadFloat3(&plane.collisionData.plane.planeNormal);
	Rx = DirectX::XMMatrixRotationX(obj1.rot.x);
	Ry = DirectX::XMMatrixRotationY(obj1.rot.y);
	Rz = DirectX::XMMatrixRotationZ(obj1.rot.z);
	v = DirectX::XMVector3TransformCoord(v, Rx * Ry * Rz);
	v = DirectX::XMVector3Normalize(v);
	DirectX::XMStoreFloat3(&plane.collisionData.plane.planeNormal, v);

	plane.collisionData.plane.planeVtx[0] = vtx[2];
	plane.collisionData.plane.planeVtx[1] = vtx[3];
	plane.collisionData.plane.planeVtx[2] = vtx[6];
	plane.collisionData.plane.planeVtx[3] = vtx[7];

	if (Utility::IsCollisionRayPlane(obj2, plane))
	{
		return true;
	}

	// 後
	plane.collisionData.plane.planeNormal = DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f);
	v = DirectX::XMLoadFloat3(&plane.collisionData.plane.planeNormal);
	Rx = DirectX::XMMatrixRotationX(obj1.rot.x);
	Ry = DirectX::XMMatrixRotationY(obj1.rot.y);
	Rz = DirectX::XMMatrixRotationZ(obj1.rot.z);
	v = DirectX::XMVector3TransformCoord(v, Rx * Ry * Rz);
	v = DirectX::XMVector3Normalize(v);
	DirectX::XMStoreFloat3(&plane.collisionData.plane.planeNormal, v);

	plane.collisionData.plane.planeVtx[0] = vtx[1];
	plane.collisionData.plane.planeVtx[1] = vtx[0];
	plane.collisionData.plane.planeVtx[2] = vtx[5];
	plane.collisionData.plane.planeVtx[3] = vtx[4];

	if (Utility::IsCollisionRayPlane(obj2, plane))
	{
		return true;
	}

	// 左
	plane.collisionData.plane.planeNormal = DirectX::XMFLOAT3(-1.0f, 0.0f, 0.0f);
	v = DirectX::XMLoadFloat3(&plane.collisionData.plane.planeNormal);
	Rx = DirectX::XMMatrixRotationX(obj1.rot.x);
	Ry = DirectX::XMMatrixRotationY(obj1.rot.y);
	Rz = DirectX::XMMatrixRotationZ(obj1.rot.z);
	v = DirectX::XMVector3TransformCoord(v, Rx * Ry * Rz);
	v = DirectX::XMVector3Normalize(v);
	DirectX::XMStoreFloat3(&plane.collisionData.plane.planeNormal, v);

	plane.collisionData.plane.planeVtx[0] = vtx[0];
	plane.collisionData.plane.planeVtx[1] = vtx[2];
	plane.collisionData.plane.planeVtx[2] = vtx[4];
	plane.collisionData.plane.planeVtx[3] = vtx[6];

	if (Utility::IsCollisionRayPlane(obj2, plane))
	{
		return true;
	}

	// 右
	plane.collisionData.plane.planeNormal = DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f);
	v = DirectX::XMLoadFloat3(&plane.collisionData.plane.planeNormal);
	Rx = DirectX::XMMatrixRotationX(obj1.rot.x);
	Ry = DirectX::XMMatrixRotationY(obj1.rot.y);
	Rz = DirectX::XMMatrixRotationZ(obj1.rot.z);
	v = DirectX::XMVector3TransformCoord(v, Rx * Ry * Rz);
	v = DirectX::XMVector3Normalize(v);
	DirectX::XMStoreFloat3(&plane.collisionData.plane.planeNormal, v);

	plane.collisionData.plane.planeVtx[0] = vtx[3];
	plane.collisionData.plane.planeVtx[1] = vtx[1];
	plane.collisionData.plane.planeVtx[2] = vtx[7];
	plane.collisionData.plane.planeVtx[3] = vtx[5];

	if (Utility::IsCollisionRayPlane(obj2, plane))
	{
		return true;
	}

	return false;
}

/// 未実装
bool Utility::IsCollisionBoxPlane(TObjectParam obj1, TObjectParam obj2)
{
	return false;
}

/// 完了
bool Utility::IsCollisionShpire(TObjectParam obj1, TObjectParam obj2)
{
    if ((obj1.pos.x - obj2.pos.x) * (obj1.pos.x - obj2.pos.x) +
		(obj1.pos.y - obj2.pos.y) * (obj1.pos.y - obj2.pos.y) +
		(obj1.pos.z - obj2.pos.z) * (obj1.pos.z - obj2.pos.z)
		<= powf(obj1.collisionData.sphireRadius + obj2.collisionData.sphireRadius, 3))
	{
		return true;
	}

	return false;
}

/// 完了
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

	if (h <= obj1.collisionData.sphireRadius)
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

/// 完了
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