#include "SE.h"

XAUDIO2_BUFFER* CSoundSE::m_pSE[CSoundSE::SE_MAX];
IXAudio2SourceVoice* CSoundSE::m_pSESource;


bool CSoundSE::m_IsPlay;
int CSoundSE::m_cnt;
int CSoundSE::m_SoundNum;

CSoundSE::CSoundSE()
{
}

CSoundSE::~CSoundSE()
{
}

void CSoundSE::Init()
{
	m_IsPlay = false;
	m_cnt = 0;
	m_SoundNum = 0;
	m_pSE[SE_SELECT]			= CreateSound("Assets/Sound/SE/Select.mp3", false);
	m_pSE[SE_CURSOR]			= CreateSound("Assets/Sound/SE/Cursor.mp3", false);
	m_pSE[SE_CANCEL]			= CreateSound("Assets/Sound/SE/cancel.mp3", false);
	m_pSE[SE_BAR]				= CreateSound("Assets/Sound/SE/Bar.mp3", false);
	m_pSE[SE_KEMO]				= CreateSound("Assets/Sound/SE/thankyou.wav", false);
	m_pSE[SE_BOMB]				= CreateSound("Assets/Sound/SE/bomb.mp3", false);
	m_pSE[SE_EXPLOTION]			= CreateSound("Assets/Sound/SE/explotion.mp3", false);
	m_pSE[SE_RAIL]				= CreateSound("Assets/Sound/SE/rail.mp3", false);
	m_pSE[SE_MENU]				= CreateSound("Assets/Sound/SE/Menu.mp3", false);
	m_pSE[SE_LOAD]				= CreateSound("Assets/Sound/SE/Load.mp3", false);
	m_pSE[SE_WARNING]			= CreateSound("Assets/Sound/SE/Warning.mp3", true);
	m_pSE[SE_RESULT]			= CreateSound("Assets/Sound/SE/Result.mp3", false);
	m_pSE[SE_BACK]				= CreateSound("Assets/Sound/SE/Back.mp3", false);
	m_pSE[SE_P]					= CreateSound("Assets/Sound/SE/P.mp3", false);
	m_pSE[SE_VOICE_CHECK]		= CreateSound("Assets/Sound/SE/CheckVoice.wav", false);
	m_pSE[SE_VOICE_END]			= CreateSound("Assets/Sound/SE/EndVoice.wav", false);
	m_pSE[SE_VOICE_LOAD]		= CreateSound("Assets/Sound/SE/LoadVoice.wav", false);
	m_pSE[SE_VOISE_LOSE]		= CreateSound("Assets/Sound/SE/LoseVoice.wav", false);
	m_pSE[SE_VOICE_WIN]			= CreateSound("Assets/Sound/SE/WinNormalVoice.wav", false);
	m_pSE[SE_VOICE_WIN_BRONZE]	= CreateSound("Assets/Sound/SE/WinBronzeVoice.wav", false);
	m_pSE[SE_VOICE_WIN_SILVER]	= CreateSound("Assets/Sound/SE/WinSilverVoice.wav", false);
	m_pSE[SE_VOICE_WIN_GOLD]	= CreateSound("Assets/Sound/SE/WinGoldVoice.wav", false);
	m_pSE[SE_VOICE_FIGHT_WIN]	= CreateSound("Assets/Sound/SE/FightWinVoice.wav", false);
	m_pSE[SE_VOICE_FIGHT_LOSE]	= CreateSound("Assets/Sound/SE/FightLoseVoice.wav", false);
}

void CSoundSE::Start(SESource Source)
{
	if (m_SoundNum > 2)
	{
		Stop();
		m_SoundNum = 0;
	}
	
	m_pSESource = StartSound(m_pSE[Source]);
	m_SoundNum++;
	
	
	
}

void CSoundSE::Stop()
{
	if(m_pSESource != nullptr)
	m_pSESource->Stop();
}

void CSoundSE::ReStart()
{
	if (m_pSESource != nullptr)
		m_pSESource->Start();
}

void CSoundSE::SetVolume(float volume)
{
	if (m_pSESource != nullptr)
		m_pSESource->SetVolume(volume);
}

void CSoundSE::BoolPlay()
{
	m_IsPlay = true;
}

void CSoundSE::BoolStop()
{
	m_IsPlay = false;
}

bool CSoundSE::IsPlay()
{
	return m_IsPlay;
}

void CSoundSE::CountUp()
{
	m_cnt++;
}

int CSoundSE::GetCount()
{
	return m_cnt;
}

void CSoundSE::CountReset()
{
	m_cnt = 0;
}

void CSoundSE::ExitLoop()
{
	m_pSESource->ExitLoop();
}

