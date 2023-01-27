#include "OverlayConfig.hpp"

#include <SceneManager.hpp>
#include <Controller.hpp>
#include <DebugWindow.hpp>

// 大体ここをいじれば調整できます。
const float OVERLAY_CONFIG_CENTER_X = 640.0f;		// コンフィグUIの中心座標
const float OVERLAY_CONFIG_X_BAR_POS_Y = 230.0f;	// 上の設定バーのY座標
const float OVERLAY_CONFIG_Y_BAR_POS_Y = 350.0f;	// 下の設定バーのY座標
const float OVERLAY_CONFIG_BAR_SIZE_X = 850.0f;		// 設定バーのサイズX
const float OVERLAY_CONFIG_BAR_SIZE_Y = 100.0f;		// 設定バーのサイズY
const float OVERLAY_CONFIG_CURSOR_SIZE_X = 100.0f;	// カーソルのサイズX
const float OVERLAY_CONFIG_CURSOR_SIZE_Y = 100.0f;	// カーソルのサイズY
const float OVERLAY_CONFIG_SPEED_MIN = 1.0f;		// カメラスピードの最小値
const float OVERLAY_CONFIG_SPEED_MAX = 100.0f;		// カメラスピードの最大値
const float OVERLAY_CONFIG_POS_MIN = OVERLAY_CONFIG_CENTER_X - OVERLAY_CONFIG_BAR_SIZE_X / 2.08f;	// カーソルの移動制限最小値（最後の数値でうまく調整
const float OVERLAY_CONFIG_POS_MAX = OVERLAY_CONFIG_CENTER_X + OVERLAY_CONFIG_BAR_SIZE_X / 2.23f;	// カーソルの移動制限最大値

static bool g_isLoop = false;
COverlayConfig::COverlayConfig()
{
	auto tmp = new CGameUI("Assets/Img/PauseMenu/Back.png");
	tmp->SetPos({ OVERLAY_CONFIG_CENTER_X, 360 });
	tmp->SetSize({ 1100, 700 });
	Add("Back", tmp, SORT_ORDER_UI_BACK2);
	tmp = new CGameUI("Assets/Img/White.png");
	tmp->SetPos({ 640, 360 });
	tmp->SetSize({ 1280, 720 });
	tmp->SetColor255(0, 0, 0, 128);
	Add("Fade", tmp, SORT_ORDER_UI_BACK3);
	m_speedXBar = new CGameUI("Assets/Img/PauseMenu/Bar.png");
	m_speedXBar->SetPos(OVERLAY_CONFIG_CENTER_X, OVERLAY_CONFIG_X_BAR_POS_Y);
	m_speedXBar->SetSize(OVERLAY_CONFIG_BAR_SIZE_X, OVERLAY_CONFIG_BAR_SIZE_Y);
	Add("XBar", m_speedXBar, SORT_ORDER_UI_BACK1);
	m_speedYBar = new CGameUI("Assets/Img/PauseMenu/Bar.png");
	m_speedYBar->SetPos(OVERLAY_CONFIG_CENTER_X, OVERLAY_CONFIG_Y_BAR_POS_Y);
	m_speedYBar->SetSize(OVERLAY_CONFIG_BAR_SIZE_X, OVERLAY_CONFIG_BAR_SIZE_Y);
	Add("YBar", m_speedYBar, SORT_ORDER_UI_BACK1);
	m_speedXCursor = new CGameUI("Assets/Img/PauseMenu/Cursor.png");
	m_speedXCursor->SetPos(OVERLAY_CONFIG_CENTER_X, OVERLAY_CONFIG_X_BAR_POS_Y);
	m_speedXCursor->SetSize(OVERLAY_CONFIG_CURSOR_SIZE_X, OVERLAY_CONFIG_CURSOR_SIZE_Y);
	Add("XCursor", m_speedXCursor);
	m_speedYCursor = new CGameUI("Assets/Img/PauseMenu/Cursor.png");
	m_speedYCursor->SetPos(OVERLAY_CONFIG_CENTER_X, OVERLAY_CONFIG_Y_BAR_POS_Y);
	m_speedYCursor->SetSize(OVERLAY_CONFIG_CURSOR_SIZE_X, OVERLAY_CONFIG_CURSOR_SIZE_Y);
	Add("YCursor", m_speedYCursor);

	m_speedXNum.reset(new CNumberUI(3, SORT_ORDER_UI_FRONT4, 2));
	m_speedXNum->SetSize(36, 45);
	m_speedYNum.reset(new CNumberUI(3, SORT_ORDER_UI_FRONT4, 2));
	m_speedYNum->SetSize(36, 45);

	m_pcursorSE = CreateSound("Assets/Sound/cursor.mp3", false);
	m_pselectSE = CreateSound("Assets/Sound/select.mp3", false);
	m_pbarSE = CreateSound("Assets/Sound/bar.mp3", false);
}

