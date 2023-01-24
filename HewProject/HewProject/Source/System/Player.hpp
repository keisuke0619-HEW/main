#pragma once
#include <ObjectBase.hpp>
#include <Beam.hpp>
#include <memory>
#include <PlayerUI.hpp>
#include <Billboard.h>
#include "Sound.h"
#include <OutputEffekseer.h>

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
	bool m_isBeamStore;	// ビームを溜めている？
	//std::unique_ptr<CBeam> m_beam;	// ビーム本体
	std::unique_ptr<CPlayerUI> m_playerUI;	// プレイヤーのUI
	void Move();
	void Beam();
	XAUDIO2_BUFFER* m_pBeamSE;
	XAUDIO2_BUFFER* m_pChargeSE;
	IXAudio2SourceVoice* m_pSESource;
	bool m_isSE;

	void CancelMove();
	bool m_isCancel;	// 硬直中？
	int m_CancelTime;	// 硬直時間

	void KnockBack();
	int m_knockBackFrame;
	DirectX::XMVECTOR m_vKnockBack;
	CBillboard::Ptr m_bill;

	CEffect::Ptr m_pEfk;
	CEffect::Ptr m_pEfk2;

	int m_Fream;	// シーン遷移用の時間

	DirectX::XMFLOAT3 m_oldPos;
};