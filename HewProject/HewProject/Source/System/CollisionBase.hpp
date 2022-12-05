#pragma once
#include <IObjectBase.hpp>

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