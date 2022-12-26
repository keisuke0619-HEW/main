#pragma once

#include <ObjectManager.hpp>
#include <memory>
#include <GameUI.h>
#include <UiManager.hpp>
#include <map>
class COverlayWindowBase
{
public:
	COverlayWindowBase();
	virtual ~COverlayWindowBase();

	void UpdateBase();
	void DrawBase();
	void Uninit();
	std::weak_ptr<CObjectManager> GetObjList();
	bool IsDestroy();
protected:
	virtual void Update() = 0;
	virtual void Draw();
	void Add(const char* tagName, CGameUI* uiObj, SortOrder sort = SORT_ORDER_UI_DEFAULT);

	int m_frame;
	bool m_isDestroy;

	std::unique_ptr<COverlayWindowBase> m_overlay;
private:
	std::map<const char*, CGameUI::Ref> m_objList;
	std::shared_ptr<CObjectManager> m_obj;
};