#pragma once
#include <ObjectBase.hpp>

class CPlayer : public CObjectBase
{
public:
	CPlayer();
	~CPlayer();

	void Update() override;

private:
	void Move();
	float m_gra;
	bool m_isGround;
};