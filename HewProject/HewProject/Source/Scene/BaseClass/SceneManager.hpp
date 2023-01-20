#pragma once
#include <ISceneBase.hpp>
#include <memory>


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


class CSceneManager
{
public:
	static void SetScene(ESceneID id);
	static void Update();
	static void Draw();

	static void SwapScene();
private:
	static std::unique_ptr<IScene> m_scene;
	static bool m_isSwap;
	static ESceneID m_next;
};