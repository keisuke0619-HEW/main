#include "GameScene.hpp"
#include <SceneManager.hpp>
#include <Player.hpp>
#include <PlayerCamera.hpp>
#include <DebugCamera.hpp>
#include <Input.h>
#include <EnemyZako01.hpp>
#include <Controller.hpp>
#include <OverlayConfig.hpp>
CGameScene::CGameScene()
{
	m_obj->Add(new CPlayer());
	CCameraBase::CreateCamera(new CPlayerCamera(), "Player");
	CCameraBase::SetPrimaryCamera("Player");

	SetBGM("Assets/Sound/BGM.wav");

}

CGameScene::~CGameScene()
{
}

void CGameScene::Update()
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
	if (Utility::GetKeyTrigger(KEY_CANCEL))
	{
		AddOverlay(new CGameEnd());
	}
}

void CGameScene::Draw()
{
	CSceneBase::Draw();
	m_stage->Draw();
}

void CGameScene::SetData(void* dataPtr, long size, const char* name)
{
	m_stage.reset((CStageData01*)dataPtr);
}