#pragma once
#include <OverlayWindowBase.hpp>
#include <NumberUI.hpp>
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


};

class CGameEnd : public COverlayWindowBase
{
public:
	CGameEnd();
	~CGameEnd();
	static bool IsLoop();

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
	CGameUI* m_speedYCursor;

	CNumberUI::Ptr m_speedXNum;
	CNumberUI::Ptr m_speedYNum;



};

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

	CGameUI* m_speedXCursor;
	CGameUI* m_speedYCursor;

	CNumberUI::Ptr m_speedXNum;
	CNumberUI::Ptr m_speedYNum;

	bool* m_next;

};

class CSetumei : public COverlayWindowBase
{
public:
	CSetumei();
	~CSetumei();

private:
	void Update();
};