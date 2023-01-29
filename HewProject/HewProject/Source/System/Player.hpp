#pragma once
#include <ObjectBase.hpp>
#include <Beam.hpp>
#include <memory>
#include <PlayerUI.hpp>
#include <Billboard.h>
#include "Sound.h"
#include <OutputEffekseer.h>
#include <ISceneBase.hpp>
#include <EnemyBoss01.hpp>

class CPlayer : public CObjectBase
{


public:
	CPlayer(Data* data);
	~CPlayer();

	void Update() override;
	void Draw() override;
	void SetTarget(DirectX::XMFLOAT3 target);
	void OnCollision(IObjectBase::Ptr obj) override;

	static bool isGetPlayerBuff();
	static void ResetBuff();
private:
	
	
	Model::AnimeNo no;
	Model::AnimeNo no1;
	Model::AnimeNo no2;
	
	
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

	int m_ChargeTime;
	bool m_isChargeContinue; // チャージ継続中？
	CEffect::Ptr m_pEfk;
	CEffect::Ptr m_pEfk2;
	CEffect::Ptr m_pEfk3;
	CEffect::Ptr m_pEfk4;

	int m_Fream;	// シーン遷移用の時間

	DirectX::XMFLOAT3 m_oldPos;

	Data* m_data;

	CProtEnemyBoss* m_pEnmeyBoss;

	void Buff();
	static bool m_isBeamPowerUpBuff;	// ビームの威力をあげるバフ中？
	static bool m_isBeamChargeUpBuff;	// ビームのチャージ速度をあげるバフ中?
	int m_BuffCnt;
	int m_OldKillCnt;	// 前回のキルカウント
	int m_KillCnt;
};