#include "Game3D.h"
#include "Geometory.h"
#include "Input.h"
#include <PlayerCamera.hpp>
#include <DebugCamera.hpp>
//#include <DataPool.hpp>
#include <DebugWindow.hpp>
int g_gameFrame = 0;
float g_geometoryAngleX = 0;
float g_geometoryAngleY = 0;



Game3D::Game3D()
{
	m_player.reset(new CPlayer);

	CCameraBase::CreateCamera(new CDebugCamera(), "Debug");
	CCameraBase::CreateCamera(new CPlayerCamera(m_player),"Player");
	m_stage.reset(new CStage00());
	CDebugWindow::Create();
}
Game3D::~Game3D()
{
	CDebugWindow::Close();
}

void Game3D::Update()
{
	SwapCamera();
	if(CCameraBase::GetPrimaryName() == "Player")
		m_player->Update();
	CCameraBase::UpdatePrimary();
	if (IsKeyTrigger('C'))
		printf("debug\n");
		//CDebugWindow::Print(ShimizuKeisuke, "aaaaaaa%d%d\n", 1);
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
