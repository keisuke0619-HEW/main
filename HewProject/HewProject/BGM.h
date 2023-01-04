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
		RESET_FADE_NONE,	// リセットフェードなし
		RESET_FADE_DOING,	// リセットフェード（消音化）中
		RESET_FADE_DONE,	// リセットフェード（消音化）済み
	};
	const char* m_resetNewSrc;	// 新しいBGMのパス名
	float m_resetVolume;		// 新しいBGMのボリューム
	EResetFadeStage m_isResetBGM;			// 新しいBGMへの変更があるか
};


