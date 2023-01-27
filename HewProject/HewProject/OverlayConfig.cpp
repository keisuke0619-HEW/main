#include "OverlayConfig.hpp"

#include <SceneManager.hpp>
#include <Controller.hpp>
#include <DebugWindow.hpp>
#include <SE.h>

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

	CSoundSE::CountReset();
}

COverlayConfig::~COverlayConfig()
{
}

void COverlayConfig::Update()
{
	MoveCursor();
	SetStatus();
	CSoundSE::CountUp();
	if (Utility::GetKeyTrigger(KEY_CANCEL) || Utility::GetKeyTrigger(KEY_CONFIG))
	{
		CSoundSE::Start(CSoundSE::SE_CANCEL);
		m_isDestroy = true;
	}
}

void COverlayConfig::MoveCursor()
{
	if (Utility::GetKeyTrigger(KEY_UP))
	{
		m_target--;
		CSoundSE::Start(CSoundSE::SE_CURSOR);
	}
	if (Utility::GetKeyTrigger(KEY_DOWN))
	{
		m_target++;
		CSoundSE::Start(CSoundSE::SE_CURSOR);
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
		if (!CSoundSE::IsPlay())
		{
			CSoundSE::Start(CSoundSE::SE_BAR);
			CSoundSE::BoolPlay();
			CSoundSE::CountReset();
		}
		else
		{
			if (CSoundSE::GetCount() % 15 == 0)
				CSoundSE::Start(CSoundSE::SE_BAR);
		}
		

	}
	else if (Utility::GetKeyPress(KEY_LEFT))
	{
		add -= addLevel;
		if (!CSoundSE::IsPlay())
		{
			CSoundSE::Start(CSoundSE::SE_BAR);
			CSoundSE::BoolPlay();
			CSoundSE::CountReset();
		}
		else
		{
			if (CSoundSE::GetCount() % 15 == 0)
				CSoundSE::Start(CSoundSE::SE_BAR);
		}
	}
	else
	{
		CSoundSE::BoolStop();
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
	tmp->SetColor255(0, 0, 0, 128);
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
		CSoundSE::Start(CSoundSE::SE_CANCEL);
		m_isDestroy = true;
	}
}
