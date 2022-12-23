#pragma once
#include <SceneBase.hpp>
#include <GameUI.h>

class CSceneTitle : public CSceneBase
{
public:
	CSceneTitle();
	~CSceneTitle();

private:
	void Update() override;
	CGameUI::Ref m_TitleUI;
};
