#include "GameScene_04.hpp"
#include <SceneManager.hpp>
#include <Player.hpp>
#include <PlayerCamera.hpp>
#include <DebugCamera.hpp>
#include <Input.h>
#include <EnemyZako01.hpp>
#include <Controller.hpp>
#include <OverlayConfig.hpp>
CGameScene_04::CGameScene_04()
{
	m_obj->Add(new CPlayer());
	CCameraBase::CreateCamera(new CPlayerCamera(), "Player");
	CCameraBase::SetPrimaryCamera("Player");

	SetBGM("Assets/Sound/BGM.wav");

}

CGameScene_04::~CGameScene_04()
{
}

void CGameScene_04::Update()
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

void CGameScene_04::Draw()
{
	CSceneBase::Draw();
	m_stage->Draw();
}

void CGameScene_04::SetData(void* dataPtr, long size, const char* name)
{
	m_stage.reset((CStageData01*)dataPtr);
}