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
	XAUDIO2_BUFFER* m_pBGM;
	IXAudio2SourceVoice* m_pBGMSource;
};