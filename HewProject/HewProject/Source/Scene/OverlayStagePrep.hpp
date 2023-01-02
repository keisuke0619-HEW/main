#pragma once

#include <OverlayWindowBase.hpp>

class COverlayStagePrep : public COverlayWindowBase
{
public:
	COverlayStagePrep(int id = 0);
	~COverlayStagePrep();

	void SetIsNext(bool* next);
private:
	void Update() override;

	enum PrepID
	{
		PREP_FADE,
		PREP_BACK,
		PREP_NAME_LABEL,
		PREP_ENEMY_LABEL,
		PREP_ENEMY_ICON_01,
		PREP_ENEMY_ICON_02,
		PREP_ENEMY_ICON_03,
		PREP_ENEMY_ICON_04,
		PREP_ENEMY_ICON_05,
		PREP_EXP,	// ステージ概要説明
		PREP_CONTROLL_EXP,	// 操作説明UI

		PREP_MAX
	};



	CGameUI* m_ui[PREP_MAX];
	bool* m_next;
};