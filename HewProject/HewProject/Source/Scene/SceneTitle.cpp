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
	

	// �^�C�g�����S
	m_TitlerogoUI = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/Title/titlerogo.png"));
	m_TitlerogoUI.lock()->SetSize({ 702.0f, 436.0f });
	m_TitlerogoUI.lock()->SetPos({ 640.0f, 285.0f });

	//�G�t�F�N�g����
	m_EffectUI = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/Title/meteor.png"),SORT_ORDER_BACK);
	m_EffectUI.lock()->SetSize({ 702.0f, 436.0f });
	m_EffectUI.lock()->SetPos({ 840.0f, 0.0f });

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
	
	// �w�i
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
	m_efect++;



	
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
	
	m_EffectUI.lock()->SetPos({ 840.0f-m_efect*14.f, 0.0f+ m_efect *14.f });

	if (m_efect%180==0/*m_EffectUI.lock()->GetPos().x >= -555.0f&& m_EffectUI.lock()->GetPos().y>= 444.0f*/)
	{
		m_EffectUI.lock()->SetPos({ 840.0f, 0.0f });//�����ňʒu��������
		m_efect = 0;
	}
//�����Q�֌W	
}


