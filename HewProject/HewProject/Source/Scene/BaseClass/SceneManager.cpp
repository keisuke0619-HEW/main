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
bool CSceneManager::m_isSwap;
ESceneID CSceneManager::m_next;

void CSceneManager::SetScene(ESceneID ID)
{
	m_isSwap = true;
	m_next = ID;
}

void CSceneManager::Update()
{
	m_scene->BaseUpdate();
}

void CSceneManager::Draw()
{
	m_scene->BaseDraw();
}

void CSceneManager::SwapScene()
{
	if (m_isSwap == false)
		return;
	CBillboard::ClearBillboard();
	CCameraBase::DeleteCameraAll();
	if (m_scene)
		m_scene->Uninit();
	switch (m_next)
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
	m_isSwap = false;
}
