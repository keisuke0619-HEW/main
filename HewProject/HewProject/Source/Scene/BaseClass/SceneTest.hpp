#pragma once
#include <SceneBase.hpp>
//#include <Stage00.hpp>
#include <ProtStage.hpp>
#include <Sound.h>
class CSceneTest : public CSceneBase
{
public:
	CSceneTest();
	~CSceneTest();

	void Update() override;
	void Draw() override;
private:
	//std::unique_ptr<CStage00> m_stage;
	std::unique_ptr<CProtScene> m_stage;
	XAUDIO2_BUFFER* m_pBGM;
	IXAudio2SourceVoice* m_pBGMSource;
};