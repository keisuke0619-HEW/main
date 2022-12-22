#include "SceneTest.hpp"
#include <Player.hpp>
#include <PlayerCamera.hpp>
#include <DebugCamera.hpp>
#include <Input.h>
#include <ProtEnemy.hpp>
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
}

void CSceneTest::Draw()
{
	CSceneBase::Draw();
	m_stage->Draw();
}
