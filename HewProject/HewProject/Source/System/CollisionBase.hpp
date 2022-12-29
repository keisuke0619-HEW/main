#pragma once
#include <IObjectBase.hpp>

struct Triangle
{
	DirectX::XMFLOAT3 p[3];			// 三角形の座標
};

namespace Utility
{
	/// オブジェクト(All)とオブジェクト(All)の当たり判定
	bool IsCollision(TObjectParam obj1, TObjectParam obj2);

	/// オブジェクト(Shpire)とオブジェクト(Shpire)の当たり判定
	bool IsCollisionShpire(TObjectParam obj1, TObjectParam obj2);

	/// オブジェクト(Shpire)とオブジェクト(Ray)の当たり判定
	bool IsCollisionShpireRay(TObjectParam obj1, TObjectParam obj2);

	/// オブジェクト(Shpire)とオブジェクト(Plane)の当たり判定
	bool IsCollisionShpirePlane(TObjectParam obj1, TObjectParam obj2);

	/// オブジェクト(Ray)とオブジェクト(Ray)の当たり判定
	bool IsCollisionRay(TObjectParam obj1, TObjectParam obj2);

	/// オブジェクト(Ray)とオブジェクト(Plane)の当たり判定
	bool IsCollisionRayPlane(TObjectParam obj1, TObjectParam obj2);

	/// オブジェクト(Plane)とオブジェクト(Plane)の当たり判定
	bool IsCollisionPlane(TObjectParam obj1, TObjectParam obj2);

	/// オブジェクト(Ray)とオブジェクト(Plane)の当たり判定 (使用非推奨)
	DirectX::XMFLOAT3 GetTargetPlane(TObjectParam obj1, TObjectParam obj2);
}