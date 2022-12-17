#pragma once
#include <DirectXMath.h>
#include <memory>
#include <string>
enum EObjectTag
{
	TAG_NONE,
	TAG_PLAYER,
	TAG_CAMERA,
	TAG_ENEMY,
	TAG_BEAM,
	TAG_SHOCK,	// 衝撃波
	TAG_STATIC_OBJECT,	// 移動しないオブジェクト（Static同士の判定はしない）
	// 必要な場合はここにタグを追記する
};

enum ECollisionType
{
	COLLISION_NONE,		// 当たり判定を使用しない
	COLLISION_SPHIRE,	// 球の当たり判定
	COLLISION_RAY,		// レイの当たり判定
	COLLISION_PLANE,	// 板の当たり判定
	// 新たに当たり判定の種類を作る場合はここに追加する。
};

struct SphireData
{
	DirectX::XMFLOAT3 sphirePos;	// 球の中心
	float sphireRadius;				// 球の半径
};

struct RayData
{
	DirectX::XMFLOAT3 rayStart;		// レイの開始点
	DirectX::XMVECTOR rayDirection;	// レイの方向
	float rayLength;				// レイの長さ
};

struct PlaneData
{
	DirectX::XMFLOAT3 planePos;		// 面の中心座標	()
	DirectX::XMFLOAT2 planeSize;	// 面の横縦		(x:横,y:縦)
	DirectX::XMFLOAT3 planeRot;		// 面の角度		(デフォルトは法線ベクトル上向き。軸回転。45°のときは 45 でOK)
};

union UCollisionData
{
	SphireData sphire;		// 球の情報
	RayData ray;			// レイの情報
	PlaneData plane;		// 面の情報
};

struct TObjectParam
{
	// オブジェクト座標
	DirectX::XMFLOAT3 pos;
	// オブジェクトの速度
	DirectX::XMFLOAT3 move;
	// オブジェクトの加速度
	DirectX::XMFLOAT3 accel;
	// オブジェクトの回転
	DirectX::XMFLOAT3 rot;
	// オブジェクトの拡大率
	DirectX::XMFLOAT3 scale;
	// オブジェクトのタググループ（上の列挙体）
	EObjectTag tag;
	// 生成からの経過フレーム
	int frame;
	// 名前
	std::string name;
	// 削除フラグ
	bool isDestroy;
	// 当たり判定設定
	ECollisionType collisionType;
	// 当たり判定データ
	UCollisionData collisionData;
	// 描画のオフセット
	DirectX::XMFLOAT3 drawOffset;
	// 体力
	float hp;
};

/// <summary>
/// オブジェクトとマネージャーをつなぐインタフェースクラス（よくわかってない）
/// </summary>
class IObjectBase
{
public:
	using Ptr = std::shared_ptr<IObjectBase>;
	using Ref = std::weak_ptr<IObjectBase>;
	
public:
	virtual void BaseUpdate() = 0;
	virtual void BaseDraw() = 0;
	virtual void OnCollision(Ptr collisionObj) = 0;
	virtual void OnCollisionTag(EObjectTag tag) = 0;
	virtual TObjectParam GetParam() = 0;
	

	virtual ~IObjectBase() {}

};