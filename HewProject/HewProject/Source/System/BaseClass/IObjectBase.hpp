#pragma once
#include <DirectXMath.h>
#include <Model.h>
#include <ConstantBuffer.h>
#include <memory>
#include <string>
enum EObjectTag
{
	TAG_NONE,
	TAG_PLAYER,
	TAG_CAMERA,
	TAG_ENEMY,
	TAG_ENEMY_BOSS,
	TAG_BEAM,
	TAG_SHOCK,	// 衝撃波
	TAG_STATIC_OBJECT,	// 移動しないオブジェクト（Static同士の判定はしない）
	// 必要な場合はここにタグを追記する
};

enum ECollisionType
{
	COLLISION_NONE,			// 当たり判定を使用しない

	COLLISION_CHARACTER,	// キャラクターの当たり判定	(円柱)
	COLLISION_OBSTACLES,	// 障害物の当たり判定		(立方体)
	COLLISION_CAMERARAY,	// カメラのレイの当たり判定	(レイ)
	COLLISION_PLANE,		// 板の当たり判定			(面)

	// 新たに当たり判定の種類を作る場合はここに追加する。
};

struct CharacterData
{
	DirectX::XMFLOAT3 pos;			// キャラクターの中心座標
	float radius;					// キャラクターの半径
};

struct ObstaclesData
{
	DirectX::XMFLOAT3 pos;			// 障害物の座標
	DirectX::XMFLOAT2 size;			// 障害物のサイズ	(X:横、Y:縦、高さはいらない)
	bool spin;						// 障害物の回転		(true:あり、false:なし)
};

struct RayData
{
	DirectX::XMFLOAT3 start;		// カメラレイの開始点
	DirectX::XMVECTOR direction;	// カメラレイの方向
	float length;					// カメラレイの長さ
};

struct PlaneData
{
	DirectX::XMFLOAT3 pos;			// 面の中心座標
	DirectX::XMFLOAT2 size;			// 面の横縦		(x:横,y:縦)
	DirectX::XMFLOAT3 rot;			// 面の角度		(デフォルトは法線ベクトル上向き。軸回転。45°のときは 45 でOK)
};

union UCollisionData
{
	CharacterData character;		// キャラクターの情報
	ObstaclesData obstacles;		// 障害物の情報
	RayData ray;					// カメラレイの情報
	PlaneData plane;				// 面の情報
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

struct TModelData
{
	// モデル情報
	std::shared_ptr<Model> model;
	// 頂点バッファ情報
	std::shared_ptr<VertexShader> vs;
	// ワールドビュー定数バッファ
	std::shared_ptr<ConstantBuffer> wvp;
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