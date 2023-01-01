#pragma once

#include <SceneBase.hpp>
#include <GameUI.h>
class CSceneStageSelect : public CSceneBase
{
public:
	CSceneStageSelect();
	~CSceneStageSelect();

private:
	void Update() override;
};