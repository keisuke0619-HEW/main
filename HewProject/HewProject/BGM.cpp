#include "BGM.h"
#include <DebugWindow.hpp>

CSound::Ptr CSound::m_ins;
const int CROSS_FADE_FRAME = 30;

CSound::CSound()
	: m_BGM(nullptr)
	, m_bgmBuffer(nullptr)
	, m_frame(0)
	, m_newVolume(0)
	, m_fadeFlame(0)
	, m_fadeVolume(0)
	, m_isFade(false)
{

}

CSound::~CSound()
{
	BGMStop();
}

void CSound::Update()
{
	if (m_BGM == nullptr)
		return;
	if (m_isFade)
	{
		float nowVolume;
		m_BGM->GetVolume(&nowVolume);
		nowVolume += m_fadeVolume;

		if (nowVolume > 1.f)
			nowVolume = 1.f;
		if (nowVolume < 0.f)
			nowVolume = 0.f;

		m_BGM->SetVolume(nowVolume);

		if ((m_fadeVolume <= 0.f && nowVolume <= m_newVolume) ||
			(m_fadeVolume >= 0.f && nowVolume >= m_newVolume))
		{
			m_BGM->SetVolume(m_newVolume);
			m_isFade = false;
			if (m_isResetBGM == RESET_FADE_DOING)
			{
				m_BGM = nullptr;
				BGMSet(m_resetNewSrc, 0);
				SetVolumeFade(m_resetVolume, CROSS_FADE_FRAME / 2);
				m_isResetBGM = RESET_FADE_DONE;
			}
			else if (m_isResetBGM == RESET_FADE_DONE)
			{
				m_isResetBGM = RESET_FADE_NONE;
			}
		}
		m_frame = 0;
	}
	m_frame++;
}

void CSound::BGMSet(const char * src, float volume)
{
	// もしすでにBGMがあるならフェード処理を入れる
	if (m_BGM != nullptr)
	{
		m_resetNewSrc = src;
		m_resetVolume = volume;
		m_isResetBGM = RESET_FADE_DOING;
		SetVolumeFade(0, CROSS_FADE_FRAME / 2);
		return;
	}

	m_bgmBuffer = CreateSound(src, true);
	m_BGM = StartSound(m_bgmBuffer);
	m_BGM->SetVolume(volume);

}

void CSound::SetVolumeFade(float newVolume, int flame)
{
	if (m_BGM == nullptr)
		return;
	m_newVolume = newVolume;
	m_fadeFlame = flame;
	float nowVolume;
	m_BGM->GetVolume(&nowVolume);

	m_fadeVolume = (newVolume - nowVolume) / m_fadeFlame;
	m_isFade = true;
}

void CSound::BGMStop()
{
	if (m_BGM != nullptr && GetIsUsefulSound())
	{
		m_BGM->Stop();
	}
}

void CSound::BGMRestart()
{
	if(m_BGM != nullptr)
		m_BGM->Start();
}

void CSound::BGMEnd()
{
	if (m_BGM == nullptr)
		return;
	m_BGM->Stop();
	m_BGM = nullptr;
}
