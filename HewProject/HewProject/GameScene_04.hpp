#pragma once
#include <SceneBase.hpp>
//#include <Stage00.hpp>
#include <StageData01.hpp>
#include <Sound.h>
class CGameScene_04 : public CSceneBase
{
public:
	CGameScene_04();
	~CGameScene_04();

	void Update() override;
	void Draw() override;
	void SetData(void* dataPtr, long size = 0, const char* name = "NO_NAME");
private:
	std::unique_ptr<CStageData01> m_stage;
};