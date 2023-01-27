#include "Main.h"
#include "WinUtil.h"
#include "Timer.h"
#include <OverlayConfig.hpp>

//--- 定数定義
const char* APP_TITLE = "It's so CHARGE BEAM -AX218-";
const Frame DEFAULT_FPS = 60;

bool g_isLoop = false;
/*
* エントリポイント
*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (FAILED(InitWindow(APP_TITLE, GetAppWidth(), GetAppHeight())))
	{
		Error("window initialize faield");
	}
	InitTimer(DEFAULT_FPS);
	Init();

	//--- ウィンドウの管理
	AppState state = APP_STATE_MESSAGE;
	while (state != APP_STATE_QUIT)
	{
		state = UpdateWindow();
		if (state == APP_STATE_WAIT && UpdateTimer())
		{

			Update(GetDeltaTime());
			Draw();
			if (g_isLoop)
			{
				state = APP_STATE_QUIT;
			}
			
		}
	}

	// 終了時
	Uninit();
	UninitTimer();
	UninitWindow();
	return 0;
}

bool* GetLoopPointer()
{
	return &g_isLoop;
}