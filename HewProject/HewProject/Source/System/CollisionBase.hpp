#pragma once
#include <IObjectBase.hpp>

// データの取得
struct Box
{
	DirectX::XMFLOAT3 pos;			//  中心座標
	DirectX::XMFLOAT3 size;			//  サイズ
	DirectX::XMFLOAT3 rot;			//  回転
};

struct Shpire
{
	DirectX::XMFLOAT3 pos;			//  中心座標
	float radius;					//  半径
};

struct Plane
{
	DirectX::XMFLOAT3 normal;		//	面の法線
	DirectX::XMFLOAT3 vtx[4];		//	頂点の座標
};

struct Ray
{
	DirectX::XMFLOAT3 start;		//	レイの開始点
	DirectX::XMVECTOR direction;	//	レイの方向
	float length;					//	レイの長さ
};

struct Triangle
{
	DirectX::XMFLOAT3 p[3];			// 三角形の座標
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
	


	/// pointがオブジェクトの内部にあるか
	bool IsIncludPoint(DirectX::XMFLOAT3 point, TObjectParam obj);

	/// 線と面の当たり判定
	bool IsCollisionRayPlane(Ray ray, Plane plane);

	/// レイとオブジェクト(Box)の当たり判定
	bool IsCollisionRayBox(Ray ray, TObjectParam obj);

	/// オブジェクト(Box)とオブジェクト(Box)の当たり判定
	bool IsCollisionBox(TObjectParam obj1, TObjectParam obj2);

	/// オブジェクト(Shpire)とオブジェクト(Box)の当たり判定
	bool IsCollisionShpireBox(TObjectParam obj1, TObjectParam obj2);

}