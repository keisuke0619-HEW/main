#include "CometSS.hpp"

CCometSS::CCometSS()
{
	m_pos.x = 300;
	m_pos.y = 300.0f;
	m_handle = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/Title/CometSS.png"), SORT_ORDER_BACK);
	m_handle.lock()->SetSize(200, 200);
	m_handle.lock()->SetPos(m_pos);
}

CCometSS::~CCometSS()
{
}

void CCometSS::Update()
{
	//m_pos.x -= 1.0f;
	//m_pos.y -= 1.0f;
	if (m_pos.x < -100)
	{
		m_pos.x = 1380;
	}
	if (m_pos.y > 920)
	{
		m_pos.y = -10000;
	}
}

void CCometSS::Draw()
{
	m_handle.lock()->SetPos(m_pos);
}
