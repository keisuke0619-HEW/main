#pragma once
#include <SceneBase.hpp>
#include <Stage00.hpp>
class CSceneTest : public CSceneBase
{
public:
	CSceneTest();
	~CSceneTest();

	void Update() override;
	void Draw() override;
private:
	std::unique_ptr<CStage00> m_stage;

};