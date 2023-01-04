#pragma once
#include <Sound.h>
#include <memory>
class CSound
{
	// �V���O���g���@�\
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
	void BGMEnd();

private:
	CSound();
	int m_frame;
	int m_fadeFlame;
	float m_newVolume;
	float m_fadeVolume;
	bool m_isFade;
	IXAudio2SourceVoice* m_BGM;
	XAUDIO2_BUFFER* m_bgmBuffer;

	enum EResetFadeStage
	{
		RESET_FADE_NONE,	// ���Z�b�g�t�F�[�h�Ȃ�
		RESET_FADE_DOING,	// ���Z�b�g�t�F�[�h�i�������j��
		RESET_FADE_DONE,	// ���Z�b�g�t�F�[�h�i�������j�ς�
	};
	const char* m_resetNewSrc;	// �V����BGM�̃p�X��
	float m_resetVolume;		// �V����BGM�̃{�����[��
	EResetFadeStage m_isResetBGM;			// �V����BGM�ւ̕ύX�����邩
};


