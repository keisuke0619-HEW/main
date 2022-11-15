#pragma once

#include <memory>
/// <summary>
/// モデルデータや画像データを保存しておくクラス。シングルトン。
/// </summary>
class CDataPool
{
	// シングルトン機構
public:
	static std::weak_ptr<CDataPool> GetIns();
private:

};