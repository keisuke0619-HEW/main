#pragma once
#include <Windows.h>
#include <stdio.h>

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
	// デバッグウィンドウの消去
	static void Close();


	template<class... A>
	static void Print(const char* src, A... args);

private:
	static FILE* m_fp;
};

template<class ...A>
inline void CDebugWindow::Print(const char* src, A ...args)
{

}
