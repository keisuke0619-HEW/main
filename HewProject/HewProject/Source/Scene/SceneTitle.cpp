#include "SceneTitle.hpp"
#include <SceneManager.hpp>
#include <DebugCamera.hpp>
#include <Controller.hpp>
#include <UiManager.hpp>
#include <OverlayConfig.hpp>
#include <OverlayAskBase.hpp>
#include <Startup.h>
#include <SE.h>


CSceneTitle::CSceneTitle()
{
	

	// タイトルロゴ
	m_TitlerogoUI = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/Title/titlerogo.png"));
	m_TitlerogoUI.lock()->SetSize({ 702.0f, 436.0f });
	m_TitlerogoUI.lock()->SetPos({ 640.0f, 285.0f });

	//エフェクト流星
	for (int i = 0; i < 7; i++)
	{
		m_efectPosX[i] = (float)(rand() % 1880);
		m_efectPosY[i] = -350.0f - (float)(rand() % 350);
		m_EffectUI[i] = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/Title/meteor.png"), SORT_ORDER_BACK);
		m_EffectUI[i].lock()->SetSize({ 100.0f, 100.0f });
		m_EffectUI[i].lock()->SetPos({ m_efectPosX[i], m_efectPosY[i] });
	}

	m_TitleLogoEffect = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/Title/titlerogo.png"), SORT_ORDER_FRONT);
	m_TitleLogoEffect.lock()->SetSize({ 702.0f, 436.0f });
	m_TitleLogoEffect.lock()->SetPos({ 640.0f, 285.0f });
	m_TitleLogoEffect.lock()->SetColor255(255, 255, 255, 128);

	m_StartUI = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/Title/start.png"));
	m_StartUI.lock()->SetSize({ 263.0f, 47.0f });
	m_StartUI.lock()->SetPos({ 640.0f, 530.0f });

	m_EndUI = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/Title/end.png"));
	m_EndUI.lock()->SetSize({ 181.0f, 47.0f });
	m_EndUI.lock()->SetPos({ 600.0f, 620.0f });
	
	// 背景
	m_TitlebgUI = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/Title/title_background.png"),SORT_ORDER_BACK);
	m_TitlebgUI.lock()->SetSize({ 1281.0f, 720.0f });
	m_TitlebgUI.lock()->SetPos({ 640.0f, 360.0f });

	

	SetBGM("Assets/Sound/BGM/ExtendedWinter.wav");
	m_titleEffectAlpha = 128;
}

CSceneTitle::~CSceneTitle()
{
}

#include <DebugWindow.hpp>
void CSceneTitle::Update()
{
	

	

	
	if (Utility::GetKeyTrigger(KEY_SELECT))
	{
		CSoundSE::Start(CSoundSE::SE_SELECT);
		CSceneManager::SetScene(SCENE_STAGE_SELECT);
	}
	if (Utility::GetKeyTrigger(KEY_BEAM))
	{
		SetBGM("Assets/Sound/BGM/korinoyaiba.wav");
	}
	if (Utility::GetKeyTrigger(KEY_CANCEL))
	{
		CSoundSE::Start(CSoundSE::SE_CANCEL);
		AddOverlay(new COverlayAskBase("Assets/Img/PauseMenu/Label_Exit.png", GetLoopPointer() ));

		
	}
	if (m_frame % 180 == 0)
	{
		m_TitleLogoEffect.lock()->SetSize({ 702.0f, 436.0f });
		m_TitleLogoEffect.lock()->SetColor255(255, 255, 255, 255);
		m_titleEffectAlpha = 128.0f;
	}
	else
	{
		m_TitleLogoEffect.lock()->SetSize({ 702.0f + m_frame % 180 * 3, 436.0f + m_frame % 180 * 3 });
		m_TitleLogoEffect.lock()->SetColor255(255, 255, 255, m_titleEffectAlpha);
		m_titleEffectAlpha -= 5;
	}
	
	for (int i = 0; i < 7; i++)
	{
		m_efectPosX[i] -= 17.0f;
		m_efectPosY[i] += 17.0f;
		m_EffectUI[i].lock()->SetPos({ m_efectPosX[i],m_efectPosY[i] });

		if (m_EffectUI[i].lock()->GetPos().x <= -350.0f || m_EffectUI[i].lock()->GetPos().y <= -1420.0f)
		{
			m_efectPosX[i] = (float)(rand() % 1880);
			m_efectPosY[i] = -350.0f - (float)(rand() % 350);
			m_EffectUI[i].lock()->SetPos({ m_efectPosX[i],m_efectPosY[i] });//ここで位置調整して
		}
	}
//流星群関係	
}


