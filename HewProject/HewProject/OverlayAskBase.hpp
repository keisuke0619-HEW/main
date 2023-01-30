#pragma once
#include <OverlayWindowBase.hpp>

class COverlayAskBase : public COverlayWindowBase
{
public:
	COverlayAskBase(const char* textSource, bool* out);
	virtual ~COverlayAskBase();

protected:
	virtual void Update() override;
	virtual void Draw() override;

	bool* m_out;
	CGameUI* m_circleIn;
	CGameUI* m_circleOut;
	CGameUI* m_labelYes;
	CGameUI* m_labelNo;
	CGameUI* m_cursor;
	
	CGameUI* m_gauge[7];
	int m_target;
};