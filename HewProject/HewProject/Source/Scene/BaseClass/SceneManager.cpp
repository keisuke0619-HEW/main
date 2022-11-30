#include "SceneManager.hpp"

std::unique_ptr<IScene> CSceneManager::m_scene;

void CSceneManager::SetScene(IScene* scene)
{
	m_scene.reset(scene);
}

void CSceneManager::Update()
{
	m_scene->BaseUpdate();
}

void CSceneManager::Draw()
{
	m_scene->BaseDraw();
}
