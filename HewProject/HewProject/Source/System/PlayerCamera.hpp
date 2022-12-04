#pragma once
#include <Camera.hpp>
#include <memory>
#include <ObjectToManagerInterface.hpp>
class CPlayerCamera : public CCameraBase
{
public:
	CPlayerCamera();
	~CPlayerCamera();

	void Update() override;
private:
	std::weak_ptr<IObjectBase> m_target;
};