#pragma once
#include <SceneBase.hpp>
#include <GameUI.h>
#include <Sound.h>
#include <BGM.h>
#include <CometSS.hpp>
class CSceneTitle : public CSceneBase
{
public:
	CSceneTitle();
	~CSceneTitle();

private:
	
	float m_efectPosX[7];
	float m_efectPosY[7];

	void Update() override;
	void Draw() override;
	CGameUI::Ref m_TitlebgUI;
	CGameUI::Ref m_TitlerogoUI;
	CGameUI::Ref m_TitleLogoEffect;
	CGameUI::Ref m_StartUI;
	CGameUI::Ref m_EndUI;
	CGameUI::Ref m_EffectUI[7];
	CCometSS* m_cometSS;

	float m_titleEffectAlpha;
};
