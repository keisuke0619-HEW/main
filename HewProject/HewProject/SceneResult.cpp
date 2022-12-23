#include "SceneResult.hpp"
#include <SceneManager.hpp>
#include <DebugCamera.hpp>
#include <Controller.hpp>
CSceneResult::CSceneResult()
{
	CCameraBase::CreateCamera(new CDebugCamera(), "Debug");
	CCameraBase::SetPrimaryCamera("Debug");
}

CSceneResult::~CSceneResult()
{
}

void CSceneResult::Update()
{
	if (Utility::GetKeyTrigger(Key_RETURN))
	{
		CSceneManager::SetScene(SCENE_TITLE);
	}
}
