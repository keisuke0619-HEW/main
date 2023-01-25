#include "SceneResult.hpp"
#include <SceneManager.hpp>
#include <DebugCamera.hpp>
#include <Controller.hpp>
#include <UiManager.hpp>
#include <Time.h>

bool g_isClear = false;

CSceneResult::CSceneResult(Data data)
{
	// ゲームのデータ取得
	m_data = data;
	// ホーム
	m_Home = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/Result/Clear/home.png"));
	m_Home.lock()->SetSize({ 377.5f, 35.f });//151.f, 14.f
	m_Home.lock()->SetPos({ 230.f, 642.f });
	m_Home.lock()->SetColor(1, 1, 1, 1);
	// ネクスト
	m_Retry = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/Result/Clear/retry.png"));
	m_Retry.lock()->SetSize({ 377.5f, 35.f });//151.f, 14.f
	m_Retry.lock()->SetPos({ 1050.f, 642.f });
	m_Retry.lock()->SetColor(1, 1, 1, 0.3f);
	if (g_isClear)
	{
		// ゲームクリア
		m_ResultUI = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/Result/Clear/gameclear.png"));
		m_ResultUI.lock()->SetSize({ 646.f, 91.7f });//265.f, 37.f
		m_ResultUI.lock()->SetPos({ 650.f, 204.f });
	}
	else
	{
		// ゲームオーバー
		m_ResultUI = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/Result/Clear/gameover.png"));
		m_ResultUI.lock()->SetSize({ 646.f, 91.7f });//265.f, 37.f
		m_ResultUI.lock()->SetPos({ 650.f, 204.f });
	}
	
	// 背景
	m_ResultUI = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/Result/Clear/back.png"));
	m_ResultUI.lock()->SetSize({ 1200.f, 600.f });//467.f, 276.f
	m_ResultUI.lock()->SetPos({ 640.f, 360.f });
	// 猫
	m_ResultUI = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/Result/Clear/cat.png"));
	m_ResultUI.lock()->SetSize({ 83.3f, 97.6f });//31.f, 32.f
	m_ResultUI.lock()->SetPos({ 1000.f, 490.f });

	
	

	// 音データの読み込み
	SetBGM("Assets/Sound/korinoyaiba.wav");

	// 数字
	m_time.reset(new CNumberUI(2, SORT_ORDER_UI_FRONT4, 2));
	m_time->SetSize(36, 45);
	m_time->SetColor(1, 1, 1, 1);
	m_time->SetNum(CTime::GetTime());
	m_time->SetPos({ 980,305 });

	m_maxDefeat.reset(new CNumberUI(2, SORT_ORDER_UI_FRONT4, 0));
	m_maxDefeat->SetSize(108, 135);
	m_maxDefeat->SetColor(1, 1, 1, 1);
	m_maxDefeat->SetIsZeroFill(true);
	m_maxDefeat->SetNum(m_data.MAX_kill); // ここに最大撃破数を入れる
	m_maxDefeat->SetPos({ 840,490 });
	float score = (float)m_data.MAX_kill / 20.f;
	if (score <= 0.4)
	{
		m_ResultUI.lock()->SetColor(1, 1, 1, 0);
	}
	if (score > 0.4)
	{
		// 銅
		m_ResultUI.lock()->SetColor255(134, 74, 43);
	}
	if (score > 0.6)
	{
		// 銀
		m_ResultUI.lock()->SetColor(1, 1, 1);
	}
	if (score > 0.8)
	{
		// 金
		m_ResultUI.lock()->SetColor255(255, 215, 0);
	}
	
}

CSceneResult::~CSceneResult()
{
}

void CSceneResult::SetClear()
{
	g_isClear = true;
}

void CSceneResult::SetOver()
{
	g_isClear = false;
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
	

	if (Utility::GetKeyTrigger(KEY_RIGHT))
	{
		m_selectCursol = 1;
		m_Retry.lock()->SetColor(1, 1, 1, 1);
		m_Home.lock()->SetColor(1, 1, 1, 0.3f);
	}
	if (Utility::GetKeyTrigger(KEY_LEFT))
	{
		m_selectCursol = 0;
		m_Retry.lock()->SetColor(1, 1, 1, 0.3f);
		m_Home.lock()->SetColor(1, 1, 1, 1);
		
	}

	if (Utility::GetKeyTrigger(KEY_SELECT))
	{

		if (m_selectCursol == 0)
		{
			CSceneManager::SetScene(SCENE_TITLE);
		}
		if(m_selectCursol==1)
		{
			CSceneManager::SetScene(SCENE_STAGE01);
		}
	}
}
