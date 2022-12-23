#pragma once

#include <GameUI.h>
#include <list>
class CUIManager
{
public:
	// シングルトン機構
	static CUIManager* GetIns();
	~CUIManager();

	void UpdateAll();
	void DrawAll();

	CGameUI::Ref Add(CGameUI*, SortOrder order = SORT_ORDER_DEFAULT);
	void Delete(CGameUI::Ref ref);
	void DeleteAll();
private:
	static CUIManager* m_ins;
	CUIManager();

	std::list<CGameUI::Ptr> m_list;
};