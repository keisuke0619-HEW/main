#pragma once
#include <SceneBase.hpp>
#include <GameUI.h>
#include <Sound.h>


struct TResultData
{
	bool isClear;
	int score;
	int time;
};
class CSceneResult : public CSceneBase
{
public:
	CSceneResult();
	~CSceneResult();

	void SetData(void* dataPtr, long size = 0, const char* name = "NO_NAME") override;
private:
	void Update() override;
	CGameUI::Ref m_ResultUI;
	TResultData m_resultData;
};