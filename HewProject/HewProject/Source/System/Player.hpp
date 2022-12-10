#pragma once
#include <ObjectBase.hpp>
#include <Beam.hpp>
#include <memory>

class CPlayer : public CObjectBase
{
public:
	CPlayer();
	~CPlayer();

	void Update() override;
	void Draw() override;
	void SetTarget(DirectX::XMFLOAT3 target);
private:
	float m_gra;		// 重力
	bool m_isGround;	// 地に足ついてる？
	float m_beamSize;	// ビームのサイズ
	DirectX::XMFLOAT3 m_beamTarget; // ビームの方向
	//std::unique_ptr<CBeam> m_beam;	// ビーム本体

	void Move();
	void Beam();
};