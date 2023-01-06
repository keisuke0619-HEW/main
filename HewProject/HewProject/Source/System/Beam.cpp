#include "Beam.hpp"
#include <Geometory.h>
#include <DebugWindow.hpp>
#include <Easing.hpp>
#include <Camera.hpp>
#include <SceneBase.hpp>
CBeam::CBeam(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 target, float size)
	: CObjectBase("Assets/Box.fbx")
{
	m_pos = pos;
	m_target = target;
	m_size = 0;

	m_maxSize = size;
	m_time = 2.0f;

	// �G�t�F�N�V�A�̏������@�ǂݍ���
	m_pEfk.reset(new CEffect(u"Assets/Effect/Laser01.efkefc"));
}

CBeam::~CBeam()
{
}

void CBeam::Update()
{
	const int beamGrowFrame = 60 * 1;
	const int beamDeadFrame = 60 * 3;
	if (m_param.frame < beamGrowFrame)
	{
		m_size = m_maxSize * Utility::OutQuad((float)m_param.frame / beamGrowFrame);// += m_maxSize / beamGrowFrame;
		Collision();
	}
	if (m_param.frame >= beamDeadFrame)
	{
		Destroy();
	}	
	m_pEfk->SetRotation(0, -60, 0);
	m_pEfk->SetScale(1, 1, 1);
	m_pEfk->SetPos(m_pos.x, m_pos.y, m_pos.z);//(m_param.pos.x, m_param.pos.y + 1.5f, m_param.pos.z);
}

void CBeam::Draw()
{
	// ���ˋN�_��m_pos�ɁA�^�[�Q�b�g���W��m_target�ɓ����Ă��܂��B
	// �����̕ϐ����玲�̉�]�����߂�rot�ɂԂ����݂܂����B
	SetGeometoryVPMatrix(CCameraBase::GetPrimaryViewMatrix(), CCameraBase::GetPrimaryProjectionMatrix());

	DirectX::XMFLOAT3 rot = {};

	DirectX::XMVECTOR vPos = DirectX::XMLoadFloat3(&m_pos);
	DirectX::XMVECTOR vTarget = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&m_target), vPos));
	DirectX::XMVECTOR vToTarget = DirectX::XMVectorAdd(vTarget, DirectX::XMVectorZero());

	DirectX::XMFLOAT3 ToTarget;

	DirectX::XMStoreFloat3(&ToTarget, vToTarget);

	rot.x = atan2f(sqrtf(ToTarget.z * ToTarget.z + ToTarget.x * ToTarget.x), ToTarget.y);
	rot.y = atan2f(ToTarget.x, ToTarget.z);
	rot.z = 0;

	SetGeometoryTranslate(m_pos.x, m_pos.y, m_pos.z);
	SetGeometoryRotation(rot.x, rot.y, rot.z);
	SetGeometoryScaling(m_size, 10000, m_size);
	m_time -= 1.0f / 60.0f;

	SetColorPS(true, 0.3f, 0.56f, 1.0f, 0.5f, 1, 1);
	DrawCapsule();

	// ����G�t�F�N�V�A��`�悷�邽�ߏ������d���Ȃ�
	// �V�����֐������Ȃǉ��P�̗]�n����
	//m_pEfk->Play();
	
}

void CBeam::Collision()
{
	// �v���C���[�̃f�[�^���擾
	DirectX::XMVECTOR vPos = DirectX::XMLoadFloat3(&m_pos);
	DirectX::XMVECTOR vTarget = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&m_target), vPos));

	// �G�̃��X�g
	auto enemyList = CSceneBase::GetObjList().lock()->FindTagAll(TAG_ENEMY);

	// �G�̃��X�g�S�T��
	for (auto itr = enemyList.begin(); itr != enemyList.end(); itr++)
	{
		// �G�̃f�[�^�i�[
		auto enemyParam = (*itr)->GetParam();

		// �G�̃f�[�^���g���ăG�l�~�[�Ƃ̓����蔻����Ƃ�
		m_enemyPos = enemyParam.pos;
		DirectX::XMVECTOR vEnemyPos = DirectX::XMLoadFloat3(&m_enemyPos);
		DirectX::XMVECTOR vEnemyTarget = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(vEnemyPos, vPos)); // �r�[���̊J�n�n����G�̈ʒu�̒P�ʃx�N�g��

		// ���ς̌v�Z
		DirectX::XMVECTOR vdot = DirectX::XMVector3Dot(vTarget, vEnemyTarget);
		float A;
		DirectX::XMStoreFloat(&A,vdot);
		if (A < 0.0f)
		{
			continue;
		}
		
		// �r�[���ƓG�̊p�x���v�Z
		float rad;
		DirectX::XMStoreFloat(&rad, vdot);
		rad = acosf(rad);

		// �r�[���ƓG�Ƃ̋������v�Z
		DirectX::XMVECTOR vEnemyToBeamDis = DirectX::XMVectorSubtract(vEnemyPos,vPos);
		float EnemyToBeamDis;
		DirectX::XMStoreFloat(&EnemyToBeamDis, vEnemyToBeamDis);
		float distance = sinf(rad) * EnemyToBeamDis;

		// ��Βl  
		float AbsoluteValue_EnemyDis = fabsf(distance);
		float AbsoluteValue_BeamPos = fabsf(m_size);
		float AbsoluteValue_Shockwave = fabsf(m_size * 2.0f);

		// �����蔻�����邽�߂̌v�Z
		float DisResult = enemyParam.collisionData.sphire.sphireRadius - (AbsoluteValue_EnemyDis - AbsoluteValue_BeamPos);
		float ShockwaveDisResult = enemyParam.collisionData.sphire.sphireRadius - (AbsoluteValue_EnemyDis - AbsoluteValue_Shockwave);

		// �r�[���ƓG�̓����蔻��
		if (DisResult > 0)
		{
			(*itr)->OnCollisionTag(TAG_BEAM);
		}
		else if (ShockwaveDisResult > 0)	// �Ռ��g�ƓG�̓����蔻��
		{
			(*itr)->OnCollisionTag(TAG_SHOCK);
		}
	}
}
