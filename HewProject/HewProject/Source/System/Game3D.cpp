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
#include <MiniMap.h>
#include <SE.h>
//--- Scenes ---//

Game3D::Game3D()
{
	CSceneManager::SetScene(SCENE_TITLE);
	//CSceneManager::SwapScene();
	CDebugWindow::Create();
	Sprite::Init();
	Utility::InitBlendState();
	Utility::SetBlendState(BLEND_NONE);
	Utility::ControllerInit();
	CEffect::InitSystem();
	CNumberUI::Init();
	CMiniMap::Init();
	CSoundSE::Init();
}
Game3D::~Game3D()
{
	CMiniMap::Uninit();
	CNumberUI::Uninit();
	CEffect::UninitSystem();
	CBillboard::ClearBillboard();
	Utility::UninitBlendState();
	Sprite::Uninit();
	CDebugWindow::Close();
}

void Game3D::Update()
{
	CSceneManager::SwapScene();
	Utility::ControllerUpdate();
	CSound::GetIns()->Update();
	CSceneManager::Update();
}
void Game3D::Draw()
{
	CSceneManager::Draw();
}