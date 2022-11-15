#pragma once
#include <ObjectToManagerInterface.hpp>
#include <memory>
#include <Model.h>
#include <ConstantBuffer.h>

/// <summary>
/// すべての3Dオブジェクトの基底となるクラス
/// </summary>
class CObjectBase : IObjectToManager
{
public:
	// 基底コンストラクタ
	CObjectBase();
	// 仮想デストラクタ
	virtual ~CObjectBase();

	// システムから呼び出されるアップデート
	void UpdateBase()override final;
	// システムから呼び出されるドロー
	void DrawBase() override final;
	// パラメータ取得
	TObjectParam GetParam() override final;

	// 毎フレームの更新処理（必ず実装）
	virtual void Update() = 0;
	// 毎フレームの描画処理（デフォルト設定を使う場合は実装不要）
	virtual void Draw();

protected:
	// オブジェクト情報
	TObjectParam m_param;
	// モデル情報
	std::shared_ptr<Model> m_model;
	// 頂点バッファ情報
	std::unique_ptr<VertexShader> m_vs;
	// ワールドビュー定数バッファ
	std::unique_ptr<ConstantBuffer> m_wvp;
};