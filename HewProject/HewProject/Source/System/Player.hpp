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
	
	
	float m_gra;		// �d��
	bool m_isGround;	// �n�ɑ����Ă�H
	float m_beamSize;	// �r�[���̃T�C�Y
	int m_InvincibleTime;	// ���G����
	DirectX::XMFLOAT3 m_beamTarget; // �r�[���̕���
	bool m_isBeamStore;	// �r�[���𗭂߂Ă���H
	//std::unique_ptr<CBeam> m_beam;	// �r�[���{��
	std::unique_ptr<CPlayerUI> m_playerUI;	// �v���C���[��UI
	void Move();
	void Beam();
	XAUDIO2_BUFFER* m_pBeamSE;
	XAUDIO2_BUFFER* m_pChargeSE;
	IXAudio2SourceVoice* m_pSESource;
	bool m_isSE;

	void CancelMove();
	bool m_isCancel;	// �d�����H
	int m_CancelTime;	// �d������

	void KnockBack();
	int m_knockBackFrame;
	DirectX::XMVECTOR m_vKnockBack;
	CBillboard::Ptr m_bill;

	int m_ChargeTime;
	bool m_isChargeContinue; // �`���[�W�p�����H
	CEffect::Ptr m_pEfk;
	CEffect::Ptr m_pEfk2;
	CEffect::Ptr m_pEfk3;
	CEffect::Ptr m_pEfk4;

	int m_Fream;	// �V�[���J�ڗp�̎���

	DirectX::XMFLOAT3 m_oldPos;

	Data* m_data;

	CProtEnemyBoss* m_pEnmeyBoss;

	void Buff();
	static bool m_isBeamPowerUpBuff;	// �r�[���̈З͂�������o�t���H
	static bool m_isBeamChargeUpBuff;	// �r�[���̃`���[�W���x��������o�t��?
	int m_BuffCnt;
	int m_OldKillCnt;	// �O��̃L���J�E���g
	int m_KillCnt;
};