#pragma once

#include <SceneBase.hpp>
#include <GameUI.h>
class CSceneStageSelect : public CSceneBase
{
	enum EStageSelectUI
	{
		BACK,
		STAGE_ICON_01,
		STAGE_ICON_02,
		STAGE_ICON_03,
		STAGE_ICON_04,

		STAGE_SELECT_UI_MAX
	};
public:
	CSceneStageSelect();
	~CSceneStageSelect();

private:
	void Update() override;

	void MoveCursor();
	void ChangeScene();
	void SetUiAlpha();

	CGameUI::Ref m_ui[STAGE_SELECT_UI_MAX];
	int m_cursor;	// ÉJÅ[É\Éã
	bool m_isNext;

	EStageSelectUI m_nowIcon;
};