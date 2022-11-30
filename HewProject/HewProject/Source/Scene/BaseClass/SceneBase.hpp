#pragma once
#include <ISceneBase.hpp>
#include <Camera.hpp>

class CSceneBase : IScene
{
public:
	CSceneBase();
	virtual ~CSceneBase();

	virtual void BaseUpdate() override;
	virtual void BaseDraw() override;
protected:
	virtual void Update() = 0;
	virtual void Draw();

	int m_frame;

};