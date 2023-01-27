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
	m_pSE[SE_SELECT] = CreateSound("Assets/Sound/select.mp3", false);
	m_pSE[SE_CURSOR] = CreateSound("Assets/Sound/cursor.mp3", false);
	m_pSE[SE_CANCEL] = CreateSound("Assets/Sound/cancel.mp3", false);
	m_pSE[SE_BAR] = CreateSound("Assets/Sound/bar.mp3", false);
	m_pSE[SE_KEMO] = CreateSound("Assets/Sound/thankyou.wav", false);
	m_pSE[SE_BOMB] = CreateSound("Assets/Sound/explotion.mp3", false);
	m_pSE[SE_EXPLOTION] = CreateSound("Assets/Sound/bomb.mp3", false);
	m_pSE[SE_RAIL] = CreateSound("Assets/Sound/rail.mp3", false);
}

void CSoundSE::Start(SESource Source)
{
	//Stop();
	switch (Source)
	{
	case CSoundSE::SE_SELECT:
		m_pSESource = StartSound(m_pSE[SE_SELECT]);
		break;
	case CSoundSE::SE_CURSOR:
		m_pSESource = StartSound(m_pSE[SE_CURSOR]);
		break;
	case CSoundSE::SE_CANCEL:
		m_pSESource = StartSound(m_pSE[SE_CANCEL]);
		break;
	case CSoundSE::SE_BAR:
		m_pSESource = StartSound(m_pSE[SE_BAR]);
		break;
	case CSoundSE::SE_KEMO:
		m_pSESource = StartSound(m_pSE[SE_KEMO]);
		break;
	case CSoundSE::SE_BOMB:
		m_pSESource = StartSound(m_pSE[SE_BOMB]);
		break;
	case CSoundSE::SE_EXPLOTION:
		m_pSESource = StartSound(m_pSE[SE_EXPLOTION]);
		break;
	case CSoundSE::SE_RAIL:
		m_pSESource = StartSound(m_pSE[SE_RAIL]);
		break;
	default:
		break;
	}
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

