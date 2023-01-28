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

};

class CSetumei : public COverlayWindowBase
{
public:
	CSetumei();
	~CSetumei();

private:
	void Update();
	enum Wakka
	{
		OUTSIDE,
		INSIDE,

		SIDE_MAX
	};
	CGameUI* m_wakka[SIDE_MAX];
};