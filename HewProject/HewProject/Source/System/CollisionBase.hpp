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
	
	/// <summary>
	/// オブジェクト１と２が衝突していたらTrueを返す
	/// </summary>
	/// <param name="obj1">オブジェクト１のデータ</param>
	/// <param name="obj2">オブジェクト２のデータ</param>
	/// <returns>当たっていたらTrue・当たっていなかったらFalse</returns>
	bool IsCollisionShpire(TObjectParam obj1, TObjectParam obj2);

	/// <summary>
	/// オブジェクト１と２が衝突していたらTrueを返す
	/// </summary>
	/// <param name="obj1">オブジェクト１のデータ</param>
	/// <param name="obj2">オブジェクト２のデータ</param>
	/// <returns>当たっていたらTrue・当たっていなかったらFalse</returns>
	bool IsCollisionBoxNoRotation(TObjectParam obj1, TObjectParam obj2);

	//bool IsCollisionBox(TObjectParam obj1, TObjectParam obj2, TObjectParam objSize1, TObjectParam objSize2);

}