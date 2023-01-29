#include "SceneStageSelect.hpp"
#include <DebugCamera.hpp>
#include <UiManager.hpp>

#include <Controller.hpp>
#include <SceneManager.hpp>
#include <OverlayStagePrep.hpp>
#include <OverlayConfig.hpp>
#include <SE.h>
#include <BGM.h>

const float stageIconSizeX = 300.0f;
const float stageIconSizeY = 300.0f;
const float stageIconPosMinX = 245.0f;
const float stageIconPosMinY = 330.0f;
const float stageIconPosAddX = 400.0f;
CSceneStageSelect::CSceneStageSelect()
{
	// BGMSet("");	// BGM‚ð“ü‚ê‚éB
	m_isNext = false;
	auto tmp = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/StageSelect/satageSelect_sousa.png"), SORT_ORDER_DEFAULT);
	tmp.lock()->SetSize(400, 200);
	tmp.lock()->SetPos(1075, 602);

	m_ui[BACK] = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/Title/title_background.png"), SORT_ORDER_BACK);
	m_ui[BACK].lock()->SetData(640, 360, 1280, 720);

	

	/*m_ui[STAGE_ICON_01] = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/StageSelect/haguruma.png"), SORT_ORDER_DEFAULT);
	m_ui[STAGE_ICON_01].lock()->SetData(
		stageIconPosMinX + stageIconPosAddX * 0,
		stageIconPosMinY,
		stageIconSizeX,
		stageIconSizeY
	);*/
	m_gearRight = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/StageSelect/haguruma.png"), SORT_ORDER_DEFAULT);
	m_gearRight.lock()->SetData(stageIconPosMinX + stageIconPosAddX * 0.1,
		stageIconPosMinY,
		stageIconSizeX * 0.5f,
		stageIconSizeY * 0.5f);
	m_gearRight.lock()->SetRotation(359);
	m_gearLeft = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/StageSelect/haguruma.png"), SORT_ORDER_DEFAULT);
	m_gearLeft.lock()->SetData(stageIconPosMinX + stageIconPosAddX * -0.2,
		stageIconPosMinY * 0.8,
		stageIconSizeX * 0.5f,
		stageIconSizeY * 0.5f);
	m_ui[STAGE_ICON_02] = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/StageSelect/map icon.png"), SORT_ORDER_DEFAULT);
	m_ui[STAGE_ICON_02].lock()->SetData(
		stageIconPosMinX + stageIconPosAddX * 1,
		stageIconPosMinY,
		stageIconSizeX,
		stageIconSizeY
	);
	m_ui[STAGE_ICON_03] = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/StageSelect/setumeisyo.png"), SORT_ORDER_DEFAULT);
	m_ui[STAGE_ICON_03].lock()->SetData(
		stageIconPosMinX + stageIconPosAddX * 2,
		stageIconPosMinY,
		stageIconSizeX,
		stageIconSizeY
	);
	m_ui[STAGE_ICON_04] = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/StageSelect/fairu.png"), SORT_ORDER_DEFAULT);
	m_ui[STAGE_ICON_04].lock()->SetData(
		stageIconPosMinX + stageIconPosAddX * 2,
		stageIconPosMinY,
		stageIconSizeX,
		stageIconSizeY
	);
	m_ui[STAGE_ICON_04].lock()->SetColor255(0, 0, 0, 0);
	m_nowIcon = STAGE_ICON_01;
	m_cursor = 1;
	m_frame = 0;

	SetBGM("Assets/Sound/BGM/StageSelectBGM.mp3");
}

CSceneStageSelect::~CSceneStageSelect()
{
}

void CSceneStageSelect::Update()
{
	MoveCursor();
	SetUiAlpha();
	RotationIcon();
	ChangeScene();
}