COverlayConfig::~COverlayConfig()
{
}

void COverlayConfig::Update()
{
	MoveCursor();
	SetStatus();
	if (Utility::GetKeyTrigger(KEY_CANCEL) || Utility::GetKeyTrigger(KEY_CONFIG))
	{
		m_isDestroy = true;
	}
}

void COverlayConfig::MoveCursor()
{
	if (Utility::GetKeyTrigger(KEY_UP))
	{
		m_target--;
		m_pSESource = StartSound(m_pcursorSE);
	}
	if (Utility::GetKeyTrigger(KEY_DOWN))
	{
		m_target++;
		m_pSESource = StartSound(m_pcursorSE);
	}
	if (m_target < 0)
	{
		m_target = TARGET_MAX * 100;
	}
}

void COverlayConfig::SetStatus()
{
	const float addLevel = 0.5f;
	float add = 0;
	m_speedXBar->SetColor255(128, 128, 128, 128);
	m_speedXCursor->SetColor255(128, 128, 128, 128);
	m_speedYBar->SetColor255(128, 128, 128, 128);
	m_speedYCursor->SetColor255(128, 128, 128, 128);
	m_speedXNum->SetColor255(128, 128, 128, 128);
	m_speedYNum->SetColor255(128, 128, 128, 128);
	if (Utility::GetKeyPress(KEY_RIGHT))
	{
		add += addLevel;
		m_pSESource = StartSound(m_pbarSE);

	}
	if (Utility::GetKeyPress(KEY_LEFT))
	{
		add -= addLevel;
		m_pSESource = StartSound(m_pbarSE);
	}
	switch (m_target % TARGET_MAX)
	{
	case 0:
		m_speedXBar->SetColor255(255, 255, 255, 255);
		m_speedXCursor->SetColor255(255, 255, 255, 255);
		m_speedXNum->SetColor255(255, 255, 255, 255);
		Utility::SetCameraSpeedX(Utility::GetCameraSpeedX() + add);
		break;
	case 1:
		m_speedYBar->SetColor255(255, 255, 255, 255);
		m_speedYCursor->SetColor255(255, 255, 255, 255);
		m_speedYNum->SetColor255(255, 255, 255, 255);
		Utility::SetCameraSpeedY(Utility::GetCameraSpeedY() + add);
		break;
	default:
		break;
	}
	// クリップ
	auto speedX = Utility::GetCameraSpeedX();
	auto speedY = Utility::GetCameraSpeedY();
	if (speedX < OVERLAY_CONFIG_SPEED_MIN)
		Utility::SetCameraSpeedX(OVERLAY_CONFIG_SPEED_MIN);
	if (speedY < OVERLAY_CONFIG_SPEED_MIN)
		Utility::SetCameraSpeedY(OVERLAY_CONFIG_SPEED_MIN);
	if (speedX > OVERLAY_CONFIG_SPEED_MAX)
		Utility::SetCameraSpeedX(OVERLAY_CONFIG_SPEED_MAX);
	if (speedY > OVERLAY_CONFIG_SPEED_MAX)
		Utility::SetCameraSpeedY(OVERLAY_CONFIG_SPEED_MAX);
	m_speedXCursor->SetPos(OVERLAY_CONFIG_POS_MIN + (OVERLAY_CONFIG_POS_MAX - OVERLAY_CONFIG_POS_MIN) * (Utility::GetCameraSpeedX() / OVERLAY_CONFIG_SPEED_MAX), OVERLAY_CONFIG_X_BAR_POS_Y);
	m_speedYCursor->SetPos(OVERLAY_CONFIG_POS_MIN + (OVERLAY_CONFIG_POS_MAX - OVERLAY_CONFIG_POS_MIN) * (Utility::GetCameraSpeedY() / OVERLAY_CONFIG_SPEED_MAX), OVERLAY_CONFIG_Y_BAR_POS_Y);
	m_speedXNum->SetPos(
		OVERLAY_CONFIG_POS_MIN + (OVERLAY_CONFIG_POS_MAX - OVERLAY_CONFIG_POS_MIN) * (Utility::GetCameraSpeedX() / OVERLAY_CONFIG_SPEED_MAX),
		OVERLAY_CONFIG_X_BAR_POS_Y - OVERLAY_CONFIG_CURSOR_SIZE_Y / 2.5f);
	m_speedXNum->SetNum(Utility::GetCameraSpeedX());
	m_speedYNum->SetPos(
		OVERLAY_CONFIG_POS_MIN + (OVERLAY_CONFIG_POS_MAX - OVERLAY_CONFIG_POS_MIN) * (Utility::GetCameraSpeedY() / OVERLAY_CONFIG_SPEED_MAX),
		OVERLAY_CONFIG_Y_BAR_POS_Y - OVERLAY_CONFIG_CURSOR_SIZE_Y / 2.5f);
	m_speedYNum->SetNum(Utility::GetCameraSpeedY());
}


