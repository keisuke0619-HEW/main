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
	// 必要な場合はここにタグを追記する
};

enum ECollisionType
{
	COLLISION_NONE,		// 当たり判定を使用しない
	COLLISION_BOX,		// 箱の当たり判定
	COLLISION_SPHIRE,	// 球の当たり判定
	// 新たに当たり判定の種類を作る場合はここに追加する。
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
	virtual TObjectParam GetParam() = 0;

	virtual ~IObjectBase() {}

};