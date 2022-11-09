#include <Windows.h>	// Windowsの機能を利用
#include <stdio.h>		// 標準入出力
#include <main.hpp>
#ifdef _DEBUG
#include <crtdbg.h>
#endif // !_DEBUG

//----- プロトタイプ宣言 -----
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

bool g_isMainLoop = true;

/// <summary>
/// Windows.hのエントリ関数
/// </summary>
/// <param name="hInstance"		>起動しているプログラムをOSが判別するために振られる数字</param>
/// <param name="hPrevInstance"	>昔の名残で残っているだけのデータ（互換性を保つため）</param>
/// <param name="lpCmdLine"		>コマンドライン引数  ※プログラムを実行するときに渡す引数</param>
/// <param name="nCmdShow"		>最初の表示状態</param>
/// <returns>あ</returns>
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _DEBUG

	//---ウィンドウクラス情報の設定---
	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(wcex));
	// 紐づけ対象
	wcex.hInstance = hInstance;
	// クラス情報を識別する名称
	wcex.lpszClassName = "Class Name";
	// 
	wcex.lpfnWndProc = WndProc;
	// 
	wcex.style = CS_CLASSDC;
	// 構造体の大きさを指定（互換性）
	wcex.cbSize = sizeof(WNDCLASSEX);
	// 下に出てくるアイコンを指定
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	// より小さなアイコンを指定
	wcex.hIconSm = wcex.hIcon;
	// カーソルタイプを指定
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	// 背景を指定
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

	//---ウィンドウクラス情報の登録---
	if (!RegisterClassEx(&wcex))
	{
		//LogError("ウィンドウ情報の登録に失敗");
		return 0;
	}

	// ウィンドウの作成
	HWND hWnd;
	hWnd = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,		// ウィンドウの外観を設定（拡張版）。基本オーバーラップドウィンドウでＯＫ
		wcex.lpszClassName,			// 作成元のウィンドウうクラス情報を指定。クラス情報の紐づけを行う。
		"window",					// タイトルバーの設定
		WS_CAPTION | WS_SYSMENU,	// ウィンドウの外観を決定
		CW_USEDEFAULT,				// ウィンドウの表示X座標を指定（CW_USEDEFAULTでWindowsにおまかせ）
		CW_USEDEFAULT,				// ウィンドウの表示Y座標を指定（CW_USEDEFAULTでWindowsにおまかせ）
		WINDOW_WIDTH,				// ウィンドウのサイズX
		WINDOW_HEIGHT,				// ウィンドウのサイズY
		HWND_DESKTOP,				// 親を指定（最初のウィンドウはデスクトップが親）
		NULL,						// 
		hInstance,					// 
		NULL);						// 

	if (hWnd == NULL)
	{
		//LogError("ウィンドウの作成に失敗");
		return 0;
	}

	// ウィンドウの表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// メッセージループ
	MSG message;
	while (g_isMainLoop)
	{
		// メッセージがあるか確認
		if (PeekMessage(&message, NULL, 0, 0, PM_NOREMOVE))
		{
			// メッセージを取得
			// ※WM_QUITが送られていると戻り値がfalse
			if (!GetMessage(&message, NULL, 0, 0))
			{
				break;
			}
			else
			{
				// ウィンドウプロシージャへメッセージを転送。
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
		}
		// メッセージがなければゲームの処理
		else
		{
		}
	}
	// 終了処理 初期化と逆順で終了する

	return 0;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		//case WM_MOUSEMOVE:	// マウスが移動
		//{
		//	// マウスの座標はlParamに格納されている。lParamは32ビット（４バイト）のデータで
		//	// 下位16ビットにＸ座標
		//	// 上位16ビットにＹ座標を格納している。論理積とビットシフトで取り出せるが、面倒なのでマクロを使う。
		//	WORD x = LOWORD(lParam);	// 下位16ビット取り出し
		//	WORD y = HIWORD(lParam);	// 上位16ビット取り出し
		//	char str[32];
		//	sprintf(str, "X:%d, Y:%d", x, y);
		//	// MessageBox(hWnd, str, "マウス座標", MB_OK);
		//}
		//	break;
	case WM_KEYDOWN:	// キーボードが押された
		// wParamにキー情報が格納されている。Escが押されたかつ確認で「はい」なら
		if (wParam == VK_ESCAPE && MessageBox(hWnd, "終了しますか？", "確認", MB_YESNO) == IDYES)
		{
			// ウィンドウを破棄し、（ついでに）WM_DESTORYを通知
			DestroyWindow(hWnd);
		}
		break;
	case WM_CLOSE:		// [×]ボタンが押された
		if (MessageBox(hWnd, "終了しますか？", "確認", MB_YESNO) == IDNO)
			return 0;
		break;
	case WM_DESTROY:	// ウィンドウが閉じられた
		// プログラムの終了を通知
		PostQuitMessage(0);
		break;
	}
	// デフォルトのウィンドウ処理を実行
	return DefWindowProc(hWnd, message, wParam, lParam);
}