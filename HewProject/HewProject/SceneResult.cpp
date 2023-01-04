#include "SceneResult.hpp"
#include <SceneManager.hpp>
#include <DebugCamera.hpp>
#include <Controller.hpp>
#include <UiManager.hpp>
CSceneResult::CSceneResult()
{
	m_ResultUI = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/resultSceneUI.png"));
	m_ResultUI.lock()->SetSize({ 1200.f, 600.f });
	m_ResultUI.lock()->SetPos({ 640.f, 360.f });
	// âπÉfÅ[É^ÇÃì«Ç›çûÇ›
	//BGMSet("Assets/Sound/korinoyaiba.wav");
	
}

CSceneResult::~CSceneResult()
{
}

void CSceneResult::Update()
{
	if (Utility::GetKeyTrigger(KEY_SELECT))
	{
		CSceneManager::SetScene(SCENE_STAGE_SELECT);
	}
}
