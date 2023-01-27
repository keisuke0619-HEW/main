#pragma once
#include <Sound.h>

class CSoundSE
{
public:
	enum SESource
	{
		SE_SELECT,
		SE_CURSOR,
		SE_CANCEL,
		SE_BAR,
		SE_KEMO,
		SE_BOMB,
		SE_MAX,
	};
	CSoundSE();
	~CSoundSE();
	static void Init();
	static void Start(SESource);
	static void Stop();
	static void ReStart();
	static void SetVolume(float);
	static void BoolPlay();
	static void BoolStop();
	static bool IsPlay();
	

private:
	static XAUDIO2_BUFFER* m_pSE[SE_MAX];
	static IXAudio2SourceVoice* m_pSESource;

	static bool m_IsPlay;
};



