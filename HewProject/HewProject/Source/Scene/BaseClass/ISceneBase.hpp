#pragma once

class IScene
{
public:
	IScene() {};
	virtual ~IScene() {};

	virtual void BaseUpdate() = 0;
	virtual void BaseDraw() = 0;
	virtual void Uninit() = 0;
};