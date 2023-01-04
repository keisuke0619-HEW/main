#pragma once
#include <Sound.h>
#include <memory>
class CSound
{
	// シングルトン機構
public:
	using Ptr = std::shared_ptr<CSound>;
	static Ptr GetIns() { if (m_ins)return m_ins; m_ins.reset(new CSound()); return m_ins; };
private:
	static Ptr m_ins;


public:
	~CSound();
	void Update();
	void BGMSet(const char* src, float volume = 1.0f);
	void SetVolumeFade(float newVolume, int flame);
	void BGMStop();
	void BGMRestart();

private:
	CSound();
	int m_frame;
	int m_fadeFlame;
	float m_newVolume;
	float m_fadeVolume;
	bool m_isFade;
	IXAudio2SourceVoice* m_BGM;
	XAUDIO2_BUFFER* m_bgmBuffer;
};


