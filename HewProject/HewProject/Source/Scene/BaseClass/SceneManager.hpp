#pragma once
#include <ISceneBase.hpp>
#include <memory>
#include <vector>

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

struct TScenePassingData
{
	void* dataPtr;
	long size;
	const char* name;
};
class CSceneManager
{
public:
	static void SetScene(ESceneID id);
	static void Update();
	static void Draw();

	static void SwapScene();
	static void SetData(void* dataPtr, long size = 0, const char* name = "NO_NAME");
private:
	static std::unique_ptr<IScene> m_scene;
	static bool m_isSwap;
	static ESceneID m_next;
	static std::vector<TScenePassingData> m_passingData;
};