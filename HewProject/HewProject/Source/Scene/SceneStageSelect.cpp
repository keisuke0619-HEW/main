#include "SceneStageSelect.hpp"
#include <DebugCamera.hpp>
#include <UiManager.hpp>

#include <Controller.hpp>
#include <SceneManager.hpp>
#include <OverlayStagePrep.hpp>
CSceneStageSelect::CSceneStageSelect()
{
	// BGMSet("");	// BGM‚ð“ü‚ê‚éB
	m_isNext = false;
	auto tmp = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/StageSelect/test_sousaUI.png"), SORT_ORDER_DEFAULT);
	tmp.lock()->SetSize(400, 150);
	tmp.lock()->SetPos(1075, 642);
	
	m_ui[BACK] = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/StageSelect/test_BG.png"), SORT_ORDER_BACK);
	m_ui[BACK].lock()->SetData(640, 360, 1280, 720);

	const float stageIconSizeX = 300.0f;
	const float stageIconSizeY = 200.0f;
	const float stageIconPosMinX = 200.0f;
	const float stageIconPosMinY = 200.0f;
	const float stageIconPosAddX = 500.0f;
	const float stageIconPosAddY = 250.0f;
	const float stageIconPosRowDown = 250.0f;	// Žš‰º‚°‚Ý‚½‚¢‚ÈŠ´‚¶B‰E‚É‚¸‚ê‚é—Ê‚ð’²®

	m_ui[STAGE_ICON_01] = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/StageSelect/testLogo_Stage01.png"), SORT_ORDER_DEFAULT);
	m_ui[STAGE_ICON_01].lock()->SetData(
		stageIconPosMinX + stageIconPosAddX * 0 + stageIconPosRowDown * 0,
		stageIconPosMinY + stageIconPosAddY * 0,
		stageIconSizeX,
		stageIconSizeY
		);
	m_ui[STAGE_ICON_02] = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/StageSelect/testLogo_Stage02.png"), SORT_ORDER_DEFAULT);
	m_ui[STAGE_ICON_02].lock()->SetData(
		stageIconPosMinX + stageIconPosAddX * 1 + stageIconPosRowDown * 0,
		stageIconPosMinY + stageIconPosAddY * 0,
		stageIconSizeX,
		stageIconSizeY
		);
	m_ui[STAGE_ICON_03] = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/StageSelect/testLogo_Stage03.png"), SORT_ORDER_DEFAULT);
	m_ui[STAGE_ICON_03].lock()->SetData(
		stageIconPosMinX + stageIconPosAddX * 0 + stageIconPosRowDown * 1,
		stageIconPosMinY + stageIconPosAddY * 1,
		stageIconSizeX,
		stageIconSizeY
		);
	m_ui[STAGE_ICON_04] = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/StageSelect/testLogo_Stage04.png"), SORT_ORDER_DEFAULT);
	m_ui[STAGE_ICON_04].lock()->SetData(
		stageIconPosMinX + stageIconPosAddX * 1 + stageIconPosRowDown * 1,
		stageIconPosMinY + stageIconPosAddY * 1,
		stageIconSizeX,
		stageIconSizeY
		);


}

CSceneStageSelect::~CSceneStageSelect()
{
}

void CSceneStageSelect::Update()
{
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
	m_cursor = m_cursor < 0 ? 0 : m_cursor > 3 ? 3 : m_cursor;
}

void CSceneStageSelect::ChangeScene()
{
	if (Utility::GetKeyTrigger(KEY_SELECT))
	{
		auto tmp = new COverlayStagePrep();
		tmp->SetIsNext(&m_isNext);
		AddOverlay(tmp);
		return;
	}
	if (Utility::GetKeyTrigger(KEY_CANCEL))
	{
		CSceneManager::SetScene(SCENE_TITLE);
		return;
	}
	if (m_isNext)
	{
		switch (m_cursor + STAGE_ICON_01)
		{
		case STAGE_ICON_01:
			CSceneManager::SetScene(SCENE_STAGE01);
			break;
		case STAGE_ICON_02:
			//CSceneManager::SetScene(SCENE_STAGE01);
			break;
		case STAGE_ICON_03:
			//CSceneManager::SetScene(SCENE_STAGE01);
			break;
		case STAGE_ICON_04:
			//CSceneManager::SetScene(SCENE_STAGE01);
			break;
		default:
			break;
		}
	}
}

void CSceneStageSelect::SetUiAlpha()
{
	const int stageNum = STAGE_ICON_04 - STAGE_ICON_01 + 1;
	for (int i = 0; i < stageNum ; i++)
	{
		int uiID = i + STAGE_ICON_01;
		m_ui[uiID].lock()->SetColor255(128, 128, 128, 128);
		if (m_cursor % stageNum == i)
		{
			m_ui[uiID].lock()->SetColor255(255, 255, 255, 255);
		}
	}
}
