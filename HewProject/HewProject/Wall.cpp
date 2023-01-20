#include"Wall.hpp"

Wall::Wall(float x, float y, float z, bool spin)
	:CObjectBase("Assets/Model/kabe.fbx", 0.2f)
{
	m_param.pos.x = x;
	m_param.pos.y = y;
	m_param.pos.z = z;
	m_param.rot.x = 0.0f;
	if (spin)
	{
		m_param.rot.y = 90.0f * 3.14159f / 180.0f;
	}
	else
	{
		m_param.rot.y = 0.0f;
	}
	m_param.rot.z = 0.0f;

	// ìñÇΩÇËîªíËÇÃê›íË
	m_param.collisionType = COLLISION_OBSTACLES;
	m_param.tag = TAG_STATIC_OBJECT;
	m_param.collisionData.obstacles.pos = m_param.pos;
	m_param.collisionData.obstacles.size = {1.5f,11.5f};
	m_param.collisionData.obstacles.spin = spin;

	m_param.drawOffset = { 0,8.0f,0 };
}

Wall::~Wall()
{
}


