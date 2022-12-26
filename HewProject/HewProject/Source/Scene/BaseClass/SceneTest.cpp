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
	CCameraBase::CreateCamera(new CDebugCamera(), "Debug");
	CCameraBase::CreateCamera(new CPlayerCamera(), "Player");
	CCameraBase::SetPrimaryCamera("Player");
	m_stage.reset(new CProtScene());
	// 音データの読み込み
	m_pBGM = CreateSound("Assets/Sound/BGM.wav", true);
	// BGMの再生
	m_pBGMSource = StartSound(m_pBGM);
	m_pBGMSource->SetVolume(0.05f);	// 1が最大

}

CSceneTest::~CSceneTest()
{
}

void CSceneTest::Update()
{
	m_stage->Update();
	if (Utility::GetKeyTrigger(Key_RETURN))
	{
		m_pBGMSource->Stop();
		CSceneManager::SetScene(SCENE_RESULT);
	}
	if (Utility::GetKeyTrigger(Key_ESCAPE))
	{
		AddOverlay(new COverlayConfig());
	}
}

void CSceneTest::Draw()
{
	CSceneBase::Draw();
	m_stage->Draw();
}
