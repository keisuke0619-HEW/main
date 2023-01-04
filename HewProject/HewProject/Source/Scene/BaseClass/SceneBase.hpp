#pragma once
#include <ISceneBase.hpp>
#include <ObjectManager.hpp>
#include <OverlayWindowBase.hpp>
#include <memory>
#include <Sound.h>
#include <BGM.h>
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
	virtual void SetData(void* dataPtr, long size = 0, const char* name = "NO_NAME") override;
protected:
	virtual void PreUpdate();
	virtual void Update() = 0;
	virtual void PreDraw();
	virtual void Draw();
	
	void AddOverlay(COverlayWindowBase* overlayIns);

	void SetBGM(const char* src, float volume = 0.6f);
	void SetVolumeFade(float newVolume, int frame);



	int m_frame;
	std::unique_ptr<COverlayWindowBase> m_overlay;
	static std::shared_ptr<CObjectManager> m_obj;
};