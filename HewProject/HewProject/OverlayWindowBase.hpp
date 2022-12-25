#pragma once

#include <ObjectManager.hpp>
#include <memory>

class COverlayWindowBase
{
public:
	COverlayWindowBase();
	virtual ~COverlayWindowBase();

	void UpdateBase();
	void DrawBase();
	void Uninit();
	std::weak_ptr<CObjectManager> GetObjList();
protected:
	virtual void Update() = 0;
	virtual void Draw();
private:
	int m_frame;
	std::shared_ptr<CObjectManager> m_obj;
};