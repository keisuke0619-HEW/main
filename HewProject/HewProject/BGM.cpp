#include "BGM.h"
#include <DebugWindow.hpp>

CSound::Ptr CSound::m_ins;

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
	if (m_isFade)
	{
		float nowVolume;
		m_BGM->GetVolume(&nowVolume);
		nowVolume += m_fadeVolume;

		if (nowVolume > 1.f)
			nowVolume = 1.f;
		if (nowVolume < 0.f)
			nowVolume = 0.f;

		CDebugWindow::Print(ShimizuKeisuke, "Volume", nowVolume);
		m_BGM->SetVolume(nowVolume);

		if ((m_fadeVolume <= 0.f && nowVolume <= m_newVolume) ||
			(m_fadeVolume >= 0.f && nowVolume >= m_newVolume))
		{
			m_BGM->SetVolume(m_newVolume);
			m_isFade = false;
		}
		m_frame = 0;
	}
	m_frame++;
}

void CSound::BGMSet(const char * src, float volume)
{
	m_bgmBuffer = CreateSound(src, true);
	m_BGM = StartSound(m_bgmBuffer);
	m_BGM->SetVolume(volume);
}

void CSound::SetVolumeFade(float newVolume, int flame)
{
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