//■■■■■■■■ タイトルに戻りますか？タブ ■■■■■■■■■■■

CTitleBack::CTitleBack()
{
	auto tmp = new CGameUI("Assets/Img/PauseMenu/END.png");
	tmp->SetPos({ OVERLAY_CONFIG_CENTER_X, 360 });
	tmp->SetSize({ 1100, 700 });
	//tmp->SetColor255(255, 255, 255, 128);
	Add("Back", tmp, SORT_ORDER_UI_BACK2);
	tmp = new CGameUI("Assets/Img/White.png");
	tmp->SetPos({ 640, 360 });
	tmp->SetSize({ 1280, 720 });
	tmp->SetColor255(0, 0, 0, 255);
	Add("Fade", tmp, SORT_ORDER_UI_BACK3);
	m_speedXCursor = new CGameUI("Assets/Img/PauseMenu/Cursor2.png");
	m_speedXCursor->SetPos(OVERLAY_CONFIG_CENTER_X - 240.0f, OVERLAY_CONFIG_X_BAR_POS_Y + 215.0f);
	m_speedXCursor->SetSize(OVERLAY_CONFIG_CURSOR_SIZE_X * 1.5f, OVERLAY_CONFIG_CURSOR_SIZE_Y);
	//m_speedXCursor->SetColor255(128, 128, 128, 128);
	Add("XCursor", m_speedXCursor, SORT_ORDER_UI_FRONT);


	m_speedXNum.reset(new CNumberUI(3, SORT_ORDER_UI_FRONT4, 2));
	m_speedXNum->SetSize(36, 45);
	m_speedYNum.reset(new CNumberUI(3, SORT_ORDER_UI_FRONT4, 2));
	m_speedYNum->SetSize(36, 45);

	g_isLoop = false;
	m_isDestroy = false;
	m_next = false;

	m_pcursorSE = CreateSound("Assets/Sound/cursor.mp3", false);
	m_pselectSE = CreateSound("Assets/Sound/select.mp3", false);
	m_pcancelSE = CreateSound("Assets/Sound/cancel.mp3", false);
}

CTitleBack::~CTitleBack()
{
}

bool CTitleBack::IsLoop()
{
	return g_isLoop;
}

void CTitleBack::SetIsNext(bool * next)
{
	m_next = next;
}

void CTitleBack::Update()
{
	SetStatus();
	MoveCursor();
	if (Utility::GetKeyTrigger(KEY_CANCEL))
	{
		m_isDestroy = true;
		m_pSESource = StartSound(m_pcancelSE);
	}

	if (Utility::GetKeyTrigger(KEY_SELECT))
	{
		m_pSESource = StartSound(m_pselectSE);
		//	決定
		if ((m_target % TARGET_MAX) == 0)
		{
			if (m_next != nullptr)
				*m_next = true;
			m_isDestroy = true;
		}
		if ((m_target % TARGET_MAX) == 1)
		{
			m_isDestroy = true;
		}
	}
}

