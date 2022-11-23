#ifndef __GAME_3D_H__
#define __GAME_3D_H__

#include "Model.h"
#include <memory>
#include <ConstantBuffer.h>
#include <Camera.hpp>

#include <Stage00.hpp>
#include <Player.hpp>
class Game3D
{
public:
	Game3D();
	~Game3D();

	void Update();
	void Draw();
private:
	std::unique_ptr<Model> m_model;
	std::shared_ptr<CPlayer> m_player;
	std::unique_ptr<CStage00> m_stage;


	void SwapCamera();
};

#endif // __GAME_3D_H__