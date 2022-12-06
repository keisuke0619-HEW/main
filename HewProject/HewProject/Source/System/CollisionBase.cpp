#include "CollisionBase.hpp"

bool Utility::IsCollision(TObjectParam obj1, TObjectParam obj2)
{
    // 引数として渡されたデータをもとに当たり判定をとる。




    // 当たっていたらTrue
    // 当たっていなかったらFalse
    return false;
}

bool Utility::IsCollisionCircle(TObjectParam obj1, TObjectParam obj2, float Rad1, float Rad2)
{
	if ((obj1.pos.x - obj2.pos.x) * (obj1.pos.x - obj2.pos.x) +
		(obj1.pos.y - obj2.pos.y) * (obj1.pos.y - obj2.pos.y) +
		(obj1.pos.z - obj2.pos.z) * (obj1.pos.z - obj2.pos.z)
		<= (Rad1 + Rad2) * (Rad1 + Rad2) *(Rad1 + Rad2))
	{
		return true;
	}

	return false;
}

bool Utility::IsCollisionBox(TObjectParam obj1, TObjectParam obj2, TObjectParam objSize1, TObjectParam objSize2)
{
	DirectX::XMFLOAT3 halfSize1 = { objSize1.pos.x / 2.0f, objSize1.pos.y / 2.0f, objSize1.pos.z / 2.0f };
	DirectX::XMFLOAT3 halfSize2 = { objSize2.pos.x / 2.0f, objSize2.pos.y / 2.0f, objSize2.pos.z / 2.0f };

	if ((obj2.pos.x - halfSize2.x < obj1.pos.x + halfSize1.x) &&
		(obj1.pos.x - halfSize1.x < obj2.pos.x + halfSize2.x))
	{
		if ((obj2.pos.z - halfSize2.z < obj1.pos.z + halfSize1.z) &&
			(obj1.pos.z - halfSize1.z < obj2.pos.z + halfSize2.z))
		{
			if ((obj2.pos.y - halfSize2.y < obj1.pos.z + halfSize1.z) &&
				(obj1.pos.y - halfSize1.y < obj2.pos.z + halfSize2.z))
			{
				return true;
			}
		}
	}

	return false;
}
