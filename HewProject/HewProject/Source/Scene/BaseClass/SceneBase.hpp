#pragma once
#include <ISceneBase.hpp>
#include <ObjectManager.hpp>
#include <OverlayWindowBase.hpp>
#include <memory>
#include <Sound.h>

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
	void BGMSet(const char* src, float volume = 1.0f);
	void BGMStop();
	void BGMRestart();

	int m_frame;
	std::unique_ptr<COverlayWindowBase> m_overlay;
	static std::shared_ptr<CObjectManager> m_obj;
	IXAudio2SourceVoice* m_BGM;
private:
	XAUDIO2_BUFFER* m_bgmBuffer;
};