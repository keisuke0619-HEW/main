#include <ProtStage.hpp>
#include <stdio.h>
#include <Windows.h>
#include <Geometory.h>
#include <Camera.hpp>
#include <DirectX.h>

// Stage00.cpp���Q�l�ɃW�I���g���[�ō쐬
CProtScene::CProtScene()
{
	m_stageData = { 1, 1 };
	// �����œǂݍ��݁����������[�N����
	FILE* fp = fopen("Assets/Data/Test.dat", "rb");
	if (fp == nullptr)
	{
		MessageBox(NULL, "�X�e�[�W�ǂݍ��݃G���[", "CProtScene�R���X�g���N�^", MB_OK);
	}
	else
	{
		fread(&m_stageData, sizeof(StageData), 1, fp);
		fclose(fp);
	}
	m_terrain = new CTerrainBase("Assets/Data/TestTerrain.dat", 100, 100);
	m_enemyManager.reset(new CProtEnemyManager());
	
	m_producePlane = new ProducePlane("Assets/Img/White.png");
	m_producePlane->SetProducePlaneInformation({ 0,0.5f,0 }, { 8.37f, 8.37f, 0 }, { 90,0,0 });
	m_producePlane->SetColor(0.3f, 0.3f, 0.3f, 1);

	for (int i = 0; i < 4; i++)
	{
		m_wall[i].reset(new ProducePlane("Assets/Img/White.png"));
		m_wall[i]->SetProducePlaneInformation({ cosf(i*3.14f/2) * 35,3.5f,sinf(i * 3.14f / 2) * 35 }, {8.37f, 2.5f, 0}, {0,-i * 90.0f + 90.0f,0});
		m_wall[i]->SetColor(0.3f, 0.76f, 1.0f, 0.5f);
	}
}

CProtScene::~CProtScene()
{
	delete m_producePlane;
}

void CProtScene::Update()
{
	// �X�e�[�W�̃A�b�v�f�[�g
	m_enemyManager->Update();
}

void CProtScene::Draw()
{
	m_producePlane->Draw();

	for (int i = 0; i < 4; i++)
	{
		m_wall[i]->Draw();
	}
}
