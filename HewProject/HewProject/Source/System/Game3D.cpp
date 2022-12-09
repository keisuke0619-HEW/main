#include "Game3D.h"
#include <DebugWindow.hpp>
#include <Controller.hpp>
#include <Sprite.h>
#include <Blend.hpp>

//--- Scenes ---//
#include <SceneTest.hpp>

Game3D::Game3D()
{
	m_scenes.reset(new CSceneManager());
	m_scenes->SetScene(new CSceneTest());
	CDebugWindow::Create();
	Sprite::Init();
	Utility::InitBlendState();
	Utility::SetBlendState(BLEND_ALPHA);
	Utility::ControllerInit();
}
Game3D::~Game3D()
{
	Utility::UninitBlendState();
	Sprite::Uninit();
	CDebugWindow::Close();
}

void Game3D::Update()
{
	Utility::ControllerUpdate();
	m_scenes->Update();
}
void Game3D::Draw()
{
	m_scenes->Draw();
}