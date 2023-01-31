#include "OverlayConfig.hpp"

#include <SceneManager.hpp>
#include <Controller.hpp>
#include <DebugWindow.hpp>
#include <SE.h>

// ��̂�����������Β����ł��܂��B
const float OVERLAY_CONFIG_CENTER_X = 640.0f;		// �R���t�B�OUI�̒��S���W
const float OVERLAY_CONFIG_X_BAR_POS_Y = 290.0f;	// ��̐ݒ�o�[��Y���W
const float OVERLAY_CONFIG_Y_BAR_POS_Y = 490.0f;	// ���̐ݒ�o�[��Y���W
const float OVERLAY_CONFIG_BAR_SIZE_X = 850.0f;		// �ݒ�o�[�̃T�C�YX
const float OVERLAY_CONFIG_BAR_SIZE_Y = 100.0f;		// �ݒ�o�[�̃T�C�YY
const float OVERLAY_CONFIG_CURSOR_SIZE_X = 70.0f;	// �J�[�\���̃T�C�YX
const float OVERLAY_CONFIG_CURSOR_SIZE_Y = 70.0f;	// �J�[�\���̃T�C�YY
const float OVERLAY_CONFIG_SPEED_MIN = 1.0f;		// �J�����X�s�[�h�̍ŏ��l
const float OVERLAY_CONFIG_SPEED_MAX = 100.0f;		// �J�����X�s�[�h�̍ő�l
const float OVERLAY_CONFIG_POS_MIN = OVERLAY_CONFIG_CENTER_X - OVERLAY_CONFIG_BAR_SIZE_X / 2.08f;	// �J�[�\���̈ړ������ŏ��l�i�Ō�̐��l�ł��܂�����
const float OVERLAY_CONFIG_POS_MAX = OVERLAY_CONFIG_CENTER_X + OVERLAY_CONFIG_BAR_SIZE_X / 2.23f;	// �J�[�\���̈ړ������ő�l

static bool g_isLoop = false;
COverlayConfig::COverlayConfig()
{
	auto tmp = new CGameUI("Assets/Img/PauseMenu/Back.png");
	tmp->SetPos({ OVERLAY_CONFIG_CENTER_X, 360 });
	tmp->SetSize({ 1100, 700 });
	Add("Back", tmp, SORT_ORDER_UI_BACK2);
	tmp = new CGameUI("Assets/Img/White.png");
	tmp->SetPos({ 640, 360 });
	tmp->SetSize({ 1280, 720 });
	tmp->SetColor255(0, 0, 0, 128);
	Add("Fade", tmp, SORT_ORDER_UI_BACK3);
	m_speedXLabel = new CGameUI("Assets/Img/Label/config_speedX.png");
	m_speedXLabel->SetPos({ 350, OVERLAY_CONFIG_X_BAR_POS_Y - 70 });
	m_speedXLabel->SetSize({ 1000, 50 });
	Add("label_x", m_speedXLabel, SORT_ORDER_UI_BACK1);
	m_speedYLabel = new CGameUI("Assets/Img/Label/config_speedY.png");
	m_speedYLabel->SetPos({ 350, OVERLAY_CONFIG_Y_BAR_POS_Y - 70 });
	m_speedYLabel->SetSize({ 1000, 50 });
	Add("label_y", m_speedYLabel, SORT_ORDER_UI_BACK1);
	m_speedXBar = new CGameUI("Assets/Img/PauseMenu/Bar.png");
	m_speedXBar->SetPos(OVERLAY_CONFIG_CENTER_X, OVERLAY_CONFIG_X_BAR_POS_Y);
	m_speedXBar->SetSize(OVERLAY_CONFIG_BAR_SIZE_X, OVERLAY_CONFIG_BAR_SIZE_Y);
	Add("XBar", m_speedXBar, SORT_ORDER_UI_BACK1);
	m_speedYBar = new CGameUI("Assets/Img/PauseMenu/Bar.png");
	m_speedYBar->SetPos(OVERLAY_CONFIG_CENTER_X, OVERLAY_CONFIG_Y_BAR_POS_Y);
	m_speedYBar->SetSize(OVERLAY_CONFIG_BAR_SIZE_X, OVERLAY_CONFIG_BAR_SIZE_Y);
	Add("YBar", m_speedYBar, SORT_ORDER_UI_BACK1);
	m_speedXCursor = new CGameUI("Assets/Img/PauseMenu/Cursor.png");
	m_speedXCursor->SetPos(OVERLAY_CONFIG_CENTER_X, OVERLAY_CONFIG_X_BAR_POS_Y);
	m_speedXCursor->SetSize(OVERLAY_CONFIG_CURSOR_SIZE_X, OVERLAY_CONFIG_CURSOR_SIZE_Y);
	Add("XCursor", m_speedXCursor);
	m_speedYCursor = new CGameUI("Assets/Img/PauseMenu/Cursor.png");
	m_speedYCursor->SetPos(OVERLAY_CONFIG_CENTER_X, OVERLAY_CONFIG_Y_BAR_POS_Y);
	m_speedYCursor->SetSize(OVERLAY_CONFIG_CURSOR_SIZE_X, OVERLAY_CONFIG_CURSOR_SIZE_Y);
	Add("YCursor", m_speedYCursor);

	m_speedXNum.reset(new CNumberUI(3, SORT_ORDER_UI_FRONT4, 2));
	m_speedXNum->SetSize(36, 45);
	m_speedYNum.reset(new CNumberUI(3, SORT_ORDER_UI_FRONT4, 2));
	m_speedYNum->SetSize(36, 45);

	CSoundSE::CountReset();
	CSoundSE::Stop();
	CSoundSE::BoolStop();
	CSoundSE::Start(CSoundSE::SE_MENU);
}

