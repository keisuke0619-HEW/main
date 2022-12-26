#pragma once
#include <OverlayWindowBase.hpp>

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
};