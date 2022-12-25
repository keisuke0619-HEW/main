#pragma once
#include <ISceneBase.hpp>
#include <ObjectManager.hpp>
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


	int m_frame;
	static std::shared_ptr<CObjectManager> m_obj;
//private:
};