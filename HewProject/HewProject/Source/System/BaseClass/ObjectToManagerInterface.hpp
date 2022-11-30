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
};

/// <summary>
/// オブジェクトとマネージャーをつなぐインタフェースクラス（よくわかってない）
/// </summary>
class IObjectToManager
{
public:
	using Ptr = std::shared_ptr<IObjectToManager>;
	using Ref = std::weak_ptr<IObjectToManager>;
public:
	virtual void BaseUpdate() = 0;
	virtual void BaseDraw() = 0;
	virtual TObjectParam GetParam() = 0;

	virtual ~IObjectToManager() {}

};