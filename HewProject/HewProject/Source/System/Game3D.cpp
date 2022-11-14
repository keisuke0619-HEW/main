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
	//m_model.reset(new Model());
	//m_model.get()->Load("Assets/unitychan/unitychan.fbx", 0.01f);
	//m_pModelVS = new VertexShader();
	//if (FAILED(m_pModelVS->Load("Assets/Shader/ModelVS.cso")))
	//	MessageBox(nullptr, "ModelVS.cso", "Error", MB_OK);
	//m_model->SetVertexShader(m_pModelVS);
	//m_pWVP = new ConstantBuffer();
	//m_pWVP->Create(sizeof(DirectX::XMFLOAT4X4) * 3);
	m_player.reset(new CPlayer);

	m_camera[0] = new CDebugCamera();
	m_camera[1] = new CPlayerCamera(m_player);
	m_player->SetCamera(m_camera[1]);
	m_stage.reset(new CStage00());
	m_camID = CAMERA_PLAYER;
}
Game3D::~Game3D()
{
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
}