void CTitleBack::MoveCursor()
{
	if (Utility::GetKeyTrigger(KEY_LEFT))
	{
		m_target--;
		m_pSESource = StartSound(m_pcursorSE);
	}
	if (Utility::GetKeyTrigger(KEY_RIGHT))
	{
		m_target++;
		m_pSESource = StartSound(m_pcursorSE);
	}
	
	if (m_target < 0)
	{
		m_target = TARGET_MAX * 100;
	}
}

void CTitleBack::SetStatus()
{
	//m_pSESource = StartSound(m_pcursorSE);
	switch (m_target % TARGET_MAX)
	{
	case 0:
		m_speedXCursor->SetPos(OVERLAY_CONFIG_CENTER_X - 240.0f, OVERLAY_CONFIG_X_BAR_POS_Y + 215.0f);
		break;
	case 1:
		m_speedXCursor->SetPos(OVERLAY_CONFIG_CENTER_X + 265.0f, OVERLAY_CONFIG_X_BAR_POS_Y + 215.0f);
		break;
	default:
		break;
	}
}

//■■■■■■■■ 説明タブ（？） ■■■■■■■■■■■

CSetumei::CSetumei()
{
	auto tmp = new CGameUI("Assets/Img/StageSelect/test_sousaTab.png");
	tmp->SetPos({ OVERLAY_CONFIG_CENTER_X, 360 });
	tmp->SetSize({ 960, 540 });
	//tmp->SetColor255(255, 255, 255, 128);
	Add("Back", tmp, SORT_ORDER_UI_BACK2);
	tmp = new CGameUI("Assets/Img/White.png");
	tmp->SetPos({ 640, 360 });
	tmp->SetSize({ 1280, 720 });
	tmp->SetColor255(0, 0, 0, 255);
	Add("Fade", tmp, SORT_ORDER_UI_BACK3);

	m_isDestroy = false;
}

CSetumei::~CSetumei()
{
}

void CSetumei::Update()
{
	if (Utility::GetKeyTrigger(KEY_CANCEL))
	{
		m_isDestroy = true;
	}
}

//■■■■■■■■ 終了タブ ■■■■■■■■■■■

CGameEnd::CGameEnd()
{
	auto tmp = new CGameUI("Assets/Img/PauseMenu/flame.png");
	tmp->SetData( OVERLAY_CONFIG_CENTER_X, 360 ,1100, 500);
	Add("Back", tmp, SORT_ORDER_UI_BACK4);

	m_circleIn = new CGameUI("Assets/Img/PauseMenu/circle_in.png");
	m_circleIn->SetData( 640, 360,200, 200);
	Add("CircleIn", m_circleIn, SORT_ORDER_UI_BACK3);

	m_circleOut = new CGameUI("Assets/Img/PauseMenu/circle_out.png");
	m_circleOut->SetData( 640, 360 ,300, 300);
	Add("CircleOut", m_circleOut, SORT_ORDER_UI_BACK3);

	tmp = new CGameUI("Assets/Img/White.png");
	tmp->SetData(640, 360, 1280, 720);
	tmp->SetColor255(0, 0, 0, 128);
	Add("Fade", tmp, SORT_ORDER_UI_BACKEND);

	m_cursor = new CGameUI("Assets/Img/PauseMenu/Cursor2.png");
	m_cursor->SetPos(OVERLAY_CONFIG_CENTER_X - 120.0f, OVERLAY_CONFIG_X_BAR_POS_Y + 140.0f);
	m_cursor->SetColor(1.0f, 1.0f, 1.0f, 0.3f);
	Add("XCursor", m_cursor, SORT_ORDER_UI_BACK);


	m_labelYes = new CGameUI("Assets/Img/PauseMenu/Label_Yes.png");
	m_labelYes->SetData(OVERLAY_CONFIG_CENTER_X - 120.0f, OVERLAY_CONFIG_X_BAR_POS_Y + 140.0f, 1400, 70);
	Add("Label_Yes", m_labelYes, SORT_ORDER_UI_FRONT);

	m_labelNo = new CGameUI("Assets/Img/PauseMenu/Label_No.png");
	m_labelNo->SetData(OVERLAY_CONFIG_CENTER_X + 120.0f, OVERLAY_CONFIG_X_BAR_POS_Y + 140.0f, 1400, 70);
	Add("Label_No", m_labelNo, SORT_ORDER_UI_FRONT);

	for (int i = 0; i < 7; i++)
	{
		std::string str = "GAUGE_";
		str += std::to_string(i);
		m_gauge[i] = new CGameUI("Assets/Img/PauseMenu/virticalBar.png");
		m_gauge[i]->SetData(934 + i * 36, 547, 23, 60);
		Add(str, m_gauge[i]);
	}
	g_isLoop = false;
	m_isDestroy = false;

	m_pcursorSE = CreateSound("Assets/Sound/cursor.mp3", false);
	m_pselectSE = CreateSound("Assets/Sound/select.mp3", false);
	m_pcancelSE = CreateSound("Assets/Sound/cancel.mp3", false);
}

