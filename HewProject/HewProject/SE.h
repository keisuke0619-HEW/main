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
		SE_EXPLOTION,
		SE_BOMB,
		SE_RAIL,
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
	static void CountUp();
	static int GetCount();
	static void CountReset();
	static void ExitLoop();
	

private:
	static XAUDIO2_BUFFER* m_pSE[SE_MAX];
	static IXAudio2SourceVoice* m_pSESource;

	static bool m_IsPlay;
	static int m_cnt;
};



