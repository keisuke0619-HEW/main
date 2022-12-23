#pragma once
#include <SceneBase.hpp>
#include <GameUI.h>

class CSceneResult : public CSceneBase
{
public:
	CSceneResult();
	~CSceneResult();

private:
	void Update() override;
	CGameUI::Ref m_ResultUI;
};