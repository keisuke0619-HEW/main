#pragma once
#include <Sound.h>

class CSound
{
public:
	CSound();
	~CSound();
	void Update();
	void BGMSet(const char* src, float volume = 1.0f);
	void SetVolumeFade(float newVolume, int flame);
	void BGMStop();
	void BGMRestart();

private:
	int m_frame;
	int m_fadeFlame;
	float m_newVolume;
	float m_fadeVolume;
	bool m_isFade;
	IXAudio2SourceVoice* m_BGM;
	XAUDIO2_BUFFER* m_bgmBuffer;
};


