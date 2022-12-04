#pragma once
#include <ObjectBase.hpp>
#include <ObjectToManagerInterface.hpp>
#include <memory>
class CProtEnemy : public CObjectBase
{
public:
	CProtEnemy();
	~CProtEnemy();

	void Update() override;

private:
	void Move();
	void Finalize() override;

	IObjectBase::Ref m_player;
};