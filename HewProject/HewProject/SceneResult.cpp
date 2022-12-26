#include "SceneResult.hpp"
#include <SceneManager.hpp>
#include <DebugCamera.hpp>
#include <Controller.hpp>
#include <UiManager.hpp>
CSceneResult::CSceneResult()
{
	CCameraBase::CreateCamera(new CDebugCamera(), "Debug");
	CCameraBase::SetPrimaryCamera("Debug");
	m_ResultUI = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/resultSceneUI.png"));
	m_ResultUI.lock()->SetSize({ 1200.f, 600.f });
	m_ResultUI.lock()->SetPos({ 640.f, 360.f });
	// 音データの読み込み
	m_pBGM = CreateSound("Assets/Sound/korinoyaiba.wav", true);
	// BGMの再生
	m_pBGMSource = StartSound(m_pBGM);
	m_pBGMSource->SetVolume(0.05f);	// 1が最大
	
}

CSceneResult::~CSceneResult()
{
}

void CSceneResult::Update()
{
	if (Utility::GetKeyTrigger(KEY_DEBUG_RETURN))
	{
		m_pBGMSource->Stop();
		CSceneManager::SetScene(SCENE_TITLE);
	}
}
