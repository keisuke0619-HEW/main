#include "Game3D.h"
#include "Geometory.h"
#include "Input.h"
#include <PlayerCamera.hpp>
#include <DebugCamera.hpp>
#include <DataPool.hpp>
int g_gameFrame = 0;
float g_geometoryAngleX = 0;
float g_geometoryAngleY = 0;



Game3D::Game3D()
{
	m_player.reset(new CPlayer);

	CCameraBase::CreateCamera(new CDebugCamera(), "Debug");
	CCameraBase::CreateCamera(new CPlayerCamera(m_player),"Player");
	m_stage.reset(new CStage00());
}
Game3D::~Game3D()
{
}

void Game3D::Update()
{
	SwapCamera();
	if(CCameraBase::GetPrimaryName() == "Player")
		m_player->Update();
	CCameraBase::UpdatePrimary();
	g_gameFrame++;
}
void Game3D::Draw()
{
	SetGeometoryVPMatrix(CCameraBase::GetPrimaryViewMatrix(), CCameraBase::GetPrimaryProjectionMatrix());
	m_stage.get()->Draw();
	m_player->Draw();
}

void Game3D::SwapCamera()
{
	if (!IsKeyPress(VK_RETURN))
		return;
	if (IsKeyTrigger('P'))
	{
		CCameraBase::SetPrimaryCamera("Player");
	}
	if (IsKeyTrigger('O'))
	{
		CCameraBase::SetPrimaryCamera("Debug");
	}
	//m_player->SetCamera(m_camera[m_camID]);
}
