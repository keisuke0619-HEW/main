#include "SceneManager.hpp"

// ƒV[ƒ“
#include <SceneTest.hpp>
#include <SceneTitle.hpp>
#include<SceneResult.hpp>

std::unique_ptr<IScene> CSceneManager::m_scene;

void CSceneManager::SetScene(ESceneID ID)
{
	CCameraBase::DeleteCameraAll();
	switch (ID)
	{
	case SCENE_TITLE:
		m_scene.reset(new CSceneTitle());
		break;
	case SCENE_STAGE01:
		m_scene.reset(new CSceneTest());
		break;
	case SCENE_RESULT:
		m_scene.reset(new CSceneResult());
		break;
	default:
		break;
	}
}

void CSceneManager::Update()
{
	m_scene->BaseUpdate();
}

void CSceneManager::Draw()
{
	m_scene->BaseDraw();
}
