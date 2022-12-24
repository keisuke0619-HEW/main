#pragma once
#include <SceneBase.hpp>
#include <GameUI.h>
#include <Sound.h>

class CSceneTitle : public CSceneBase
{
public:
	CSceneTitle();
	~CSceneTitle();

private:
	void Update() override;
	CGameUI::Ref m_TitleUI;
	XAUDIO2_BUFFER* m_pBGM;
	IXAudio2SourceVoice* m_pBGMSource;
};
