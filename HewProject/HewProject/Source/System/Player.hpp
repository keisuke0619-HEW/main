#pragma once
#include <ObjectBase.hpp>
#include <Beam.hpp>
#include <memory>
#include <PlayerUI.hpp>
#include "Sound.h"
class CPlayer : public CObjectBase
{
public:
	CPlayer();
	~CPlayer();

	void Update() override;
	void Draw() override;
	void SetTarget(DirectX::XMFLOAT3 target);
	void OnCollision(IObjectBase::Ptr obj) override;
private:
	float m_gra;		// �d��
	bool m_isGround;	// �n�ɑ����Ă�H
	float m_beamSize;	// �r�[���̃T�C�Y
	int m_InvincibleTime;	// ���G����
	DirectX::XMFLOAT3 m_beamTarget; // �r�[���̕���
	//std::unique_ptr<CBeam> m_beam;	// �r�[���{��
	std::unique_ptr<CPlayerUI> m_playerUI;	// �v���C���[��UI
	void Move();
	void Beam();
	XAUDIO2_BUFFER* m_pBeamSE;
	XAUDIO2_BUFFER* m_pChargeSE;
	IXAudio2SourceVoice* m_pSESource;
	bool m_isSE;
};