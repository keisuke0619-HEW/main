#pragma once
#include <IObjectBase.hpp>
#include <memory>
#include <Model.h>
#include <ConstantBuffer.h>

/// <summary>
/// すべての3Dオブジェクトの基底となるクラス
/// </summary>
class CObjectBase : public IObjectBase
{
public:
	// 基底コンストラクタ
	CObjectBase(const char* src = "", float scale = 1.0f, bool isFlip = false, std::string name = "no_name");
	// 仮想デストラクタ
	virtual ~CObjectBase();

	// システムから呼び出されるアップデート
	void BaseUpdate()override final;
	// システムから呼び出されるドロー
	void BaseDraw() override final;
	// オブジェクトと衝突していたら呼び出される
	void OnCollision(Ptr collisionObj) override;
	void OnCollisionTag(EObjectTag tag) override;

	// パラメータ取得
	TObjectParam GetParam() override final;

	// 毎フレームの更新処理（必ず実装）
	virtual void Update() = 0;
	// 毎フレームの描画処理（デフォルト設定を使う場合は実装不要）
	virtual void Draw();

	void Destroy();
protected:
	// 削除の際に呼び出される
	virtual void Finalize();

	// オブジェクト情報
	TObjectParam m_param;
	// モデル情報
	std::shared_ptr<Model> m_model;
	// 頂点バッファ情報
	std::shared_ptr<VertexShader> m_vs;
	// ワールドビュー定数バッファ
	std::shared_ptr<ConstantBuffer> m_wvp;

	void LoadModel(const char* src, float scale, bool isFlip, std::shared_ptr<Model>* pModel, std::shared_ptr<VertexShader>* pVS, std::shared_ptr<ConstantBuffer>* pWVP);
};