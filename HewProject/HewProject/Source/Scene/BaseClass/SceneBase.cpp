#include "SceneBase.hpp"
#include <UiManager.hpp>
#include <Camera.hpp>
#include <Controller.hpp>
#include <DebugCamera.hpp>
std::shared_ptr<CObjectManager> CSceneBase::m_obj = nullptr;

CSceneBase::CSceneBase()
{
	m_BGM = nullptr;
	m_bgmBuffer = nullptr;



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
	BGMStop();
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

void CSceneBase::BGMSet(const char* src, float volume)
{
	m_bgmBuffer = CreateSound(src, true);
	m_BGM = StartSound(m_bgmBuffer);
	m_BGM->SetVolume(volume);
}

void CSceneBase::BGMStop()
{
	if (m_BGM != nullptr && GetIsUsefulSound())
	{
		m_BGM->Stop();
	}
}

void CSceneBase::BGMRestart()
{
	if (m_BGM != nullptr)
		m_BGM->Start();
}

