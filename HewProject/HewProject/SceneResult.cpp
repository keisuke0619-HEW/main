#include "SceneResult.hpp"
#include <SceneManager.hpp>
#include <DebugCamera.hpp>
#include <Controller.hpp>
#include <UiManager.hpp>
#include <Time.h>
#include <SE.h>

bool g_isClear = false;

CSceneResult::CSceneResult(Data data)
{
	m_selectCursol = 1;
	// ゲームのデータ取得
	m_data = data;
	// ホーム
	m_Home = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/Result/Clear/home.png"));
	m_Home.lock()->SetSize({ 377.5f, 35.f });//151.f, 14.f
	m_Home.lock()->SetPos({ 230.f, 642.f });
	m_Home.lock()->SetColor(1, 1, 1, 0.3f);
	if (g_isClear == true)
	{
		if (m_data.BackScene == SCENE_STAGE03)
		{
			// タイトル
			m_Retry = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/Result/Clear/home.png"));
			m_Retry.lock()->SetSize({ 377.5f, 35.f });//151.f, 14.f
			m_Retry.lock()->SetPos({ 1050.f, 642.f });
			m_Retry.lock()->SetColor(1, 1, 1, 1);
			m_Home.lock()->SetColor(1, 1, 1, 0);
		}
		else
		{
			// ネクスト
			m_Retry = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/Result/Clear/next.png"));
			m_Retry.lock()->SetSize({ 377.5f, 35.f });//151.f, 14.f
			m_Retry.lock()->SetPos({ 1050.f, 642.f });
			m_Retry.lock()->SetColor(1, 1, 1, 1);
		}
	}
	else
	{
		// リトライ
		m_Retry = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/Result/Clear/retry.png"));
		m_Retry.lock()->SetSize({ 377.5f, 35.f });//151.f, 14.f
		m_Retry.lock()->SetPos({ 1050.f, 642.f });
		m_Retry.lock()->SetColor(1, 1, 1, 1);
	}
	
	CSoundSE::Stop();
	// 音データの読み込み
	SetBGM("Assets/Sound/BGM/ResultBGM.mp3");
	CSoundSE::Start(CSoundSE::SE_RESULT);
	if (g_isClear)
	{
		// ゲームクリア
		m_ResultUI = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/Result/Clear/gameclear.png"));
		m_ResultUI.lock()->SetSize({ 646.f, 91.7f });//265.f, 37.f
		m_ResultUI.lock()->SetPos({ 650.f, 204.f });
		float score = (float)m_data.MAX_kill / 20.f;
		if (score <= 0.4)
			CSoundSE::Start(CSoundSE::SE_VOICE_WIN);
		if (score > 0.4 && score <= 0.6)
			CSoundSE::Start(CSoundSE::SE_VOICE_WIN_BRONZE);
		if (score > 0.6 && score <= 0.8)
			CSoundSE::Start(CSoundSE::SE_VOICE_WIN_SILVER);
		if (score > 0.8)
			CSoundSE::Start(CSoundSE::SE_VOICE_WIN_GOLD);
	}
	else
	{
		// ゲームオーバー
		m_ResultUI = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/Result/Clear/gameover.png"));
		m_ResultUI.lock()->SetSize({ 646.f, 91.7f });//265.f, 37.f
		m_ResultUI.lock()->SetPos({ 650.f, 204.f });
		CSoundSE::Start(CSoundSE::SE_VOISE_LOSE);
	}

	// 猫
	m_Cat = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/Result/Clear/cat.png"));
	m_Cat.lock()->SetSize({ 83.3f, 97.6f });//31.f, 32.f
	m_Cat.lock()->SetPos({ 1000.f, 490.f });

	float score = (float)m_data.MAX_kill / 20.f;
	if (score <= 0.4)
	{
		m_Cat.lock()->SetColor(1, 1, 1, 0);
	}
	if (score > 0.4)
	{
		// 銅
		m_Cat.lock()->SetColor255(134, 74, 43);
	}
	if (score > 0.6)
	{
		// 銀
		m_Cat.lock()->SetColor(1, 1, 1);
	}
	if (score > 0.8)
	{
		// 金
		m_Cat.lock()->SetColor255(255, 215, 0);
	}


	// 背景
	m_ResultUI = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/Result/Clear/back.png"));
	m_ResultUI.lock()->SetSize({ 1200.f, 600.f });//467.f, 276.f
	m_ResultUI.lock()->SetPos({ 640.f, 360.f });

	m_ResultUI = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/Title/title_background.png"));
	m_ResultUI.lock()->SetSize({ 1280.f, 720.f });//467.f, 276.f
	m_ResultUI.lock()->SetPos({ 640.f, 360.f });

	
	

	

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
	
	CatMove();
	if (m_data.BackScene != SCENE_STAGE03)
	{
		if (Utility::GetKeyTrigger(KEY_RIGHT))
		{
			if (m_selectCursol == 0)
				CSoundSE::Start(CSoundSE::SE_CURSOR);
			m_selectCursol = 1;
			m_Retry.lock()->SetColor(1, 1, 1, 1);
			m_Home.lock()->SetColor(1, 1, 1, 0.3f);
		}
		if (Utility::GetKeyTrigger(KEY_LEFT))
		{
			if (m_selectCursol == 1)
				CSoundSE::Start(CSoundSE::SE_CURSOR);
			m_selectCursol = 0;
			m_Retry.lock()->SetColor(1, 1, 1, 0.3f);
			m_Home.lock()->SetColor(1, 1, 1, 1);

		}
	}
	

	if (Utility::GetKeyTrigger(KEY_SELECT))
	{
		CSoundSE::Start(CSoundSE::SE_SELECT);
		if (m_selectCursol == 0)
		{
			CSceneManager::SetScene(SCENE_TITLE);
		}
		if(m_selectCursol==1)
		{
			CSoundSE::Start(CSoundSE::SE_LOAD);
			if (g_isClear == true)
			{
				switch (m_data.BackScene)
				{
				case SCENE_STAGE01:
					CSceneManager::SetScene(SCENE_STAGE02);
					break;
				case SCENE_STAGE02:
					CSceneManager::SetScene(SCENE_STAGE03);
					break;
				case SCENE_STAGE03:
					CSceneManager::SetScene(SCENE_TITLE);
					break;
				default:
					break;
				}
			}
			else
			{
				CSceneManager::SetScene(m_data.BackScene);
			}
		}
	}
	if (Utility::GetKeyTrigger(KEY_CANCEL))
	{
		CSoundSE::Start(CSoundSE::SE_CANCEL);
		CSceneManager::SetScene(SCENE_STAGE_SELECT);
	}
}

void CSceneResult::CatMove()
{
	// 軟体アニメーション
	m_Cat.lock()->SetSize(m_Cat.lock()->GetSize().x + (sinf(m_frame * 0.0625) * 0.5), (m_Cat.lock()->GetSize().y + (-sinf(m_frame * 0.0625) * 2)));
}
