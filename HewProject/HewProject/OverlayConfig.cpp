#include "OverlayConfig.hpp"

#include <Controller.hpp>
COverlayConfig::COverlayConfig()
{
	auto tmp = new CGameUI("Assets/Img/enemy.png");
	tmp->SetPos({ 100, 100 });
	tmp->SetSize({ 100, 100 });
	Add("Test", tmp);
}

COverlayConfig::~COverlayConfig()
{
}

void COverlayConfig::Update()
{
	if (Utility::GetKeyTrigger(Key_ESCAPE))
	{
		m_isDestroy = true;
	}
}
