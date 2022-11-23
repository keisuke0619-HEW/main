#pragma once
#include <Windows.h>
#include <stdio.h>
#include <string>
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
	SSK,
};


class CDebugWindow
{
public:
	// デバッグウィンドウの作成
	static void Create();
	// デバッグウィンドウの消去
	static void Close();


	template<class... A>
	static void Print(CreatorTag tag, const char* src, A... args);

private:
	static FILE* m_fp;
};

// Printfと大体同じに設定してあります。
// 使用可能フォーマット指定子（%の後に）
// d:整数値
// f:実数値（小数点以下4位固定）
// s:文字列
//
//
template<class ...A>
inline void CDebugWindow::Print(CreatorTag tag,const char* src, A ...args)
{
#ifdef _DEBUG
	std::string str;
	while (src != '\0')
	{
		if (*src == '%')
		{
			src++;
			switch (*src)
			{
			case 'd':
				break;

			}
		}
		str += *src;
		src++;
	}
#endif // _DEBUG

}
