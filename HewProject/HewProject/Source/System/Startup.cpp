#include "Main.h"
#include "WinUtil.h"
#include "Timer.h"
#include "Input.h"

//--- �萔��`
const char* APP_TITLE = "It's so CHARGE BEAM -AX218-";
const Frame DEFAULT_FPS = 60;
bool bGameFlag = true;

/*
* �G���g���|�C���g
*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (FAILED(InitWindow(APP_TITLE, GetAppWidth(), GetAppHeight())))
	{
		Error("window initialize faield");
	}
	InitTimer(DEFAULT_FPS);
	Init();

	//--- �E�B���h�E�̊Ǘ�
	AppState state = APP_STATE_MESSAGE;
	while (state != APP_STATE_QUIT && bGameFlag == true)
	{
		state = UpdateWindow();
		if (state == APP_STATE_WAIT && UpdateTimer())
		{

			Update(GetDeltaTime());
			Draw();

			if (IsKeyTrigger(VK_ESCAPE))
			{
				bGameFlag = false;
			}
		}
	}

	// �I����
	Uninit();
	UninitTimer();
	UninitWindow();
	return 0;
}
