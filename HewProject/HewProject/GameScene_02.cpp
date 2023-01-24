#include "GameScene_02.hpp"
#include <SceneManager.hpp>
#include <Player.hpp>
#include <PlayerCamera.hpp>
#include <DebugCamera.hpp>
#include <Input.h>
#include <EnemyZako01.hpp>
#include <Controller.hpp>
#include <OverlayConfig.hpp>
CGameScene_02::CGameScene_02()
{
	m_obj->Add(new CPlayer(&m_data));
	CCameraBase::CreateCamera(new CPlayerCamera(), "Player");
	CCameraBase::SetPrimaryCamera("Player");

	SetBGM("Assets/Sound/BGM.wav");

}

CGameScene_02::~CGameScene_02()
{
}

void CGameScene_02::Update()
{
	m_stage->Update();
	if (Utility::GetKeyTrigger(KEY_DEBUG_RETURN))
	{
		CSceneManager::SetScene(SCENE_STAGE03);
	}
	if (Utility::GetKeyTrigger(KEY_CONFIG))
	{
		AddOverlay(new COverlayConfig());
	}
}

void CGameScene_02::Draw()
{
	CSceneBase::Draw();
	m_stage->Draw();
}

void CGameScene_02::SetData(void* dataPtr, long size, const char* name)
{
	m_stage.reset((CStageData01*)dataPtr);
}