void CSceneStageSelect::MoveCursor()
{
	if (Utility::GetKeyTrigger(KEY_RIGHT))
	{
		m_cursor++;
		//if(m_cursor < 2)
		CSoundSE::Start(CSoundSE::SE_CURSOR);
	}
	if (Utility::GetKeyTrigger(KEY_LEFT))
	{
		m_cursor--;
		//if(m_cursor > 0)
		CSoundSE::Start(CSoundSE::SE_CURSOR);
	}
	m_cursor = m_cursor < 0 ? 2 : m_cursor;
	m_cursor = m_cursor > 2 ? 0 : m_cursor;
}

void CSceneStageSelect::ChangeScene()
{
	if (Utility::GetKeyTrigger(KEY_SELECT))
	{
		CSoundSE::Start(CSoundSE::SE_SELECT);
		switch (m_nowIcon)
		{
		case STAGE_ICON_01:
			AddOverlay(new COverlayConfig());
			break;
		case STAGE_ICON_02:
			AddOverlay(new COverlayStagePrep());
			return;
		case STAGE_ICON_03:
			AddOverlay(new CSetumei());
			return;
		default:
			break;
		}
	}
	if (Utility::GetKeyTrigger(KEY_CANCEL))
	{
		CSoundSE::Start(CSoundSE::SE_CANCEL);
		CSceneManager::SetScene(SCENE_TITLE);
		return;
	}
	if (m_nowIcon)
	{
		switch (m_cursor + STAGE_ICON_01)
		{
		case STAGE_ICON_01:
			m_nowIcon = STAGE_ICON_01;
			break;
		case STAGE_ICON_02:
			m_nowIcon = STAGE_ICON_02;
			break;
		case STAGE_ICON_03:
			m_nowIcon = STAGE_ICON_03;
			break;
		default:
			break;
		}
	}
}

void CSceneStageSelect::SetUiAlpha()
{
	const int stageNum = STAGE_ICON_03 - STAGE_ICON_01 + 1;
	for (int i = 0; i < stageNum; i++)
	{
		int uiID = i + STAGE_ICON_01;
		if (uiID == STAGE_ICON_01)
		{
			m_gearRight.lock()->SetColor255(128, 128, 128, 128);
			m_gearLeft.lock()->SetColor255(128, 128, 128, 128);
			if (m_cursor % stageNum == i)
			{
				m_gearRight.lock()->SetColor255(255, 255, 255, 255);
				m_gearLeft.lock()->SetColor255(255, 255, 255, 255);
			}
		}
		else
		{
			m_ui[uiID].lock()->SetColor255(128, 128, 128, 128);
			if (m_cursor % stageNum == i)
			{
				m_ui[uiID].lock()->SetColor255(255, 255, 255, 255);
			}
		}
		
	}
}

void CSceneStageSelect::RotationIcon()
{
	if (m_cursor == 0)
	{
		m_gearRight.lock()->SetRotation(m_frame);
		m_gearLeft.lock()->SetRotation(-m_frame);
	}
	else
	{
		m_gearRight.lock()->SetRotation(m_frame * 0.2);
		m_gearLeft.lock()->SetRotation(-m_frame * 0.2);
	}
	if (m_cursor == 1)
	{
		m_ui[STAGE_ICON_02].lock()->SetRotation((sinf(m_frame * 0.1)) * 3);
	}
	else
	{
		m_ui[STAGE_ICON_02].lock()->SetRotation(0);
	}
	if (m_cursor == 2)
	{
		m_ui[STAGE_ICON_03].lock()->SetColor255(255, 255, 255, 0);
		m_ui[STAGE_ICON_04].lock()->SetColor255(255, 255, 255, 255);
		m_ui[STAGE_ICON_04].lock()->SetPos(m_ui[STAGE_ICON_04].lock()->GetPos().x, m_ui[STAGE_ICON_04].lock()->GetPos().y + (sinf(m_frame * 0.1) * 2));
	}
	else
	{
		m_ui[STAGE_ICON_03].lock()->SetColor255(128, 128, 128, 128);
		m_ui[STAGE_ICON_04].lock()->SetColor255(255, 255, 255, 0);
	}
}