CGameEnd::~CGameEnd()
{
}

bool CGameEnd::IsLoop()
{
	return g_isLoop;
}

void CGameEnd::Update()
{
	MoveCursor();
	SetStatus();
	if (Utility::GetKeyTrigger(KEY_CANCEL))
	{
		m_isDestroy = true;
		m_pSESource = StartSound(m_pcancelSE);
	}
	m_circleIn->SetRotation(m_frame);
	m_circleOut->SetRotation(-m_frame * 0.8f);
	m_cursor->SetSize(
		(sinf(DirectX::XMConvertToRadians(m_frame * 4)) * 0.05f + 0.9f) * OVERLAY_CONFIG_CURSOR_SIZE_Y * 2.5f * 0.5f, 
		(sinf(DirectX::XMConvertToRadians(m_frame * 4)) * 0.05f + 0.9f) * OVERLAY_CONFIG_CURSOR_SIZE_Y        * 0.5f);
}

void CGameEnd::MoveCursor()
{
	m_labelYes->SetSize(1400, 70);
	m_labelNo->SetSize(1400, 70);
	if (Utility::GetKeyTrigger(KEY_LEFT))
	{
		m_target--;
		m_pSESource = StartSound(m_pcursorSE);
	}
	if (Utility::GetKeyTrigger(KEY_RIGHT))
	{
		m_target++;
		m_pSESource = StartSound(m_pcursorSE);
	}
	if (Utility::GetKeyTrigger(KEY_SELECT))
	{
		m_pSESource = StartSound(m_pselectSE);
		//	決定
		if ((m_target % TARGET_MAX) == 0)
		{
			g_isLoop = true;
		}
		if ((m_target % TARGET_MAX) == 1)
		{
			m_isDestroy = true;
		}
	}
	if (m_target < 0)
	{
		m_target = TARGET_MAX * 100;
	}
	if (m_target % 2 == 1)
	{
		m_labelNo->SetSize(1800, 90);

	}
	else
	{
		m_labelYes->SetSize(1800, 90);
	}
}

void CGameEnd::SetStatus()
{
	//m_pSESource = StartSound(m_pcursorSE);
	const float moveX = 120.0f;
	const float offsetY = 170.0f;
	switch (m_target % TARGET_MAX)
	{
	case 0:
		m_cursor->SetPos(OVERLAY_CONFIG_CENTER_X - moveX - 5, OVERLAY_CONFIG_X_BAR_POS_Y + offsetY);
		break;
	case 1:
		m_cursor->SetPos(OVERLAY_CONFIG_CENTER_X + moveX, OVERLAY_CONFIG_X_BAR_POS_Y + offsetY);
		break;
	default:
		break;
	}
	// デバッグ
	static float alpha = 0.5f;
	if (Utility::GetKeyTrigger(KEY_DOWN))
		alpha -= 0.05f;
	if (Utility::GetKeyTrigger(KEY_UP))
		alpha += 0.05f;
	m_cursor->SetColor(1, 1, 1, alpha);
	CDebugWindow::Print(ShimizuKeisuke, "Alpha:", alpha);
}