COverlayConfig::~COverlayConfig()
{
}

void COverlayConfig::Update()
{
	MoveCursor();
	SetStatus();
	CSoundSE::CountUp();
	if (Utility::GetKeyTrigger(KEY_CANCEL) || Utility::GetKeyTrigger(KEY_CONFIG))
	{
		CSoundSE::Start(CSoundSE::SE_CANCEL);
		m_isDestroy = true;
	}
	if (Utility::GetKeyTrigger(KEY_BEAM))
	{
		CSoundSE::Start(CSoundSE::SE_HENTAI);
	}
}

void COverlayConfig::MoveCursor()
{
	if (Utility::GetKeyTrigger(KEY_UP))
	{
		m_target--;
		CSoundSE::Start(CSoundSE::SE_CURSOR);
	}
	if (Utility::GetKeyTrigger(KEY_DOWN))
	{
		m_target++;
		CSoundSE::Start(CSoundSE::SE_CURSOR);
	}
	if (m_target < 0)
	{
		m_target = TARGET_MAX * 100;
	}
	
}

void COverlayConfig::SetStatus()
{
	const float addLevel = 0.5f;
	float add = 0;
	m_speedXBar->SetColor255(128, 128, 128, 128);
	m_speedXCursor->SetColor255(128, 128, 128, 128);
	m_speedYBar->SetColor255(128, 128, 128, 128);
	m_speedYCursor->SetColor255(128, 128, 128, 128);
	m_speedXNum->SetColor255(128, 128, 128, 128);
	m_speedYNum->SetColor255(128, 128, 128, 128);
	m_speedXLabel->SetColor255(128, 128, 128, 128);
	m_speedYLabel->SetColor255(128, 128, 128, 128);
	if (Utility::GetKeyPress(KEY_RIGHT))
	{
		add += addLevel;
		if (!CSoundSE::IsPlay())
		{
			CSoundSE::Start(CSoundSE::SE_BAR);
			CSoundSE::BoolPlay();
			CSoundSE::CountReset();
		}
		else
		{
			if (CSoundSE::GetCount() % 15 == 0)
				CSoundSE::Start(CSoundSE::SE_BAR);
		}
		

	}
	else if (Utility::GetKeyPress(KEY_LEFT))
	{
		add -= addLevel;
		if (!CSoundSE::IsPlay())
		{
			CSoundSE::Start(CSoundSE::SE_BAR);
			CSoundSE::BoolPlay();
			CSoundSE::CountReset();
		}
		else
		{
			if (CSoundSE::GetCount() % 15 == 0)
				CSoundSE::Start(CSoundSE::SE_BAR);
		}
	}
	else
	{
		CSoundSE::BoolStop();
	}

	
	switch (m_target % TARGET_MAX)
	{
	case 0:
		m_speedXBar->SetColor255(255, 255, 255, 255);
		m_speedXCursor->SetColor255(255, 255, 255, 255);
		m_speedXNum->SetColor255(255, 255, 255, 255);
		m_speedXLabel->SetColor255(255, 255, 255, 255);
		Utility::SetCameraSpeedX(Utility::GetCameraSpeedX() + add);
		break;
	case 1:
		m_speedYBar->SetColor255(255, 255, 255, 255);
		m_speedYCursor->SetColor255(255, 255, 255, 255);
		m_speedYNum->SetColor255(255, 255, 255, 255);
		m_speedYLabel->SetColor255(255, 255, 255, 255);
		Utility::SetCameraSpeedY(Utility::GetCameraSpeedY() + add);
		break;
	default:
		break;
	}
	// �N���b�v
	auto speedX = Utility::GetCameraSpeedX();
	auto speedY = Utility::GetCameraSpeedY();
	if (speedX < OVERLAY_CONFIG_SPEED_MIN)
	{
		Utility::SetCameraSpeedX(OVERLAY_CONFIG_SPEED_MIN);
		CSoundSE::Stop();
	}
		
	if (speedY < OVERLAY_CONFIG_SPEED_MIN)
	{
		Utility::SetCameraSpeedY(OVERLAY_CONFIG_SPEED_MIN);
		CSoundSE::Stop();
	}
		
	if (speedX > OVERLAY_CONFIG_SPEED_MAX)
	{
		Utility::SetCameraSpeedX(OVERLAY_CONFIG_SPEED_MAX);
		CSoundSE::Stop();
	}
		
	if (speedY > OVERLAY_CONFIG_SPEED_MAX)
	{
		Utility::SetCameraSpeedY(OVERLAY_CONFIG_SPEED_MAX);
		CSoundSE::Stop();
	}
		
	m_speedXCursor->SetPos(OVERLAY_CONFIG_POS_MIN + (OVERLAY_CONFIG_POS_MAX - OVERLAY_CONFIG_POS_MIN) * (Utility::GetCameraSpeedX() / OVERLAY_CONFIG_SPEED_MAX), OVERLAY_CONFIG_X_BAR_POS_Y);
	m_speedYCursor->SetPos(OVERLAY_CONFIG_POS_MIN + (OVERLAY_CONFIG_POS_MAX - OVERLAY_CONFIG_POS_MIN) * (Utility::GetCameraSpeedY() / OVERLAY_CONFIG_SPEED_MAX), OVERLAY_CONFIG_Y_BAR_POS_Y);
	m_speedXNum->SetPos(
		OVERLAY_CONFIG_POS_MIN + (OVERLAY_CONFIG_POS_MAX - OVERLAY_CONFIG_POS_MIN) * (Utility::GetCameraSpeedX() / OVERLAY_CONFIG_SPEED_MAX),
		OVERLAY_CONFIG_X_BAR_POS_Y - OVERLAY_CONFIG_CURSOR_SIZE_Y / 2.5f);
	m_speedXNum->SetNum(Utility::GetCameraSpeedX());
	m_speedYNum->SetPos(
		OVERLAY_CONFIG_POS_MIN + (OVERLAY_CONFIG_POS_MAX - OVERLAY_CONFIG_POS_MIN) * (Utility::GetCameraSpeedY() / OVERLAY_CONFIG_SPEED_MAX),
		OVERLAY_CONFIG_Y_BAR_POS_Y - OVERLAY_CONFIG_CURSOR_SIZE_Y / 2.5f);
	m_speedYNum->SetNum(Utility::GetCameraSpeedY());
}



