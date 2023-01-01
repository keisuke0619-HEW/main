#include "SceneStageSelect.hpp"
#include <DebugCamera.hpp>
#include <UiManager.hpp>

#include <Controller.hpp>
#include <SceneManager.hpp>

CSceneStageSelect::CSceneStageSelect()
{
	// BGMSet("");	// BGM‚ð“ü‚ê‚éB
	auto tmp = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/StageSelect/test_sousaUI.png"), SORT_ORDER_UI_FRONT4);
	tmp.lock()->SetSize(400, 150);
	tmp.lock()->SetPos(1075, 642);
	
	m_ui[BACK] = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/StageSelect/test_BG.png"), SORT_ORDER_UI_BACKEND);
	m_ui[BACK].lock()->SetData(640, 360, 1280, 720);

	const float stageIconSizeX = 300.0f;
	const float stageIconSizeY = 200.0f;
	const float stageIconPosMinX = 200.0f;
	const float stageIconPosMinY = 200.0f;
	const float stageIconPosAddX = 500.0f;
	const float stageIconPosAddY = 250.0f;
	const float stageIconPosRowDown = 250.0f;	// Žš‰º‚°‚Ý‚½‚¢‚ÈŠ´‚¶B‰E‚É‚¸‚ê‚é—Ê‚ð’²®

	m_ui[STAGE_ICON_01] = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/StageSelect/testLogo_Stage01.png"), SORT_ORDER_UI_FRONT4);
	m_ui[STAGE_ICON_01].lock()->SetData(
		stageIconPosMinX + stageIconPosAddX * 0 + stageIconPosRowDown * 0,
		stageIconPosMinY + stageIconPosAddY * 0,
		stageIconSizeX,
		stageIconSizeY
		);
	m_ui[STAGE_ICON_02] = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/StageSelect/testLogo_Stage02.png"), SORT_ORDER_UI_FRONT4);
	m_ui[STAGE_ICON_02].lock()->SetData(
		stageIconPosMinX + stageIconPosAddX * 1 + stageIconPosRowDown * 0,
		stageIconPosMinY + stageIconPosAddY * 0,
		stageIconSizeX,
		stageIconSizeY
		);
	m_ui[STAGE_ICON_03] = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/StageSelect/testLogo_Stage03.png"), SORT_ORDER_UI_FRONT4);
	m_ui[STAGE_ICON_03].lock()->SetData(
		stageIconPosMinX + stageIconPosAddX * 0 + stageIconPosRowDown * 1,
		stageIconPosMinY + stageIconPosAddY * 1,
		stageIconSizeX,
		stageIconSizeY
		);
	m_ui[STAGE_ICON_04] = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/StageSelect/testLogo_Stage04.png"), SORT_ORDER_UI_FRONT4);
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
	if (Utility::GetKeyTrigger(KEY_SELECT))
	{
		CSceneManager::SetScene(SCENE_STAGE01);
	}
	if (Utility::GetKeyTrigger(KEY_CANCEL))
	{
		CSceneManager::SetScene(SCENE_TITLE);
	}
}
