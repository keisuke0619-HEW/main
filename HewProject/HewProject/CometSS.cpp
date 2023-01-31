#include "CometSS.hpp"

CCometSS::CCometSS()
{
	m_pos.x = (float)(rand() % 1880);
	m_pos.y = -10000.0f;
	m_handle = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/Title/CometSS.png"), SORT_ORDER_BACK);
}

CCometSS::~CCometSS()
{
	m_tex->Release();
}

void CCometSS::Update()
{
}

void CCometSS::Draw()
{

}
