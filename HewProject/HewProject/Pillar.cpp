#include "Pillar.hpp"

CPillar::CPillar(float x, float y, float z)
	: CObjectBase("Assets/Model/hasira.fbx", 0.2f)
{
	m_param.pos.x = x;
	m_param.pos.y = y;
	m_param.pos.z = z;
	m_param.collisionType = COLLISION_NONE;
	m_param.tag = TAG_STATIC_OBJECT;
	//m_param.drawOffset = { 0,5.8f,0 };
}

CPillar::~CPillar()
{
}
