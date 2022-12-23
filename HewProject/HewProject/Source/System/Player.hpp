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
	float m_gra;		// 重力
	bool m_isGround;	// 地に足ついてる？
	float m_beamSize;	// ビームのサイズ
	int m_InvincibleTime;	// 無敵時間
	DirectX::XMFLOAT3 m_beamTarget; // ビームの方向
	//std::unique_ptr<CBeam> m_beam;	// ビーム本体
	std::unique_ptr<CPlayerUI> m_playerUI;	// プレイヤーのUI
	void Move();
	void Beam();
	XAUDIO2_BUFFER* m_pBeamSE;
	XAUDIO2_BUFFER* m_pChargeSE;
	IXAudio2SourceVoice* m_pSESource;
	bool m_isSE;
};