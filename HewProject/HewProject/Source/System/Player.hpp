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
	float m_gra;		// �d��
	bool m_isGround;	// �n�ɑ����Ă�H
	float m_beamSize;	// �r�[���̃T�C�Y
	DirectX::XMFLOAT3 m_beamTarget; // �r�[���̕���
	//std::unique_ptr<CBeam> m_beam;	// �r�[���{��

	void Move();
	void Beam();
};