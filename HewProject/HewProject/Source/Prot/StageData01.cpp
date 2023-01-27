#include <StageData01.hpp>
#include <stdio.h>
#include <Windows.h>
#include <Geometory.h>
#include <Camera.hpp>
#include <DirectX.h>

#include <ObjectManager.hpp>
#include <Pillar.hpp>
#include<Wall.hpp>

// Stage00.cppを参考にジオメトリーで作成
CStageData01::CStageData01(Data* data)
	//:CObjectBase("Assets/Model/kaidan.fbx", 0.1f)
{
	m_enemyManager.reset(new CProtEnemyManager(data, 30, 0));
	m_stageData = { 70.0f,70.0f };

	//床
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m_producePlane[i * 4 + j] = new ProducePlane("Assets/Img/Game/yuka.tif");
			m_producePlane[i * 4 + j]->SetProducePlaneInformation({(j * 2 - 3) * (m_stageData.sizeX / 8.0f),0.f,(i * 2 - 2) * (m_stageData.sizeZ / 6.0f)}, { m_stageData.sizeX / 4.0f, m_stageData.sizeZ / 3.0f, 0.0f }, { 90.0f, 0.f, 0.f });
			m_producePlane[i * 4 + j]->SetColor(1.0f, 1.0f, 1.0f, 1);
		}
	}
	
	//壁
	// 前
	for (int i = 0; i < 3; i++)
	{
		m_wall[i].reset(new ProducePlane("Assets/Img/Game/kabe.tif"));
		m_wall[i]->SetProducePlaneInformation({ (i * 2 - 2) * (m_stageData.sizeX / 6.0f), 12.0f, m_stageData.sizeZ / 2.0f }, { m_stageData.sizeX / 3.0f, 24.0f, 0.f }, { 0.f, 0.f, 0.f });
		m_wall[i]->SetColor(1.0f, 1.0f, 1.0f, 1);
	}
	// 後
	for (int i = 0; i < 3; i++)
	{
		m_wall[3 + i].reset(new ProducePlane("Assets/Img/Game/kabe.tif"));
		m_wall[3 + i]->SetProducePlaneInformation({ (i * 2 - 2) * (m_stageData.sizeX / 6.0f), 12.0f, -m_stageData.sizeZ / 2.0f }, { m_stageData.sizeX / 3.0f, 24.0f, 0.f }, { 0.f, 180.f, 0.f });
		m_wall[3 + i]->SetColor(1.0f, 1.0f, 1.0f, 1);
	}
	// 右
	for (int i = 0; i < 3; i++)
	{
		m_wall[6 + i].reset(new ProducePlane("Assets/Img/Game/kabe.tif"));
		m_wall[6 + i]->SetProducePlaneInformation({m_stageData.sizeX / 2.0f, 12.0f,(i * 2 - 2) * (m_stageData.sizeZ / 6.0f) }, { m_stageData.sizeZ / 3.0f, 24.0f, 0 }, { 0.f, 90.0f, 0.f });
		m_wall[6 + i]->SetColor(1.0f, 1.0f, 1.0f, 1);
	}
	// 左
	for (int i = 0; i < 3; i++)
	{
		m_wall[9 + i].reset(new ProducePlane("Assets/Img/Game/kabe.tif"));
		m_wall[9 + i]->SetProducePlaneInformation({ -m_stageData.sizeX / 2.0f, 12.0f,(i * 2 - 2) * (m_stageData.sizeZ / 6.0f) }, { m_stageData.sizeX / 3.0f, 24.0f, 0 }, { 0.f, 270.0f, 0.f });
		m_wall[9 + i]->SetColor(1.0f, 1.0f, 1.0f, 1);
	}

	// 天井
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m_roof[i * 4 + j].reset(new ProducePlane("Assets/Img/Game/tenjyou.tif"));
			m_roof[i * 4 + j]->SetProducePlaneInformation({ (j * 2 - 3) * (m_stageData.sizeX / 8.0f),24.f,(i * 2 - 2) * (m_stageData.sizeZ / 6.0f) }, { m_stageData.sizeX / 4.0f, m_stageData.sizeZ / 3.0f, 0.0f }, { -90.0f, 0.f, 0.f });
			m_roof[i * 4 + j]->SetColor(1.0f, 1.0f, 1.0f, 1);
		}
	}

	//柱
	//(new CPillar(-20,0,20));POSのX,Y,Zの順で並んでいるので調整お願いします
	CSceneBase::GetObjList().lock()->Add(new CPillar(-20,0,20));
	CSceneBase::GetObjList().lock()->Add(new CPillar(20, 0,-20));

	//壁
	//(new Wall(-20, 0, -20,0,90*3.1415/180,0))POSのX,Y,Z、ROTのYを回転させるならtrueで並んでいるので調整お願いします
	CSceneBase::GetObjList().lock()->Add(new Wall(20, 0, 20, true));
	CSceneBase::GetObjList().lock()->Add(new Wall(-20, 0, -20,true));
}

CStageData01::~CStageData01()
{
	for (int i = 0; i < 12; i++)
	{
		delete m_producePlane[i];
	}
}

void CStageData01::Update()
{
	// ステージのアップデート
	m_enemyManager->Update();
}

void CStageData01::Draw()
{
	for (int i = 0; i < 12; i++)
	{
		m_producePlane[i]->Draw();
	}

	for (int i = 0; i < 12; i++)
	{
		m_wall[i]->Draw();
	}

	for (int i = 0; i < 12; i++)
	{
		m_roof[i]->Draw();
	}
	
}
