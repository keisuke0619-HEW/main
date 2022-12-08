#include "CollisionBase.hpp"

bool Utility::IsCollision(TObjectParam obj1, TObjectParam obj2)
{
    // 引数として渡されたデータをもとに当たり判定をとる。




    // 当たっていたらTrue
    // 当たっていなかったらFalse
    return false;
}

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

bool Utility::IsCollisionBoxNoRotation(TObjectParam obj1, TObjectParam obj2)
{
	struct data
	{
		float x;
		float y;
		float z;
		float width;
		float height;
		float depth;
	};
	data A;
	A.x = obj1.pos.x;
	A.y = obj1.pos.y;
	A.z = obj1.pos.z;
	A.width = obj1.collisionData.boxScale[0];
	A.height = obj1.collisionData.boxScale[1];
	A.depth = obj1.collisionData.boxScale[2];
	data B;
	B.x = obj2.pos.x;
	B.y = obj2.pos.y;
	B.z = obj2.pos.z;
	B.width = obj2.collisionData.boxScale[0];
	B.height = obj2.collisionData.boxScale[1];
	B.depth = obj2.collisionData.boxScale[2];
	// AとBを使って０８番「当たり判定」プリントを参考に。

	if (A.x + A.width * 0.5f >= B.x - B.width * 0.5f &&
		A.x - A.width * 0.5f <= B.x + B.width * 0.5f)
	{
		if (A.y + A.height * 0.5f >= B.y - B.height * 0.5f &&
			A.y - A.height * 0.5f <= B.y + B.height * 0.5f)
		{
			if (A.z + A.depth * 0.5f >= B.z - B.depth * 0.5f &&
				A.z - A.depth * 0.5f <= B.z + B.depth * 0.5f)
			{
				return true;
			}
		}
	}

	return false;
}

//bool Utility::IsCollisionBox(TObjectParam obj1, TObjectParam obj2, TObjectParam objSize1, TObjectParam objSize2)
//{
//	DirectX::XMFLOAT3 halfSize1 = { objSize1.pos.x / 2.0f, objSize1.pos.y / 2.0f, objSize1.pos.z / 2.0f };
//	DirectX::XMFLOAT3 halfSize2 = { objSize2.pos.x / 2.0f, objSize2.pos.y / 2.0f, objSize2.pos.z / 2.0f };
//
//	if ((obj2.pos.x - halfSize2.x < obj1.pos.x + halfSize1.x) &&
//		(obj1.pos.x - halfSize1.x < obj2.pos.x + halfSize2.x))
//	{
//		if ((obj2.pos.z - halfSize2.z < obj1.pos.z + halfSize1.z) &&
//			(obj1.pos.z - halfSize1.z < obj2.pos.z + halfSize2.z))
//		{
//			if ((obj2.pos.y - halfSize2.y < obj1.pos.y + halfSize1.y) &&
//				(obj1.pos.y - halfSize1.y < obj2.pos.y + halfSize2.y))
//			{
//				return true;
//			}
//		}
//	}
//
//	return false;
//}
