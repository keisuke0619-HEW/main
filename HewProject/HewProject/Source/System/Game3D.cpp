#include "Game3D.h"
#include <DebugWindow.hpp>
#include <Controller.hpp>
#include <Sprite.h>
#include <Blend.hpp>
#include <SamplerState.h>

//--- Scenes ---//
#include <SceneTest.hpp>

Game3D::Game3D()
{
	m_scenes.reset(new CSceneManager());
	m_scenes->SetScene(new CSceneTest());
	CDebugWindow::Create();
	Sprite::Init();
	Utility::InitBlendState();
	Utility::SetBlendState(BLEND_NONE);
	Utility::ControllerInit();
	auto sp = new SamplerState();
	sp->Create(D3D11_FILTER_MIN_MAG_MIP_POINT, D3D11_TEXTURE_ADDRESS_WRAP);

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