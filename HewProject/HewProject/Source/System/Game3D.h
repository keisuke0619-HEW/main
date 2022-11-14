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
	enum ECameraID
	{
		CAMERA_DEBUG,
		CAMERA_PLAYER,


		CAMERA_MAX,
	};
public:
	Game3D();
	~Game3D();

	void Update();
	void Draw();
private:
	std::unique_ptr<Model> m_model;
	CCameraBase* m_camera[CAMERA_MAX];
	std::shared_ptr<CPlayer> m_player;
	ECameraID m_camID;
	std::unique_ptr<CStage00> m_stage;


	void SwapCamera();
};

#endif // __GAME_3D_H__