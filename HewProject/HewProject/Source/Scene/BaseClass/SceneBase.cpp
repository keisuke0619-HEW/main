#include "SceneBase.hpp"
CSceneBase::CSceneBase()
{
	m_frame = 0;
}

CSceneBase::~CSceneBase()
{
	CCameraBase::DeleteCameraAll();
}

void CSceneBase::BaseUpdate()
{
	Update();
	m_frame++;
}

void CSceneBase::BaseDraw()
{
	Draw();
}

void CSceneBase::Draw()
{
}
