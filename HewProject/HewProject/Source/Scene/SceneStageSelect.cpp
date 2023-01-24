#include "SceneStageSelect.hpp"
#include <DebugCamera.hpp>
#include <UiManager.hpp>

#include <Controller.hpp>
#include <SceneManager.hpp>
#include <OverlayStagePrep.hpp>
#include <OverlayConfig.hpp>
CSceneStageSelect::CSceneStageSelect()
{
	// BGMSet("");	// BGMを入れる。
	m_isNext = false;
	auto tmp = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/StageSelect/test_sousaUI.png"), SORT_ORDER_DEFAULT);
	tmp.lock()->SetSize(400, 150);
	tmp.lock()->SetPos(1075, 642);

	m_ui[BACK] = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/StageSelect/test_BG.png"), SORT_ORDER_BACK);
	m_ui[BACK].lock()->SetData(640, 360, 1280, 720);
	m_ui[SETUMEI] = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/StageSelect/test_sousaTab.png"), SORT_ORDER_FRONT);
	m_ui[SETUMEI].lock()->SetData(640, 360, 960, 540);
	m_ui[SETUMEI].lock()->SetColor(0, 0, 0, 0);

	const float stageIconSizeX = 300.0f;
	const float stageIconSizeY = 300.0f;
	const float stageIconPosMinX = 245.0f;
	const float stageIconPosMinY = 330.0f;
	const float stageIconPosAddX = 400.0f;

	m_ui[STAGE_ICON_01] = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/StageSelect/test_configIcon.png"), SORT_ORDER_DEFAULT);
	m_ui[STAGE_ICON_01].lock()->SetData(
		stageIconPosMinX + stageIconPosAddX * 0,
		stageIconPosMinY,
		stageIconSizeX,
		stageIconSizeY
	);
	m_ui[STAGE_ICON_02] = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/StageSelect/test_stageIcon.png"), SORT_ORDER_DEFAULT);
	m_ui[STAGE_ICON_02].lock()->SetData(
		stageIconPosMinX + stageIconPosAddX * 1,
		stageIconPosMinY,
		stageIconSizeX,
		stageIconSizeY
	);
	m_ui[STAGE_ICON_03] = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/StageSelect/test_sousaIcon.png"), SORT_ORDER_DEFAULT);
	m_ui[STAGE_ICON_03].lock()->SetData(
		stageIconPosMinX + stageIconPosAddX * 2,
		stageIconPosMinY,
		stageIconSizeX,
		stageIconSizeY
	);

	m_nowIcon = STAGE_ICON_01;
	m_cursor = 1;
}

CSceneStageSelect::~CSceneStageSelect()
{
}

void CSceneStageSelect::Update()
{
	if (m_nowIcon == STAGE_ICON_03)
	{
		if (Utility::GetKeyTrigger(KEY_CONFIG))
		{
			m_ui[SETUMEI].lock()->SetColor(0, 0, 0, 0);
			m_ui[BACK].lock()->SetColor(1, 1, 1, 1);
		}
	}
	MoveCursor();
	SetUiAlpha();
	ChangeScene();

}

void CSceneStageSelect::MoveCursor()
{
	if (Utility::GetKeyTrigger(KEY_RIGHT))
	{
		m_cursor++;
	}
	if (Utility::GetKeyTrigger(KEY_LEFT))
	{
		m_cursor--;
	}
	m_cursor = m_cursor < 0 ? 2 : m_cursor;
	m_cursor = m_cursor > 2 ? 0 : m_cursor;
}

void CSceneStageSelect::ChangeScene()
{
	if (Utility::GetKeyTrigger(KEY_SELECT))
	{
		switch (m_nowIcon)
		{
		case STAGE_ICON_01:
			AddOverlay(new COverlayConfig());
			break;
		case STAGE_ICON_02:
			AddOverlay(new COverlayStagePrep());
			return;
		case STAGE_ICON_03:
			m_ui[SETUMEI].lock()->SetColor(1, 1, 1, 1);
			m_ui[BACK].lock()->SetColor(0.2, 0.2, 0.2, 1);
			return;
		default:
			break;
		}
	}
	if (Utility::GetKeyTrigger(KEY_CANCEL))
	{
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
		m_ui[uiID].lock()->SetColor255(128, 128, 128, 128);
		if (m_cursor % stageNum == i)
		{
			m_ui[uiID].lock()->SetColor255(255, 255, 255, 255);
		}
	}
}
