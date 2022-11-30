#pragma once
#include <ISceneBase.hpp>
#include <memory>
class CSceneManager
{
public:
	static void SetScene(IScene* scene);
	static void Update();
	static void Draw();


private:
	static std::unique_ptr<IScene> m_scene;
};