#pragma once
#include <SceneBase.hpp>
#include <GameUI.h>
#include <Sound.h>

class CSceneResult : public CSceneBase
{
public:
	CSceneResult();
	~CSceneResult();

private:
	void Update() override;
	CGameUI::Ref m_ResultUI;
};