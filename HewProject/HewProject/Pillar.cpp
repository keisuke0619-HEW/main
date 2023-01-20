#include "Pillar.hpp"

CPillar::CPillar(float x, float y, float z)
	: CObjectBase("Assets/Model/hasira.fbx", 0.2f)
{
	m_param.pos.x = x;
	m_param.pos.y = y;
	m_param.pos.z = z;
	// ìñÇΩÇËîªíËÇÃê›íË
	m_param.collisionType = COLLISION_OBSTACLES;
	m_param.tag = TAG_STATIC_OBJECT;
	m_param.collisionData.obstacles.pos = m_param.pos;
	m_param.collisionData.obstacles.size = { 4.0f,4.0f };
	m_param.collisionData.obstacles.spin = false;

	//m_param.drawOffset = { 0,5.8f,0 };
}

CPillar::~CPillar()
{
}
