#pragma once
#include <SceneBase.hpp>
#include <GameUI.h>
#include <Sound.h>
#include <BGM.h>

class CSceneTitle : public CSceneBase
{
public:
	CSceneTitle();
	~CSceneTitle();

private:
	void Update() override;
	CGameUI::Ref m_TitlebgUI;
	CGameUI::Ref m_TitlerogoUI;
	CGameUI::Ref m_TitleLogoEffect;
	CGameUI::Ref m_StartUI;
	CGameUI::Ref m_EndUI;
	float m_titleEffectAlpha;
};
