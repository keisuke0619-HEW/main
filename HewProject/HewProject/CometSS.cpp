#include "CometSS.hpp"

CCometSS::CCometSS()
{
	m_pos.x =  10000 + (rand() % 1880);
	m_pos.y = -10000;
	m_handle = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/Title/CometSS.png"), SORT_ORDER_BACK);
	m_handle.lock()->SetSize(200, 200);
	m_handle.lock()->SetPos(m_pos);
}

CCometSS::~CCometSS()
{
}

void CCometSS::Update()
{
	m_pos.x -= 17.0f;
	m_pos.y += 17.0f;
	if (m_pos.y > 920)
	{
		m_pos.x = 10000 + (rand() % 1880);
		m_pos.y = -10000;
	}
}

void CCometSS::Draw()
{
	m_handle.lock()->SetPos(m_pos);
}
