#include "SceneResult.hpp"
#include <SceneManager.hpp>
#include <DebugCamera.hpp>
#include <Controller.hpp>
#include <UiManager.hpp>
CSceneResult::CSceneResult()
{
	// ホーム
	m_ResultUI = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/Result/Clear/home.png"));
	m_ResultUI.lock()->SetSize({ 377.5f, 35.f });//151.f, 14.f
	m_ResultUI.lock()->SetPos({ 230.f, 642.f });
	// ネクスト
	m_ResultUI = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/Result/Clear/retry.png"));
	m_ResultUI.lock()->SetSize({ 377.5f, 35.f });//151.f, 14.f
	m_ResultUI.lock()->SetPos({ 1050.f, 642.f });
	// ゲームクリア
	m_ResultUI = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/Result/Clear/gameclear.png"));
	m_ResultUI.lock()->SetSize({ 646.f, 91.7f });//265.f, 37.f
	m_ResultUI.lock()->SetPos({ 650.f, 204.f });
	// 猫
	m_ResultUI = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/Result/Clear/cat.png"));
	m_ResultUI.lock()->SetSize({ 133.3f, 137.6f });//31.f, 32.f
	m_ResultUI.lock()->SetPos({ 365.f, 194.f });
	// 背景
	m_ResultUI = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/Result/Clear/back.png"));
	m_ResultUI.lock()->SetSize({ 1200.f, 600.f });//467.f, 276.f
	m_ResultUI.lock()->SetPos({ 640.f, 360.f });
	// 音データの読み込み
	SetBGM("Assets/Sound/korinoyaiba.wav");
	
}

CSceneResult::~CSceneResult()
{
}

void CSceneResult::SetData(void* dataPtr, long size, const char* name)
{
	if (size == sizeof(TResultData))
	{
		m_resultData = (TResultData)*((TResultData*)dataPtr);
	}
}

void CSceneResult::Update()
{
	if (Utility::GetKeyTrigger(KEY_SELECT))
	{
		CSceneManager::SetScene(SCENE_STAGE_SELECT);
	}
}
