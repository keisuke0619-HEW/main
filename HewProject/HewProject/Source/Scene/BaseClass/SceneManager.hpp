#pragma once
#include <ISceneBase.hpp>
#include <memory>


enum ESceneID
{
	SCENE_TITLE,
	SCENE_STAGE_SELECT,
	SCENE_STAGE01,
	SCENE_RESULT,

};


class CSceneManager
{
public:
	static void SetScene(ESceneID id);
	static void Update();
	static void Draw();


private:
	static std::unique_ptr<IScene> m_scene;
};