#include "Game3D.h"
#include <DebugWindow.hpp>
#include <Controller.hpp>
#include <Sprite.h>
#include <Blend.hpp>
#include <SamplerState.h>
#include <BGM.h>
#include <Billboard.h>
#include <OutputEffekseer.h>
#include <NumberUI.hpp>
//--- Scenes ---//

Game3D::Game3D()
{
	m_scenes.reset(new CSceneManager());
	m_scenes->SetScene(SCENE_TITLE);
	CDebugWindow::Create();
	Sprite::Init();
	Utility::InitBlendState();
	Utility::SetBlendState(BLEND_NONE);
	Utility::ControllerInit();
	auto sp = new SamplerState();
	sp->Create(D3D11_FILTER_MIN_MAG_MIP_POINT, D3D11_TEXTURE_ADDRESS_WRAP);
	CEffect::InitSystem();
	CNumberUI::Init();
}
Game3D::~Game3D()
{
	CNumberUI::Uninit();
	CEffect::UninitSystem();
	CBillboard::ClearBillboard();
	Utility::UninitBlendState();
	Sprite::Uninit();
	CDebugWindow::Close();
}

void Game3D::Update()
{
	Utility::ControllerUpdate();
	CSound::GetIns()->Update();
	m_scenes->Update();
}
void Game3D::Draw()
{
	m_scenes->Draw();
}