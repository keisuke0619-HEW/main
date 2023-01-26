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
	CSceneResult(Data data);
	~CSceneResult();
	static void SetClear();
	static void SetOver();

	void SetData(void* dataPtr, long size = 0, const char* name = "NO_NAME") override;
private:
	void Update() override;
	int m_selectCursol=0;//セレクトの選択
	CGameUI::Ref m_ResultUI;	
	CGameUI::Ref m_Home;
	CGameUI::Ref m_Retry;
	TResultData m_resultData;
	CNumberUI::Ptr m_time;
	CNumberUI::Ptr m_maxDefeat;
	XAUDIO2_BUFFER* m_pselectSE;
	XAUDIO2_BUFFER* m_pcursorSE;
	IXAudio2SourceVoice* m_pSESource;

};