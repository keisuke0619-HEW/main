#pragma once

class IScene
{
public:
	IScene() {};
	virtual ~IScene() {};

	virtual void BaseUpdate() = 0;
	virtual void BaseDraw() = 0;
};