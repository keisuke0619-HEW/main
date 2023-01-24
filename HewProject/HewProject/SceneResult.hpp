#pragma once
#include <SceneBase.hpp>
#include <GameUI.h>
#include <Sound.h>
#include <NumberUI.hpp>

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
	static void SetClear();

	void SetData(void* dataPtr, long size = 0, const char* name = "NO_NAME") override;
private:
	void Update() override;
	CGameUI::Ref m_ResultUI;
	TResultData m_resultData;
	CNumberUI::Ptr m_time;
	CNumberUI::Ptr m_maxDefeat;
};