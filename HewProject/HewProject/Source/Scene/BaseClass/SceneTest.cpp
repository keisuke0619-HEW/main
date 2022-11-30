#include "SceneTest.hpp"
#include <Player.hpp>
#include <PlayerCamera.hpp>
#include <DebugCamera.hpp>
#include <Input.h>
CSceneTest::CSceneTest()
{
	m_obj->Add(new CPlayer());
	CCameraBase::CreateCamera(new CDebugCamera(), "Debug");
	CCameraBase::CreateCamera(new CPlayerCamera(), "Player");
	m_stage.reset(new CStage00());
}

CSceneTest::~CSceneTest()
{
}

void CSceneTest::Update()
{
}

void CSceneTest::Draw()
{
	CSceneBase::Draw();
	m_stage->Draw();
}
