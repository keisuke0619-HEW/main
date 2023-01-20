#include"Wall.hpp"

Wall::Wall(float x, float y, float z, float rx, float ry, float rz)
	:CObjectBase("Assets/Model/kabe.fbx", 0.1f)
{
	m_param.pos.x = x;
	m_param.pos.y = y;
	m_param.pos.z = z;
	m_param.rot.x = rx;
	m_param.rot.y = ry;
	m_param.rot.z = rz;
	m_param.collisionType = COLLISION_NONE;
	m_param.tag = TAG_STATIC_OBJECT;
	m_param.drawOffset = { 0,4.0f,0 };
}

Wall::~Wall()
{
}


