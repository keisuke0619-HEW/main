#include "OverlayWindowBase.hpp"

COverlayWindowBase::COverlayWindowBase()
{
	m_frame = 0;
	m_isDestroy = false;
	m_obj.reset(new CObjectManager());
}

COverlayWindowBase::~COverlayWindowBase()
{
	auto mgrIns = CUIManager::GetIns();
	for (auto itr = m_objList.begin(); itr != m_objList.end(); itr++)
	{
		mgrIns->Delete(itr->second);
	}
}

void COverlayWindowBase::UpdateBase()
{
	if (m_overlay)
	{
		m_overlay->UpdateBase();
		if (m_overlay->IsDestroy())
		{
			auto ins = m_overlay.release();
			delete ins;
		}
		return;
	}
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
	if (m_overlay)
		m_overlay->DrawBase();
	//CUIManager::GetIns()->DrawAll();
}

void COverlayWindowBase::Uninit()
{
}

std::weak_ptr<CObjectManager> COverlayWindowBase::GetObjList()
{
	return m_obj;
}

bool COverlayWindowBase::IsDestroy()
{
	return m_isDestroy;
}


void COverlayWindowBase::Draw()
{
}

void COverlayWindowBase::Add(const char* tagName, CGameUI* uiObj, SortOrder sort)
{
	if (m_objList.count(tagName) != 0)
	{
#ifdef _DEBUG
		MessageBox(NULL, "COverlayWindowBase:すでにそのタグ名は使用されています。\nこの操作は無視されました。", tagName, MB_OK);
#endif // _DEBUG
		return;
	}
	m_objList[tagName] = CUIManager::GetIns()->Add(uiObj, sort);
}
