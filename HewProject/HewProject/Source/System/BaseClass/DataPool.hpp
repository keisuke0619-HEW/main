#pragma once

#include <memory>
#include <Model.h>
#include <string>
#include <map>
/// <summary>
/// モデルデータや画像データを保存しておくクラス。シングルトン。
/// </summary>
class CDataPool
{
	// シングルトン機構
public:
	static std::shared_ptr<CDataPool> GetIns();
	static void CreateIns();
	static void Destroy();
	~CDataPool();
private:
	static std::shared_ptr<CDataPool> m_ins;
	CDataPool();

	// 内部機構
public:
	/// <summary>
	/// モデル情報を取得
	/// </summary>
	/// <param name="src">モデルソース</param>
	/// <returns>ソースが存在したらモデルデータ。しなかったらBOX</returns>
	Model GetModel(const char* src, float scale = 1.0f, bool flip = false);
private:
	const char* NULL_MODEL_SOURCE;
	std::map<const char*, std::unique_ptr<Model>> m_models;
};