//���������������� �����^�u�i�H�j ����������������������

CSetumei::CSetumei()
{
	auto tmp = new CGameUI("Assets/Img/StageSelect/BackGround.png");
	tmp->SetPos({ OVERLAY_CONFIG_CENTER_X, 360 });
	tmp->SetSize({ 960, 540 });
	//tmp->SetColor255(255, 255, 255, 128);
	Add("Back", tmp, SORT_ORDER_UI_BACK2);
	tmp = new CGameUI("Assets/Img/StageSelect/UI_sousa_con.png");
	tmp->SetPos({ OVERLAY_CONFIG_CENTER_X, 360 });
	tmp->SetSize({ 960 * 0.7, 540 * 0.6 });
	Add("Explamation", tmp, SORT_ORDER_UI_BACK1);
	tmp = new CGameUI("Assets/Img/White.png");
	tmp->SetPos({ 640, 360 });
	tmp->SetSize({ 1280, 720 });
	tmp->SetColor255(0, 0, 0, 128);
	Add("Fade", tmp, SORT_ORDER_UI_BACK3);

	m_wakka[OUTSIDE] = new CGameUI("Assets/Img/StageSelect/sotowakka.png");
	m_wakka[OUTSIDE]->SetPos(260, 180);
	m_wakka[OUTSIDE]->SetSize(150, 150);
	Add("OutWakka", m_wakka[OUTSIDE], SORT_ORDER_UI_FRONT);
	m_wakka[INSIDE] = new CGameUI("Assets/Img/StageSelect/utiwakka.png");
	m_wakka[INSIDE]->SetPos(260, 180);
	m_wakka[INSIDE]->SetSize(100, 100);
	Add("InWakka", m_wakka[INSIDE], SORT_ORDER_UI_BACK1);

	m_isDestroy = false;
}

CSetumei::~CSetumei()
{
}

void CSetumei::Update()
{
	m_wakka[OUTSIDE]->SetRotation(m_frame);
	m_wakka[INSIDE]->SetRotation(-m_frame);
	if (Utility::GetKeyTrigger(KEY_CANCEL))
	{
		CSoundSE::Start(CSoundSE::SE_CANCEL);
		m_isDestroy = true;
	}
}
