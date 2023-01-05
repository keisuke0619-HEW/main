#include "SceneBase.hpp"
#include <UiManager.hpp>
#include <Camera.hpp>
#include <Controller.hpp>
#include <DebugCamera.hpp>
#include <Billboard.h>
#include <OutputEffekseer.h>
std::shared_ptr<CObjectManager> CSceneBase::m_obj = nullptr;

CSceneBase::CSceneBase()
{
	CCameraBase::CreateCamera(new CDebugCamera(), "Debug");
	CCameraBase::SetPrimaryCamera("Debug");

	m_frame = 0;
	if (true)//m_obj == nullptr)
	{
		m_obj.reset(new CObjectManager());
	}
}

CSceneBase::~CSceneBase()
{
	if (m_overlay)
	{
		auto ins = m_overlay.release();
		delete ins;
	}
}

void CSceneBase::BaseUpdate()
{
	// ここにオーバーレイ
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
	PreUpdate();
	m_obj->UpdateAll();
	Update();
	CUIManager::GetIns()->UpdateAll();
	CCameraBase::UpdatePrimary();
	m_obj->DestroyUpdate();
	m_frame++;

}

void CSceneBase::BaseDraw()
{
	PreDraw();
	m_obj->DrawAll();
	Draw();
	CEffect::DrawAll();
	CBillboard::DrawAll();
	if (m_overlay)
		m_overlay->DrawBase();
	CUIManager::GetIns()->DrawAll();
}

void CSceneBase::Uninit()
{
	CUIManager::GetIns()->DeleteAll();
}

void CSceneBase::SetData(void* dataPtr, long size, const char* name)
{
}

void CSceneBase::PreUpdate()
{
}

void CSceneBase::Update()
{
}

void CSceneBase::PreDraw()
{
}

std::weak_ptr<CObjectManager> CSceneBase::GetObjList()
{
	return m_obj;
}

void CSceneBase::Draw()
{
}

void CSceneBase::AddOverlay(COverlayWindowBase* overlayIns)
{
	m_overlay.reset(overlayIns);
}

void CSceneBase::SetBGM(const char* src, float volume)
{
	CSound::GetIns()->BGMSet(src, volume);
}

void CSceneBase::SetVolumeFade(float newVolume, int frame)
{
	CSound::GetIns()->SetVolumeFade(newVolume, frame);
}

