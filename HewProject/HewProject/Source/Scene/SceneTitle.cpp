#include "SceneTitle.hpp"
#include <SceneManager.hpp>
#include <DebugCamera.hpp>
#include <Controller.hpp>
#include <UiManager.hpp>

CSceneTitle::CSceneTitle()
{

	m_TitleUI = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/titleSceneUI.png"));
	m_TitleUI.lock()->SetSize({ 1200.0f, 600.0f });
	m_TitleUI.lock()->SetPos({ 640.0f, 360.0f });

	SetBGM("Assets/Sound/ExtendedWinter.wav");
	
}

CSceneTitle::~CSceneTitle()
{
}

void CSceneTitle::Update()
{
	m_TitleUI.lock()->Draw();

	if (Utility::GetKeyTrigger(KEY_SELECT))
	{
		CSceneManager::SetScene(SCENE_STAGE_SELECT);
	}
	if (Utility::GetKeyTrigger(KEY_BEAM))
	{
		SetBGM("Assets/Sound/korinoyaiba.wav");
	}
}


