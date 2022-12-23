#include <ProtStage.hpp>
#include <stdio.h>
#include <Windows.h>
#include <Geometory.h>
#include <Camera.hpp>
#include <DirectX.h>

// Stage00.cppを参考にジオメトリーで作成
CProtScene::CProtScene()
{
	m_stageData = { 1, 1 };
	// ここで読み込み※メモリリーク注意
	FILE* fp = fopen("Assets/Data/Test.dat", "rb");
	if (fp == nullptr)
	{
		MessageBox(NULL, "ステージ読み込みエラー", "CProtSceneコンストラクタ", MB_OK);
	}
	else
	{
		fread(&m_stageData, sizeof(StageData), 1, fp);
		fclose(fp);
	}
	m_terrain = new CTerrainBase("Assets/Data/TestTerrain.dat", 100, 100);
	m_enemyManager.reset(new CProtEnemyManager());
	
	m_producePlane = new ProducePlane("Assets/Img/White.png");
	m_producePlane->SetProducePlaneInformation({ 0,0.5f,0 }, { 70, 70, 0 }, { 90,0,0 });
	m_producePlane->SetColor(0.7f, 0.7f, 0.7f, 1);

	for (int i = 0; i < 4; i++)
	{
		m_wall[i].reset(new ProducePlane("Assets/Img/White.png"));
		m_wall[i]->SetProducePlaneInformation({ cosf(i*3.14f/2) * 35,3.5f,sinf(i * 3.14f / 2) * 35 }, {70, 7, 0}, {0,-i * 90.0f + 90.0f,0});
		m_wall[i]->SetColor(0.3f, 0.76f, 1.0f, 0.5f);
	}
}

CProtScene::~CProtScene()
{
	delete m_producePlane;
}

void CProtScene::Update()
{
	// ステージのアップデート
	m_enemyManager->Update();
}

void CProtScene::Draw()
{
	m_producePlane->Draw();

	for (int i = 0; i < 4; i++)
	{
		m_wall[i]->Draw();
	}
	return;


	EnableDepth(true);
	// ステージのドロー
	SetGeometoryVPMatrix(CCameraBase::GetPrimaryViewMatrix(), CCameraBase::GetPrimaryProjectionMatrix());
	SetGeometoryTranslate(0,0,0);
	SetGeometoryScaling(m_stageData.sizeX,1, m_stageData.sizeZ);
	SetGeometoryRotation(0,0,0);
	SetColorPS(true, 0.7f, 0.7f, 0.7f, 1, m_stageData.sizeX, m_stageData.sizeZ);
	//DrawBox();


	// 壁
	const float wallHeight = 10.0f;
	SetGeometoryTranslate(m_stageData.sizeX / 2 + 0.5f, wallHeight / 2 + 0.5f,0);
	SetGeometoryScaling(wallHeight,1,m_stageData.sizeZ + 2);
	SetGeometoryRotation(0,0,3.14f / 2);
	SetColorPS(true, 0.3f, 0.76f, 1.0f, 0.5f, wallHeight, m_stageData.sizeX);
	DrawBox();

	SetGeometoryTranslate(-m_stageData.sizeX / 2 - 0.5f, wallHeight / 2 + 0.5f,0);
	SetGeometoryRotation(0,0,3.14f / 2);
	DrawBox();

	SetGeometoryTranslate(0, wallHeight / 2 + 0.5f, m_stageData.sizeZ / 2 + 0.5f);
	SetGeometoryScaling(m_stageData.sizeX + 2,1, wallHeight);
	SetGeometoryRotation(3.14f / 2,0,0);
	SetColorPS(true, 0.3f, 0.76f, 1.0f, 0.5f, m_stageData.sizeX, wallHeight);
	DrawBox();

	SetGeometoryTranslate(0, wallHeight / 2 + 0.5f, -m_stageData.sizeZ / 2 - 0.5f);
	SetGeometoryRotation(3.14f / 2,0,0);
	DrawBox();

	//m_terrain->Draw();


	SetColorPS(false);
}
