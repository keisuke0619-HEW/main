#include "OverlayConfig.hpp"

#include <Controller.hpp>
#include <DebugWindow.hpp>
COverlayConfig::COverlayConfig()
{
	auto tmp = new CGameUI("Assets/Img/PauseMenu/Back.png");
	tmp->SetPos({ 640, 360 });
	tmp->SetSize({ 900, 600 });
	Add("Back", tmp);
	tmp = new CGameUI("Assets/Img/White.png");
	tmp->SetPos({ 640, 360 });
	tmp->SetSize({ 1280, 720 });
	tmp->SetColor255(0, 0, 0, 128);
	Add("Fade", tmp, SORT_ORDER_UI_BACKEND);
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
		Utility::SetCameraSpeedX(Utility::GetCameraSpeedX() + add);
		break;
	case 1:
		Utility::SetCameraSpeedY(Utility::GetCameraSpeedY() + add);
		break;
	default:
		break;
	}
	CDebugWindow::Print(ShimizuKeisuke, "SpeedX", Utility::GetCameraSpeedX());
	CDebugWindow::Print(ShimizuKeisuke, "SpeedY", Utility::GetCameraSpeedY());
}
