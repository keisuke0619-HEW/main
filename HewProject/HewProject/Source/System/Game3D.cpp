#include "Game3D.h"
#include <DebugWindow.hpp>
//--- Scenes ---//
#include <SceneTest.hpp>

Game3D::Game3D()
{
	m_scenes.reset(new CSceneManager());
	m_scenes->SetScene(new CSceneTest());
	CDebugWindow::Create();
}
Game3D::~Game3D()
{
	CDebugWindow::Close();
}

void Game3D::Update()
{
	m_scenes->Update();
}
void Game3D::Draw()
{
	m_scenes->Draw();
}