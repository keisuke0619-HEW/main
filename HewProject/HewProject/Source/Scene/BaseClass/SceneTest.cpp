#include "SceneTest.hpp"
#include <SceneManager.hpp>
#include <Player.hpp>
#include <PlayerCamera.hpp>
#include <DebugCamera.hpp>
#include <Input.h>
#include <ProtEnemy.hpp>
#include<Controller.hpp>
#include <OverlayConfig.hpp>
CSceneTest::CSceneTest()
{
	m_obj->Add(new CPlayer());
	CCameraBase::CreateCamera(new CPlayerCamera(), "Player");
	CCameraBase::SetPrimaryCamera("Player");
	m_stage.reset(new CProtScene());

	BGMSet("Assets/Sound/BGM.wav");

}

CSceneTest::~CSceneTest()
{
}

void CSceneTest::Update()
{
	m_stage->Update();
	if (Utility::GetKeyTrigger(KEY_DEBUG_RETURN))
	{
		CSceneManager::SetScene(SCENE_RESULT);
	}
	if (Utility::GetKeyTrigger(KEY_CONFIG))
	{
		AddOverlay(new COverlayConfig());
	}
}

void CSceneTest::Draw()
{
	CSceneBase::Draw();
	m_stage->Draw();
}
