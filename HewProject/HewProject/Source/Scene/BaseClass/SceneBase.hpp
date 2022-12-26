#pragma once
#include <ISceneBase.hpp>
#include <ObjectManager.hpp>
#include <OverlayWindowBase.hpp>
#include <memory>
class CSceneBase : public IScene
{
public:
	static std::weak_ptr<CObjectManager> GetObjList();

public:
	CSceneBase();
	virtual ~CSceneBase();

	virtual void BaseUpdate() override;
	virtual void BaseDraw() override;
	virtual void Uninit() override;
protected:
	virtual void PreUpdate();
	virtual void Update() = 0;
	virtual void PreDraw();
	virtual void Draw();
	void AddOverlay(COverlayWindowBase* overlayIns);

	int m_frame;
	std::unique_ptr<COverlayWindowBase> m_overlay;
	static std::shared_ptr<CObjectManager> m_obj;
//private:
};