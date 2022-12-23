#include "UiManager.hpp"
#include <Blend.hpp>
CUIManager* CUIManager::m_ins = nullptr;

CUIManager* CUIManager::GetIns()
{
    if (m_ins == nullptr)
    {
        m_ins = new CUIManager();
    }
    return m_ins;
}

CUIManager::~CUIManager()
{
}

void CUIManager::UpdateAll()
{
}

void CUIManager::DrawAll()
{
    Utility::SetBlendState(BLEND_ALPHA);
    for (auto itr = m_list.begin(); itr != m_list.end(); itr++)
    {
        (*itr)->Draw();
    }
    Utility::SetBlendState(BLEND_NONE);
}

CGameUI::Ref CUIManager::Add(CGameUI* obj, SortOrder order)
{
    // ƒ\[ƒg‚ð“ü‚ê‚é
    CGameUI::Ptr ptr;
    ptr.reset(obj);
    //m_list.push_back(ptr);
    auto itr = m_list.begin();
    while (itr != m_list.end())
    {
        if ((*itr)->GetSortID() >= order)
            break;
        itr++;
    }
    if (itr == m_list.end())
        m_list.push_back(ptr);
    else
        m_list.insert(itr, ptr);
    return ptr;
}

void CUIManager::Delete(CGameUI::Ref ref)
{
    m_list.remove(ref.lock());
}

void CUIManager::DeleteAll()
{
    if (m_ins)
        delete m_ins;
    m_ins = new CUIManager();
}

CUIManager::CUIManager()
{
    
}
