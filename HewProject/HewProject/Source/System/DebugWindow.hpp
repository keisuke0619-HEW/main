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
	// デバッグウィンドウの消去
	static void Close();

	static void SetCreator();

	//template<typename First, typename... A>
	//static std::string Print(CreatorTag tag, const char* src, First first, A... args);

	static void Print(CreatorTag tag, const char* src);
	static void Print(CreatorTag tag, const char* label, int data);
	static void Print(CreatorTag tag, const char* label, float data);
	//static void Print(CreatorTag tag, std::string label, bool data);
	static void Print(CreatorTag tag, const char* label, DirectX::XMFLOAT3 data);
	static void Print(CreatorTag tag, const char* label, DirectX::XMVECTOR data);
	static void Print(CreatorTag tag, const char* label, DirectX::XMMATRIX data);
private:
	static FILE* m_fp;
	static CreatorTag m_creator;
};

// Printfと大体同じに設定してあります。
// 使用可能フォーマット指定子（%の後に）
// d:整数値
// f:実数値（小数点以下4位固定）
// s:文字列
//

//template<typename First, typename... A>
//std::string CDebugWindow::Print(CreatorTag tag, const char* src, First first, A... args)
//{
//#ifdef DEBUG
//	std::string str;
//	while (src != '\0')
//	{
//		if (*src == '%')
//		{
//			src++;
//			switch (*src)
//			{
//			case 'd':
//			case 'D':
//				str += std::to_string(first);
//				src++;
//				str += Print(tag, src, args...);
//				break;
//			case 'f':
//			case 'F':
//				//str += std::_Floating_to_string("%.4f",first);
//				str += std::to_string(first);
//
//				src++;
//				str += Print(tag, src, args...);
//				break;
//			case 'c':
//			case 'C':
//				str += first;
//				src++;
//				str += Print(tag, src, args...);
//				break;
//			}
//		}
//		str += *src;
//		src++;
//	}
//#endif // _DEBUG
//
//}
