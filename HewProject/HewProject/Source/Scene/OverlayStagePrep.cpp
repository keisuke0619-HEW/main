#include "OverlayStagePrep.hpp"
#include <Controller.hpp>
#include <SceneManager.hpp>
#include <OverlayConfig.hpp>
#include <SE.h>
COverlayStagePrep::COverlayStagePrep(int id)
{
	m_next = nullptr;
	m_ui[PREP_FADE] = new CGameUI("Assets/Img/White.png");
	m_ui[PREP_FADE]->SetData(640, 360, 1280, 720);
	m_ui[PREP_FADE]->SetColor255(0, 0, 0, 128);
	Add("Fade", m_ui[PREP_FADE], SORT_ORDER_UI_BACKEND);
	m_ui[PREP_BACK] = new CGameUI("Assets/Img/stagePreparationTab/IRAInasi.png");
	m_ui[PREP_BACK]->SetData(640, 360, 1280 * 0.8f, 720 * 0.8f);
	Add("Back", m_ui[PREP_BACK], SORT_ORDER_UI_BACK4);
	m_ui[PREP_WARNING_FADE] = new CGameUI("Assets/Img/White.png");
	m_ui[PREP_WARNING_FADE]->SetData(640, 360, 1280, 720);
	m_ui[PREP_WARNING_FADE]->SetColor255(255, 0, 0, 128);
	Add("WarningFade", m_ui[PREP_WARNING_FADE], SORT_ORDER_UI_FRONT);
	m_ui[PREP_WARNING_ICON] = new CGameUI("Assets/Img/stagePreparationTab/warning.png");
	m_ui[PREP_WARNING_ICON]->SetData(640, 535, 1020, 160);
	Add("WarningIcon", m_ui[PREP_WARNING_ICON], SORT_ORDER_UI_BACK3);

	switch (id)
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	default:
		MessageBox(NULL, "渡された値が不正です。", "COverlayStagePreparationコンストラクタ", MB_OK);
		break;
	}
	CSoundSE::Start(CSoundSE::SE_WARNING);
}

COverlayStagePrep::~COverlayStagePrep()
{
	
}

void COverlayStagePrep::SetIsNext(bool* next)
{
	m_next = next;
}

void COverlayStagePrep::Update()
{
	m_ui[PREP_WARNING_FADE]->SetColor255(255, 0, 0, fabs((sinf(m_frame * 0.05) * 128)));
	m_ui[PREP_WARNING_ICON]->SetColor255(255, 255, 255, fabs((sinf(m_frame * 0.05) * 255)));
	if (Utility::GetKeyTrigger(KEY_SELECT))
	{
		CSoundSE::Stop();
		CSoundSE::Start(CSoundSE::SE_LOAD);
		CSoundSE::Start(CSoundSE::SE_VOICE_LOAD);
		CSceneManager::SetScene(SCENE_STAGE01);

		//if (m_next != nullptr)
		//	*m_next = true;
		m_isDestroy = true;
		return;
	}
	else if (Utility::GetKeyTrigger(KEY_CANCEL))
	{
		CSoundSE::Stop();
		CSoundSE::Start(CSoundSE::SE_CANCEL);
		m_isDestroy = true;
	}
	/*else if (Utility::GetKeyTrigger(KEY_CONFIG))
	{
		CSoundSE::Start(CSoundSE::SE_SELECT);
		m_overlay.reset(new COverlayConfig());
	}*/

}
