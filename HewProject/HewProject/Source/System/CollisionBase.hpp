#pragma once
#include <IObjectBase.hpp>

enum ECollisionType
{
	COLLISION_NONE,		// 当たり判定を使用しない
	COLLISION_BOX,		// 箱の当たり判定
	COLLISION_SPHIRE,	// 球の当たり判定
	// 新たに当たり判定の種類を作る場合はここに追加する。
};

namespace Utility
{
	/// <summary>
	/// オブジェクト１と２が衝突していたらTrueを返す
	/// </summary>
	/// <param name="obj1">オブジェクト１のデータ</param>
	/// <param name="obj2">オブジェクト２のデータ</param>
	/// <returns>当たっていたらTrue・当たっていなかったらFalse</returns>
	bool IsCollision(TObjectParam obj1, TObjectParam obj2);
}