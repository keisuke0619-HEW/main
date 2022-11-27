#pragma once
#include <Windows.h>
#include <stdio.h>
#include <string>
#include <DirectXMath.h>
// メモ
// 
// 改行するかどうかの変数、関数
// <バッファに書き込んで一気にプリント>なし？
// 行を選択して上書き描画
//		ConioEX::clrLine参照
// 
//

enum CreatorTag
{
	NULL_CREATOR,
	ShibataOsuke,
	SatoShunma,
	HiranoYuki,
	ShimizuKeisuke,
	SatoKenta,
	TsuchiyaShouya,
	HaraHirotaka,
	HikosakaAoto,
	IkegamiRenta,
	HoriKurumi,
	MasutaRintaro,
};

//#define DebugPrint(name, func) if(name == CreatorTag::ShimizuKeisuke)func;

class CDebugWindow
{
public:
	// デバッグウィンドウの作成
	static void Create();
	// デバッグウィンドウの解放
	static void Close();

	/// <summary>
	/// デバッグウィンドウに文字列を表示します。先にSprintfなどで文字列を作成してください。
	/// </summary>
	/// <param name="tag">自分のクリエイタータグ</param>
	/// <param name="src">表示する文字列</param>
	static void Print(CreatorTag tag, const char* src);
	/// <summary>
	/// デバッグウィンドウに説明用のラベルと整数を表示します
	/// </summary>
	/// <param name="tag">自分のクリエイタータグ</param>
	/// <param name="label">何の変数か説明するラベル</param>
	/// <param name="data">表示する整数値</param>
	static void Print(CreatorTag tag, const char* label, int data);
	/// <summary>
	/// デバッグウィンドウに説明用のラベルと実数を表示します
	/// </summary>
	/// <param name="tag">自分のクリエイタータグ</param>
	/// <param name="label">何の変数か説明するラベル</param>
	/// <param name="data">表示する実数値</param>
	static void Print(CreatorTag tag, const char* label, float data);
	/// <summary>
	/// デバッグウィンドウに説明用のラベルとFloat3の値を表示します
	/// </summary>
	/// <param name="tag">自分のクリエイタータグ</param>
	/// <param name="label">何の変数か説明するラベル</param>
	/// <param name="data">表示するFloat3</param>
	static void Print(CreatorTag tag, const char* label, DirectX::XMFLOAT3 data);
	/// <summary>
	/// デバッグウィンドウに説明用のラベルと3次元ベクトルの値を表示します
	/// </summary>
	/// <param name="tag">自分のクリエイタータグ</param>
	/// <param name="label">何の変数か説明するラベル</param>
	/// <param name="data">表示する３次元ベクトルデータ</param>
	static void Print(CreatorTag tag, const char* label, DirectX::XMVECTOR data);
	/// <summary>
	/// デバッグウィンドウに説明用のラベルと４ｘ４行列を表示します
	/// </summary>
	/// <param name="tag">自分のクリエイタータグ</param>
	/// <param name="label">何の変数か説明するラベル</param>
	/// <param name="data">表示する４ｘ４行列</param>
	static void Print(CreatorTag tag, const char* label, DirectX::XMMATRIX data);

private:
	static FILE* m_fp;
	static CreatorTag m_creator;
	static bool m_enable;

	static void SetCreator();
	static void SetEnable();
};
