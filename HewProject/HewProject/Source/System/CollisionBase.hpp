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

	/// キャラクター同士
	bool IsCollision_C_to_C(TObjectParam obj1, TObjectParam obj2);

	/// キャラクターと障害物
	bool IsCollision_C_to_O(TObjectParam obj1, TObjectParam obj2);

	/// キャラクターと面
	bool IsCollision_C_to_P(TObjectParam obj1, TObjectParam obj2);
	
	/// カメラとオブジェクト(Plane)の当たり判定 (使用非推奨)
	DirectX::XMFLOAT3 GetTargetPlane(TObjectParam obj1, TObjectParam obj2);
}