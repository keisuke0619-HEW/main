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

	// カーソル移動（縦移動）
	void MoveCursor();
	// 要素をいじる（横移動）
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

// タイトルに戻りますか？
class CTitleBack : public COverlayWindowBase
{
public:
	 CTitleBack();
	~CTitleBack();
	static bool IsLoop();

	void SetIsNext(bool* next);
private:
	void Update();

	// カーソル移動（縦移動）
	void MoveCursor();
	// 要素をいじる（横移動）
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