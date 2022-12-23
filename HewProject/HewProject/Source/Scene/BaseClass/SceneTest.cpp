#include "SceneTest.hpp"
#include<SceneManager.hpp>
#include <Player.hpp>
#include <PlayerCamera.hpp>
#include <DebugCamera.hpp>
#include <Input.h>
#include <ProtEnemy.hpp>
#include<Controller.hpp>
CSceneTest::CSceneTest()
{
	m_obj->Add(new CPlayer());
	CCameraBase::CreateCamera(new CDebugCamera(), "Debug");
	CCameraBase::CreateCamera(new CPlayerCamera(), "Player");
	CCameraBase::SetPrimaryCamera("Player");
	m_stage.reset(new CProtScene());
}

CSceneTest::~CSceneTest()
{
}

void CSceneTest::Update()
{
	m_stage->Update();
	if (Utility::GetKeyTrigger(Key_RETURN))
	{
		CSceneManager::SetScene(SCENE_RESULT);
	}
}

void CSceneTest::Draw()
{
	CSceneBase::Draw();
	m_stage->Draw();
}
