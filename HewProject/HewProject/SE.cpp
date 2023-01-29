#include "SE.h"

XAUDIO2_BUFFER* CSoundSE::m_pSE[CSoundSE::SE_MAX];
IXAudio2SourceVoice* CSoundSE::m_pSESource;


bool CSoundSE::m_IsPlay;
int CSoundSE::m_cnt;

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
	m_pSE[SE_SELECT] = CreateSound("Assets/Sound/SE/Select.mp3", false);
	m_pSE[SE_CURSOR] = CreateSound("Assets/Sound/SE/Cursor.mp3", false);
	m_pSE[SE_CANCEL] = CreateSound("Assets/Sound/SE/cancel.mp3", false);
	m_pSE[SE_BAR] = CreateSound("Assets/Sound/SE/rail.mp3", false);
	m_pSE[SE_KEMO] = CreateSound("Assets/Sound/SE/thankyou.wav", false);
	m_pSE[SE_BOMB] = CreateSound("Assets/Sound/SE/bomb.mp3", false);
	m_pSE[SE_EXPLOTION] = CreateSound("Assets/Sound/SE/explotion.mp3", false);
	m_pSE[SE_RAIL] = CreateSound("Assets/Sound/SE/rail.mp3", false);
	m_pSE[SE_MENU] = CreateSound("Assets/Sound/SE/Menu.mp3", false);
	m_pSE[SE_LOAD] = CreateSound("Assets/Sound/SE/Load.mp3", false);
	m_pSE[SE_WARNING] = CreateSound("Assets/Sound/SE/Warning.mp3", true);
	m_pSE[SE_RESULT] = CreateSound("Assets/Sound/SE/Result.mp3", false);
	m_pSE[SE_BACK] = CreateSound("Assets/Sound/SE/Back.mp3", false);
}

void CSoundSE::Start(SESource Source)
{
	//Stop();
	m_pSESource = StartSound(m_pSE[Source]);
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

