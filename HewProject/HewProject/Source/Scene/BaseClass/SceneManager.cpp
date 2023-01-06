#include "SceneManager.hpp"
#include <Camera.hpp>
#include <Billboard.h>
// シーン
#include <GameScene.hpp>
#include <GameScene_02.hpp>
#include <GameScene_03.hpp>
#include <GameScene_04.hpp>
#include <SceneStageSelect.hpp>
#include <SceneTitle.hpp>
#include <SceneResult.hpp>

// ステージ情報
#include <StageData01.hpp>
std::unique_ptr<IScene> CSceneManager::m_scene;

void CSceneManager::SetScene(ESceneID ID)
{
	CBillboard::ClearBillboard();
	CCameraBase::DeleteCameraAll();
	if(m_scene)
		m_scene->Uninit();
	switch (ID)
	{
	case SCENE_TITLE:
		m_scene.reset(new CSceneTitle());
		break;
	case SCENE_STAGE_SELECT:
		m_scene.reset(new CSceneStageSelect());
		break;
	case SCENE_STAGE01:
		m_scene.reset(new CGameScene());
		m_scene->SetData(new CStageData01());
		break;
	case SCENE_STAGE02:
		m_scene.reset(new CGameScene_02());
		m_scene->SetData(new CStageData01());
		break;
	case SCENE_STAGE03:
		m_scene.reset(new CGameScene_03());
		m_scene->SetData(new CStageData01());
		break;
	case SCENE_STAGE04:
		m_scene.reset(new CGameScene_04());
		m_scene->SetData(new CStageData01());
		break;
	case SCENE_RESULT:
		m_scene.reset(new CSceneResult());
		break;
	default:
		break;
	}
}

void CSceneManager::Update()
{
	m_scene->BaseUpdate();
}

void CSceneManager::Draw()
{
	m_scene->BaseDraw();
}
