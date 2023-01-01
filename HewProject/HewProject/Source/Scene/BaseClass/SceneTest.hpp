#pragma once
#include <SceneBase.hpp>
//#include <Stage00.hpp>
#include <ProtStage.hpp>
#include <Sound.h>
class CSceneTest : public CSceneBase
{
public:
	CSceneTest();
	~CSceneTest();

	void Update() override;
	void Draw() override;
private:
	std::unique_ptr<CProtScene> m_stage;
};