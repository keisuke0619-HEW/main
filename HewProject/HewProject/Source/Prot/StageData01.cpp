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
CStageData01::CStageData01()
	//:CObjectBase("Assets/Model/kaidan.fbx", 0.1f)
{
	m_enemyManager.reset(new CProtEnemyManager());
	//床
	m_producePlane = new ProducePlane("Assets/Img/Game/yuka.tif");
	m_producePlane->SetProducePlaneInformation({ 0,0.f,0 }, { 70, 70,0 }, { 90,0,0 });
	m_producePlane->SetColor(1.0f, 1.0f, 1.0f, 1);
	//壁
	for (int i = 0; i < 4; i++)
	{
		m_wall[i].reset(new ProducePlane("Assets/Img/Game/kabe.tif"));
		m_wall[i]->SetProducePlaneInformation({ cosf(i*3.14f/2) * 35,8.0f,sinf(i * 3.14f / 2) * 35 }, {70.5f, 16.0f, 0}, {0,-i * 90.0f + 90.0f,0});
		m_wall[i]->SetColor(1.0f, 1.0f, 1.0f, 1);
	}
	// 天井
	m_roof.reset(new ProducePlane("Assets/Img/Game/tenjyou.tif"));
	m_roof->SetProducePlaneInformation({ 0,16,0 }, { 70.0f, 70.0f,0 }, { 270,0,0 });
	m_roof->SetColor(1, 1, 1, 1);
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
	delete m_producePlane;
	
}

void CStageData01::Update()
{
	// ステージのアップデート
	m_enemyManager->Update();
}

void CStageData01::Draw()
{
	m_producePlane->Draw();
	
	for (int i = 0; i < 4; i++)
	{
		m_wall[i]->Draw();
	}
	m_roof->Draw();
}
