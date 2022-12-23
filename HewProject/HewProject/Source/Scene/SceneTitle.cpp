#include "SceneTitle.hpp"
#include <SceneManager.hpp>
#include <DebugCamera.hpp>
#include <Controller.hpp>
CSceneTitle::CSceneTitle()
{
	CCameraBase::CreateCamera(new CDebugCamera(), "Debug");
	CCameraBase::SetPrimaryCamera("Debug");
}

CSceneTitle::~CSceneTitle()
{
}

void CSceneTitle::Update()
{
	if (Utility::GetKeyTrigger(Key_RETURN))
	{
		CSceneManager::SetScene(SCENE_STAGE01);
	}
}


