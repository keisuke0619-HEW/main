#pragma once
#include <Windows.h>

// メモ
// 
// 改行するかどうかの変数、関数
// <バッファに書き込んで一気にプリント>なし？
// 行を選択して上書き描画
//		ConioEX::clrLine参照
// 
//

class CDebugWindow
{
public:
	// デバッグウィンドウの作成
	static void Create();

	template<class... A>
	static void Print(const char* src, A... args);

};

template<class ...A>
inline void CDebugWindow::Print(const char* src, A ...args)
{

}
