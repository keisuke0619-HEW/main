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

	//BGMSet("Assets/Sound/ExtendedWinter.wav");
	m_pBGM = new CSound;
	m_pBGM->BGMSet("Assets/Sound/ExtendedWinter.wav", 0.f);
	m_pBGM->SetVolumeFade(0.5f, 10);
	
}

CSceneTitle::~CSceneTitle()
{
}

void CSceneTitle::Update()
{
	m_TitleUI.lock()->Draw();
	m_pBGM->Update();

	if (Utility::GetKeyTrigger(KEY_SELECT))
	{
		CSceneManager::SetScene(SCENE_STAGE_SELECT);
	}
}


