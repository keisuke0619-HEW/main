#pragma once

enum ESceneID
{
	SCENE_TITLE,
	SCENE_STAGE_SELECT,
	SCENE_STAGE01,
	SCENE_STAGE02,
	SCENE_STAGE03,
	SCENE_STAGE04,
	SCENE_RESULT,

};

struct Data	// リザルトに送るデータ
{
	int MAX_kill;
	int MAX_cnt;
	ESceneID BackScene;
};

class IScene
{
public:
	IScene() { m_data.MAX_kill = 0; m_data.MAX_cnt = 0; m_data.BackScene = SCENE_TITLE; };
	virtual ~IScene() {};

	virtual void BaseUpdate() = 0;
	virtual void BaseDraw() = 0;
	virtual void Uninit() = 0;
	virtual void SetData(void* dataPtr, long size = 0, const char* name = "NO_NAME") = 0;
	Data* GetData() { return &m_data; };
	void SetData(ESceneID ID) { m_data.BackScene = ID; };
protected:
	Data m_data;
};