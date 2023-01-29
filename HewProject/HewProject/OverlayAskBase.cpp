#include "OverlayAskBase.hpp"
#include <Controller.hpp>
#include <SE.h>
COverlayAskBase::COverlayAskBase(const char* textSource, bool* out)
{
	m_out = out;
	auto tmp  = new CGameUI("Assets/Img/PauseMenu/flame.png");
	tmp->SetData(640, 360, 1100, 500);
	Add("Back", tmp, SORT_ORDER_UI_BACK4);

	m_circleIn = new CGameUI("Assets/Img/PauseMenu/circle_in.png");
	m_circleIn->SetData(640, 360, 200, 200);
	Add("CircleIn", m_circleIn, SORT_ORDER_UI_BACK3);

	m_circleOut = new CGameUI("Assets/Img/PauseMenu/circle_out.png");
	m_circleOut->SetData(640, 360, 300, 300);
	Add("CircleOut", m_circleOut, SORT_ORDER_UI_BACK3);

	tmp = new CGameUI("Assets/Img/White.png");
	tmp->SetData(640, 360, 1280, 720);
	tmp->SetColor255(0, 0, 0, 128);
	Add("Fade", tmp, SORT_ORDER_UI_BACKEND);

	m_cursor = new CGameUI("Assets/Img/PauseMenu/Cursor2.png");
	m_cursor->SetPos(520, 400);
	m_cursor->SetSize(125, 50);
	m_cursor->SetColor(1.0f, 1.0f, 1.0f, 0.5f);
	Add("Cursor", m_cursor, SORT_ORDER_UI_BACK);

	m_labelYes = new CGameUI("Assets/Img/PauseMenu/Label_Yes.png");
	m_labelYes->SetData(520, 370, 1400, 70);
	Add("Label_Yes", m_labelYes, SORT_ORDER_UI_FRONT);

	m_labelNo = new CGameUI("Assets/Img/PauseMenu/Label_No.png");
	m_labelNo->SetData(760, 370, 1400, 70);
	Add("Label_No", m_labelNo, SORT_ORDER_UI_FRONT);

	tmp = new CGameUI(textSource);
	tmp->SetData(640, 220, 1800, 90);
	Add("Label_Text", tmp, SORT_ORDER_UI_FRONT);

	for (int i = 0; i < 7; i++)
	{
		std::string str = "GAUGE_";
		str += std::to_string(i);
		m_gauge[i] = new CGameUI("Assets/Img/PauseMenu/virticalBar.png");
		m_gauge[i]->SetData(934 + i * 36, 547, 23, 60);
		m_gauge[i]->SetColor(0, 0, 0, 1);
		Add(str, m_gauge[i]);
	}
	m_target = 1;
	CSoundSE::Stop();
	CSoundSE::Start(CSoundSE::SE_BACK);
}

COverlayAskBase::~COverlayAskBase()
{
}

void COverlayAskBase::Update()
{
	// カーソル移動
	if (Utility::GetKeyTrigger(KEY_LEFT))
	{
		if (!m_target)
			CSoundSE::Start(CSoundSE::SE_CURSOR);
		m_target = 1;
	}
	if (Utility::GetKeyTrigger(KEY_RIGHT))
	{
		if (m_target)
			CSoundSE::Start(CSoundSE::SE_CURSOR);
		m_target = 0;
	}
	if (Utility::GetKeyTrigger(KEY_SELECT))
	{
		*m_out = m_target;
		m_isDestroy = true;
		if (m_target)
		CSoundSE::Start(CSoundSE::SE_SELECT);
		else
			CSoundSE::Start(CSoundSE::SE_CANCEL);
	}
	if (Utility::GetKeyTrigger(KEY_CANCEL))
	{
		m_out = false;
		m_isDestroy = true;
		CSoundSE::Start(CSoundSE::SE_CANCEL);
	}
	m_circleIn->SetRotation(m_frame);
	m_circleOut->SetRotation(-m_frame * 0.8f);

	for (int i = 0; i < 7; i++)
	{
		auto step = -m_frame + i * (720.0f / 7);
		float width = (sinf(DirectX::XMConvertToRadians(step)) + 1.0f) / 2.3f;
		m_gauge[i]->SetUVPos(0, width);
		m_gauge[i]->SetUVScale(1, 1.0f - width);
	}

}

void COverlayAskBase::Draw()
{
	// 描画場所指定
	m_labelYes->SetSize(1400, 70);
	m_labelNo->SetSize(1400, 70);
	if (m_target % 2 == 1)
	{
		m_labelYes->SetSize(1800, 90);
		m_cursor->SetPos(520, 400);
	}
	else
	{
		m_labelNo->SetSize(1800, 90);
		m_cursor->SetPos(760, 400);
	}
	m_cursor->SetSize(
		(sinf(DirectX::XMConvertToRadians(m_frame * 4)) * 0.05f + 0.9f) * 125,
		(sinf(DirectX::XMConvertToRadians(m_frame * 4)) * 0.05f + 0.9f) * 50);
}
