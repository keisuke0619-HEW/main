#include <Windows.h>	// Windows�̋@�\�𗘗p
#include <stdio.h>		// �W�����o��
#include <main.hpp>
#ifdef _DEBUG
#include <crtdbg.h>
#endif // !_DEBUG

//----- �v���g�^�C�v�錾 -----
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

bool g_isMainLoop = true;

/// <summary>
/// Windows.h�̃G���g���֐�
/// </summary>
/// <param name="hInstance"		>�N�����Ă���v���O������OS�����ʂ��邽�߂ɐU���鐔��</param>
/// <param name="hPrevInstance"	>�̖̂��c�Ŏc���Ă��邾���̃f�[�^�i�݊�����ۂ��߁j</param>
/// <param name="lpCmdLine"		>�R�}���h���C������  ���v���O���������s����Ƃ��ɓn������</param>
/// <param name="nCmdShow"		>�ŏ��̕\�����</param>
/// <returns>��</returns>
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _DEBUG

	//---�E�B���h�E�N���X���̐ݒ�---
	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(wcex));
	// �R�Â��Ώ�
	wcex.hInstance = hInstance;
	// �N���X�������ʂ��閼��
	wcex.lpszClassName = "Class Name";
	// 
	wcex.lpfnWndProc = WndProc;
	// 
	wcex.style = CS_CLASSDC;
	// �\���̂̑傫�����w��i�݊����j
	wcex.cbSize = sizeof(WNDCLASSEX);
	// ���ɏo�Ă���A�C�R�����w��
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	// ��菬���ȃA�C�R�����w��
	wcex.hIconSm = wcex.hIcon;
	// �J�[�\���^�C�v���w��
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	// �w�i���w��
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

	//---�E�B���h�E�N���X���̓o�^---
	if (!RegisterClassEx(&wcex))
	{
		//LogError("�E�B���h�E���̓o�^�Ɏ��s");
		return 0;
	}

	// �E�B���h�E�̍쐬
	HWND hWnd;
	hWnd = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,		// �E�B���h�E�̊O�ς�ݒ�i�g���Łj�B��{�I�[�o�[���b�v�h�E�B���h�E�łn�j
		wcex.lpszClassName,			// �쐬���̃E�B���h�E���N���X�����w��B�N���X���̕R�Â����s���B
		"window",					// �^�C�g���o�[�̐ݒ�
		WS_CAPTION | WS_SYSMENU,	// �E�B���h�E�̊O�ς�����
		CW_USEDEFAULT,				// �E�B���h�E�̕\��X���W���w��iCW_USEDEFAULT��Windows�ɂ��܂����j
		CW_USEDEFAULT,				// �E�B���h�E�̕\��Y���W���w��iCW_USEDEFAULT��Windows�ɂ��܂����j
		WINDOW_WIDTH,				// �E�B���h�E�̃T�C�YX
		WINDOW_HEIGHT,				// �E�B���h�E�̃T�C�YY
		HWND_DESKTOP,				// �e���w��i�ŏ��̃E�B���h�E�̓f�X�N�g�b�v���e�j
		NULL,						// 
		hInstance,					// 
		NULL);						// 

	if (hWnd == NULL)
	{
		//LogError("�E�B���h�E�̍쐬�Ɏ��s");
		return 0;
	}

	// �E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// ���b�Z�[�W���[�v
	MSG message;
	while (g_isMainLoop)
	{
		// ���b�Z�[�W�����邩�m�F
		if (PeekMessage(&message, NULL, 0, 0, PM_NOREMOVE))
		{
			// ���b�Z�[�W���擾
			// ��WM_QUIT�������Ă���Ɩ߂�l��false
			if (!GetMessage(&message, NULL, 0, 0))
			{
				break;
			}
			else
			{
				// �E�B���h�E�v���V�[�W���փ��b�Z�[�W��]���B
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
		}
		// ���b�Z�[�W���Ȃ���΃Q�[���̏���
		else
		{
		}
	}
	// �I������ �������Ƌt���ŏI������

	return 0;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		//case WM_MOUSEMOVE:	// �}�E�X���ړ�
		//{
		//	// �}�E�X�̍��W��lParam�Ɋi�[����Ă���BlParam��32�r�b�g�i�S�o�C�g�j�̃f�[�^��
		//	// ����16�r�b�g�ɂw���W
		//	// ���16�r�b�g�ɂx���W���i�[���Ă���B�_���ςƃr�b�g�V�t�g�Ŏ��o���邪�A�ʓ|�Ȃ̂Ń}�N�����g���B
		//	WORD x = LOWORD(lParam);	// ����16�r�b�g���o��
		//	WORD y = HIWORD(lParam);	// ���16�r�b�g���o��
		//	char str[32];
		//	sprintf(str, "X:%d, Y:%d", x, y);
		//	// MessageBox(hWnd, str, "�}�E�X���W", MB_OK);
		//}
		//	break;
	case WM_KEYDOWN:	// �L�[�{�[�h�������ꂽ
		// wParam�ɃL�[��񂪊i�[����Ă���BEsc�������ꂽ���m�F�Łu�͂��v�Ȃ�
		if (wParam == VK_ESCAPE && MessageBox(hWnd, "�I�����܂����H", "�m�F", MB_YESNO) == IDYES)
		{
			// �E�B���h�E��j�����A�i���łɁjWM_DESTORY��ʒm
			DestroyWindow(hWnd);
		}
		break;
	case WM_CLOSE:		// [�~]�{�^���������ꂽ
		if (MessageBox(hWnd, "�I�����܂����H", "�m�F", MB_YESNO) == IDNO)
			return 0;
		break;
	case WM_DESTROY:	// �E�B���h�E������ꂽ
		// �v���O�����̏I����ʒm
		PostQuitMessage(0);
		break;
	}
	// �f�t�H���g�̃E�B���h�E���������s
	return DefWindowProc(hWnd, message, wParam, lParam);
}