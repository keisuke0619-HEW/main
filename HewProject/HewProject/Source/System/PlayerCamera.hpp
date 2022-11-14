#pragma once
#include <Camera.hpp>
#include <memory>
#include <Player.hpp>
class CPlayerCamera : public CCameraBase
{
public:
	CPlayerCamera(std::shared_ptr<CPlayer> player);
	~CPlayerCamera();

	void Update() override;
private:
	std::shared_ptr<CPlayer> m_target;
};