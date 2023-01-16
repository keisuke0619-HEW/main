#pragma once
#include<ObjectBase.hpp>

class Wall :public CObjectBase 
{
public:
	Wall(float x = 0 , float y = 0, float z = 0);
	~Wall();
	void Update() {};
private:

};




