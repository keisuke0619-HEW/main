#include "OverlayStagePrep.hpp"
#include <Controller.hpp>
#include <SceneManager.hpp>

COverlayStagePrep::COverlayStagePrep(int id)
{
	m_next = nullptr;
	m_ui[PREP_FADE] = new CGameUI("Assets/Img/White.png");
	m_ui[PREP_FADE]->SetData(640, 360, 1280, 720);
	m_ui[PREP_FADE]->SetColor255(0, 0, 0, 128);
	Add("Fade", m_ui[PREP_FADE], SORT_ORDER_UI_BACKEND);
	m_ui[PREP_BACK] = new CGameUI("Assets/Img/stagePreparationTab/test_Tab.png");
	m_ui[PREP_BACK]->SetData(640, 360, 700, 700);
	Add("Back", m_ui[PREP_BACK], SORT_ORDER_UI_BACK4);




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
	if (Utility::GetKeyTrigger(KEY_SELECT))
	{
		// CSceneManager::SetScene(SCENE_STAGE01);
		if (m_next != nullptr)
			*m_next = true;
		m_isDestroy = true;
		return;
	}
	else if (Utility::GetKeyTrigger(KEY_CANCEL))
	{
		m_isDestroy = true;
	}

}
