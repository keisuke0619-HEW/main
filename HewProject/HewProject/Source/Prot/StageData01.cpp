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
	m_producePlane = new ProducePlane("Assets/Img/White.png");
	m_producePlane->SetProducePlaneInformation({ 0,0.5f,0 }, { 8.37f, 8.37f, 0 }, { 90,0,0 });
	m_producePlane->SetColor(0.3f, 0.3f, 0.3f, 1);
	//壁
	for (int i = 0; i < 4; i++)
	{
		m_wall[i].reset(new ProducePlane("Assets/Img/White.png"));
		m_wall[i]->SetProducePlaneInformation({ cosf(i*3.14f/2) * 35,3.5f,sinf(i * 3.14f / 2) * 35 }, {8.37f, 2.5f, 0}, {0,-i * 90.0f + 90.0f,0});
		m_wall[i]->SetColor(0.3f, 0.76f, 1.0f, 0.5f);
	}
	//柱
	/*m_param.pos.x = 0.0f;
	m_param.pos.y = 0.0f;
	m_param.pos.z = 0.0f;
	m_param.collisionType = COLLISION_NONE;
	m_param.tag = TAG_STATIC_OBJECT;*/
	CSceneBase::GetObjList().lock()->Add(new CPillar(-5,0,5));
	CSceneBase::GetObjList().lock()->Add(new CPillar(5, 0, 5));
	CSceneBase::GetObjList().lock()->Add(new Wall(-10, 0, -10));
	
	
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
}
