#pragma once
#include <OverlayWindowBase.hpp>

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
};