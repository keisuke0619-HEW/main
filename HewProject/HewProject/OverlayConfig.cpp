#include "OverlayConfig.hpp"

#include <Controller.hpp>
#include <DebugWindow.hpp>

const float OVERLAY_CONFIG_CENTER_X = 640.0f;
const float OVERLAY_CONFIG_X_BAR_POS_Y = 230.0f;
const float OVERLAY_CONFIG_Y_BAR_POS_Y = 350.0f;
const float OVERLAY_CONFIG_BAR_SIZE_X = 850.0f;
const float OVERLAY_CONFIG_BAR_SIZE_Y = 100.0f;
const float OVERLAY_CONFIG_CURSOR_SIZE_X = 20.0f;
const float OVERLAY_CONFIG_CURSOR_SIZE_Y = 60.0f;

COverlayConfig::COverlayConfig()
{
	auto tmp = new CGameUI("Assets/Img/PauseMenu/Back.png");
	tmp->SetPos({ 640, 360 });
	tmp->SetSize({ 900, 600 });
	Add("Back", tmp, SORT_ORDER_UI_BACK4);
	tmp = new CGameUI("Assets/Img/White.png");
	tmp->SetPos({ 640, 360 });
	tmp->SetSize({ 1280, 720 });
	tmp->SetColor255(0, 0, 0, 128);
	Add("Fade", tmp, SORT_ORDER_UI_BACKEND);
	m_speedXBar = new CGameUI("Assets/Img/PauseMenu/Bar.png");
	m_speedXBar->SetPos(OVERLAY_CONFIG_CENTER_X, OVERLAY_CONFIG_X_BAR_POS_Y);
	m_speedXBar->SetSize(OVERLAY_CONFIG_BAR_SIZE_X, OVERLAY_CONFIG_BAR_SIZE_Y);
	Add("XBar", m_speedXBar, SORT_ORDER_UI_BACK3);
	m_speedYBar = new CGameUI("Assets/Img/PauseMenu/Bar.png");
	m_speedYBar->SetPos(OVERLAY_CONFIG_CENTER_X, OVERLAY_CONFIG_Y_BAR_POS_Y);
	m_speedYBar->SetSize(OVERLAY_CONFIG_BAR_SIZE_X, OVERLAY_CONFIG_BAR_SIZE_Y);
	Add("YBar", m_speedYBar, SORT_ORDER_UI_BACK3);
	m_speedXCursor = new CGameUI("Assets/Img/PauseMenu/Cursor.png");
	m_speedXCursor->SetPos(OVERLAY_CONFIG_CENTER_X, OVERLAY_CONFIG_X_BAR_POS_Y);
	m_speedXCursor->SetSize(OVERLAY_CONFIG_CURSOR_SIZE_X, OVERLAY_CONFIG_CURSOR_SIZE_Y);
	Add("XCursor", m_speedXCursor);
	m_speedYCursor = new CGameUI("Assets/Img/PauseMenu/Cursor.png");
	m_speedYCursor->SetPos(OVERLAY_CONFIG_CENTER_X, OVERLAY_CONFIG_Y_BAR_POS_Y);
	m_speedYCursor->SetSize(OVERLAY_CONFIG_CURSOR_SIZE_X, OVERLAY_CONFIG_CURSOR_SIZE_Y);
	Add("YCursor", m_speedYCursor);
}

COverlayConfig::~COverlayConfig()
{
}

void COverlayConfig::Update()
{
	MoveCursor();
	SetStatus();
	if (Utility::GetKeyTrigger(KEY_CANCEL))
	{
		m_isDestroy = true;
	}
}

void COverlayConfig::MoveCursor()
{
	if (Utility::GetKeyTrigger(KEY_UP))
	{
		m_target--;
	}
	if (Utility::GetKeyTrigger(KEY_DOWN))
	{
		m_target++;
	}
	if (m_target < 0)
	{
		m_target = TARGET_MAX * 100;
	}

}

void COverlayConfig::SetStatus()
{
	const float addLevel = 0.3f;
	float add = 0;
	m_speedXBar->SetColor255(128, 128, 128, 128);
	m_speedXCursor->SetColor255(128, 128, 128, 128);
	m_speedYBar->SetColor255(128, 128, 128, 128);
	m_speedYCursor->SetColor255(128, 128, 128, 128);
	if (Utility::GetKeyPress(KEY_RIGHT))
	{
		add += addLevel;

	}
	if (Utility::GetKeyPress(KEY_LEFT))
	{
		add -= addLevel;
	}
	switch (m_target % TARGET_MAX)
	{
	case 0:
		m_speedXBar->SetColor255(255, 255, 255, 255);
		m_speedXCursor->SetColor255(255, 255, 255, 255);
		Utility::SetCameraSpeedX(Utility::GetCameraSpeedX() + add);
		break;
	case 1:
		m_speedYBar->SetColor255(255, 255, 255, 255);
		m_speedYCursor->SetColor255(255, 255, 255, 255);
		Utility::SetCameraSpeedY(Utility::GetCameraSpeedY() + add);
		break;
	default:
		break;
	}
	CDebugWindow::Print(ShimizuKeisuke, "SpeedX", Utility::GetCameraSpeedX());
	CDebugWindow::Print(ShimizuKeisuke, "SpeedY", Utility::GetCameraSpeedY());
}
