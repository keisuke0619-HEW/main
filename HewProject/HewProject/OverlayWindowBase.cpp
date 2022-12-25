#include "OverlayWindowBase.hpp"
#include <UiManager.hpp>

COverlayWindowBase::COverlayWindowBase()
{
	m_frame = 0;
	m_obj.reset(new CObjectManager());
}

COverlayWindowBase::~COverlayWindowBase()
{
}

void COverlayWindowBase::UpdateBase()
{
	m_obj->UpdateAll();
	Update();
	CUIManager::GetIns()->UpdateAll();
	m_obj->DestroyUpdate();
	m_frame++;
}

void COverlayWindowBase::DrawBase()
{
	m_obj->DrawAll();
	Draw();
	CUIManager::GetIns()->DrawAll();
}

void COverlayWindowBase::Uninit()
{
}

std::weak_ptr<CObjectManager> COverlayWindowBase::GetObjList()
{
	return m_obj;
}


void COverlayWindowBase::Draw()
{
}
