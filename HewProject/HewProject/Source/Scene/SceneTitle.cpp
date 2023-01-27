#include "SceneTitle.hpp"
#include <SceneManager.hpp>
#include <DebugCamera.hpp>
#include <Controller.hpp>
#include <UiManager.hpp>
#include <OverlayConfig.hpp>
#include <OverlayAskBase.hpp>
#include <Startup.h>
#include <SE.h>

CSceneTitle::CSceneTitle()
{
	// ƒ^ƒCƒgƒ‹ƒƒS
	m_TitlerogoUI = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/Title/titlerogo.png"));
	m_TitlerogoUI.lock()->SetSize({ 702.0f, 436.0f });
	m_TitlerogoUI.lock()->SetPos({ 640.0f, 285.0f });

	m_StartUI = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/Title/start.png"));
	m_StartUI.lock()->SetSize({ 263.0f, 47.0f });
	m_StartUI.lock()->SetPos({ 640.0f, 530.0f });

	m_EndUI = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/Title/end.png"));
	m_EndUI.lock()->SetSize({ 181.0f, 47.0f });
	m_EndUI.lock()->SetPos({ 600.0f, 620.0f });
	
	// ”wŒi
	m_TitlebgUI = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/Title/title_background.png"));
	m_TitlebgUI.lock()->SetSize({ 1281.0f, 720.0f });
	m_TitlebgUI.lock()->SetPos({ 640.0f, 360.0f });

	SetBGM("Assets/Sound/ExtendedWinter.wav");
	
}

CSceneTitle::~CSceneTitle()
{
}

void CSceneTitle::Update()
{
	m_TitlerogoUI.lock()->Draw();
	m_StartUI.lock()->Draw();
	m_EndUI.lock()->Draw();
	m_TitlebgUI.lock()->Draw();

	if (Utility::GetKeyTrigger(KEY_SELECT))
	{
		CSoundSE::Start(CSoundSE::SE_SELECT);
		CSceneManager::SetScene(SCENE_STAGE_SELECT);
	}
	if (Utility::GetKeyTrigger(KEY_BEAM))
	{
		SetBGM("Assets/Sound/korinoyaiba.wav");
	}
	if (Utility::GetKeyTrigger(KEY_CANCEL))
	{
		AddOverlay(new COverlayAskBase("Assets/Img/PauseMenu/Label_Exit.png", GetLoopPointer() ));

		CSoundSE::Start(CSoundSE::SE_CANCEL);
	}
}


