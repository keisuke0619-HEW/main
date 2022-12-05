#ifndef __GAME_3D_H__
#define __GAME_3D_H__

#include <memory>
#include <SceneManager.hpp>

class Game3D
{
public:
	Game3D();
	~Game3D();

	void Update();
	void Draw();


private:
	//std::unique_ptr<Model> m_model;
	//std::shared_ptr<CPlayer> m_player;


	//void SwapCamera();

	std::unique_ptr<CSceneManager> m_scenes;



};

#endif // __GAME_3D_H__