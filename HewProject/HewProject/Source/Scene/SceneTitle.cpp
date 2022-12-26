#include "SceneTitle.hpp"
#include <SceneManager.hpp>
#include <DebugCamera.hpp>
#include <Controller.hpp>
#include <UiManager.hpp>

CSceneTitle::CSceneTitle()
{
	CCameraBase::CreateCamera(new CDebugCamera(), "Debug");
	CCameraBase::SetPrimaryCamera("Debug");

	m_TitleUI = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/titleSceneUI.png"));
	m_TitleUI.lock()->SetSize({ 1200.0f, 600.0f });
	m_TitleUI.lock()->SetPos({ 640.0f, 360.0f });
	// ‰¹ƒf[ƒ^‚Ì“Ç‚Ýž‚Ý
	m_pBGM = CreateSound("Assets/Sound/ExtendedWinter.wav", true);
	// BGM‚ÌÄ¶
	m_pBGMSource = StartSound(m_pBGM);
	m_pBGMSource->SetVolume(0.05f);	// 1‚ªÅ‘å
}

CSceneTitle::~CSceneTitle()
{
}

void CSceneTitle::Update()
{
	m_TitleUI.lock()->Draw();

	if (Utility::GetKeyTrigger(KEY_DEBUG_RETURN))
	{
		m_pBGMSource->Stop();
		CSceneManager::SetScene(SCENE_STAGE01);
	}
}


