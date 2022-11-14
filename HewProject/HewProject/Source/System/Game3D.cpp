#include "Game3D.h"
#include "Geometory.h"
#include "Input.h"
#include <PlayerCamera.hpp>
#include <DebugCamera.hpp>
int g_gameFrame = 0;
float g_geometoryAngleX = 0;
float g_geometoryAngleY = 0;



Game3D::Game3D()
{
	m_player.reset(new CPlayer);

	m_camera[0] = new CDebugCamera();
	m_camera[1] = new CPlayerCamera(m_player);
	m_player->SetCamera(m_camera[1]);
	m_stage.reset(new CStage00());
	m_camID = CAMERA_PLAYER;
}
Game3D::~Game3D()
{
	for (int i = 0; i < CAMERA_MAX; i++)
	{
		delete m_camera[i];
	}
}

void Game3D::Update()
{
	SwapCamera();
	if(m_camID == CAMERA_PLAYER)
		m_player->Update();
	m_camera[m_camID]->Update();
	g_gameFrame++;
}
void Game3D::Draw()
{
	SetGeometoryVPMatrix(m_camera[m_camID]->GetViewMatrix(), m_camera[m_camID]->GetProjectionMatrix());
	m_stage.get()->Draw();
	m_player->Draw();
}

void Game3D::SwapCamera()
{
	if (!IsKeyPress(VK_RETURN))
		return;
	if (IsKeyTrigger('P'))
	{
		m_camID = CAMERA_PLAYER;
	}
	if (IsKeyTrigger('O'))
	{
		m_camID = CAMERA_DEBUG;
	}
	m_player->SetCamera(m_camera[m_camID]);
}
