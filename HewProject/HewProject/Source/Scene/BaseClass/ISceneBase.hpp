#pragma once

class IScene
{
public:
	IScene() {};
	virtual ~IScene() {};

	virtual void BaseUpdate() = 0;
	virtual void BaseDraw() = 0;
	virtual void Uninit() = 0;
	virtual void SetData(void* dataPtr, long size = 0, const char* name = "NO_NAME") = 0;
};