#include "SceneBase.hpp"
std::shared_ptr<CObjectManager> CSceneBase::m_obj = nullptr;

CSceneBase::CSceneBase()
{
	m_frame = 0;
	if (m_obj == nullptr)
	{
		m_obj.reset(new CObjectManager());
	}
}

CSceneBase::~CSceneBase()
{
	CCameraBase::DeleteCameraAll();
}

void CSceneBase::BaseUpdate()
{
	PreUpdate();
	m_obj->UpdateAll();
	Update();
	CCameraBase::UpdatePrimary();
	m_obj->DestroyUpdate();
	m_frame++;
}

void CSceneBase::BaseDraw()
{
	PreDraw();
	m_obj->DrawAll();
	Draw();
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
