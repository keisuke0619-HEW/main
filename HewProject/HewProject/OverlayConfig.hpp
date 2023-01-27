#pragma once
#include <OverlayWindowBase.hpp>
#include <NumberUI.hpp>
#include <Sound.h>
class COverlayConfig : public COverlayWindowBase
{
public:
	COverlayConfig();
	~COverlayConfig();


private:
	void Update();

	// �J�[�\���ړ��i�c�ړ��j
	void MoveCursor();
	// �v�f��������i���ړ��j
	void SetStatus();
	enum ETargetID
	{
		TARGET_SPEED_X,
		TARGET_SPEED_Y,

		TARGET_MAX,
	};
	int m_target;

	CGameUI* m_speedXCursor;
	CGameUI* m_speedXBar;
	CGameUI* m_speedYCursor;
	CGameUI* m_speedYBar;

	CNumberUI::Ptr m_speedXNum;
	CNumberUI::Ptr m_speedYNum;

	XAUDIO2_BUFFER* m_pselectSE;
	XAUDIO2_BUFFER* m_pcursorSE;
	XAUDIO2_BUFFER* m_pbarSE;

	IXAudio2SourceVoice* m_pSESource;
};

// �^�C�g���ɖ߂�܂����H
class CTitleBack : public COverlayWindowBase
{
public:
	 CTitleBack();
	~CTitleBack();
	static bool IsLoop();

	void SetIsNext(bool* next);
private:
	void Update();

	// �J�[�\���ړ��i�c�ړ��j
	void MoveCursor();
	// �v�f��������i���ړ��j
	void SetStatus();
	enum ETargetID
	{
		TARGET_SPEED_X,
		TARGET_SPEED_Y,

		TARGET_MAX,
	};
	int m_target;

	CGameUI* m_cursor;
	CGameUI* m_labelYes;
	CGameUI* m_labelNo;

	bool* m_next;

	XAUDIO2_BUFFER* m_pselectSE;
	XAUDIO2_BUFFER* m_pcursorSE;
	XAUDIO2_BUFFER* m_pcancelSE;


	IXAudio2SourceVoice* m_pSESource;

};

class CSetumei : public COverlayWindowBase
{
public:
	CSetumei();
	~CSetumei();

private:
	void Update();
};