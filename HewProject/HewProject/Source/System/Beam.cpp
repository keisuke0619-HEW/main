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
	m_playerPos = DirectX::XMFLOAT3(0, 0, 0);
	m_size = 0;

	m_maxSize = size / 3;
	m_time = 2.0f;

	// �G�t�F�N�V�A�̏������@�ǂݍ���
	m_pEfk.reset(new CEffect(u"Assets/Effect/Laser01.efkefc"));
	m_debugOutput = false;
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
	//m_pEfk->SetRotation(0, -60, 0);
	m_pEfk->SetScale(m_maxSize, m_maxSize, m_maxSize);
	m_pEfk->SetPos(m_playerPos.x, m_playerPos.y + 1.5f, m_playerPos.z);//(m_param.pos.x, m_param.pos.y + 1.5f, m_param.pos.z);
}

void CBeam::Draw()
{
	// ���ˋN�_��m_pos�ɁA�^�[�Q�b�g���W��m_target�ɓ����Ă��܂��B
	// �����̕ϐ����玲�̉�]�����߂�rot�ɂԂ����݂܂����B
	//m_pos = DirectX::XMFLOAT3(0, 0, 0);
	//m_target = DirectX::XMFLOAT3(1, 1, 1);
	SetGeometoryVPMatrix(CCameraBase::GetPrimaryViewMatrix(), CCameraBase::GetPrimaryProjectionMatrix());

	DirectX::XMFLOAT3 rot = {};

	DirectX::XMVECTOR vPos = DirectX::XMLoadFloat3(&m_pos);
	DirectX::XMVECTOR vTarget = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&m_target), vPos));
	DirectX::XMVECTOR vToTarget = DirectX::XMVectorAdd(vTarget, DirectX::XMVectorZero());

	DirectX::XMFLOAT3 ToTarget;

	DirectX::XMStoreFloat3(&ToTarget, vToTarget);

	rot.x = -asinf(ToTarget.y);
	rot.y = atan2f(ToTarget.x, ToTarget.z);
	rot.z = 0;

	SetGeometoryTranslate(m_pos.x, m_pos.y, m_pos.z);
	SetGeometoryRotation(rot.x, rot.y, rot.z);
	SetGeometoryScaling(m_size, 10000, m_size);
	m_time -= 1.0f / 60.0f;

	// ����G�t�F�N�V�A��`�悷�邽�ߏ������d���Ȃ�
	// �V�����֐������Ȃǉ��P�̗]�n����
	m_pEfk->SetRotation(rot.x, rot.y, rot.z);
	m_pEfk->Play();
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
		DirectX::XMVECTOR vEnemyTarget = DirectX::XMVectorSubtract(vEnemyPos, vPos); // �r�[���̊J�n�n����G�̈ʒu�̒P�ʃx�N�g��
		DirectX::XMVECTOR vEnemyTargetNormal = DirectX::XMVector3Normalize(vEnemyTarget); // �r�[���̊J�n�n����G�̈ʒu�̒P�ʃx�N�g��

		// ���ς̌v�Z
		float normalDot;
		DirectX::XMVECTOR vdot = DirectX::XMVector3Dot(vTarget, vEnemyTargetNormal);

		DirectX::XMStoreFloat(&normalDot,vdot);
		if (normalDot <= 0.0f)
		{
			continue;
		}
		float disToEnemy;
		vdot = DirectX::XMVector3Dot(vTarget, vEnemyTarget);
		DirectX::XMStoreFloat(&disToEnemy, vdot);

		// �r�[���ƓG�̊p�x���v�Z
		float rad = normalDot;
		rad = acosf(rad);// �r�[���x�N�g���ƓG�x�N�g���̊p�x

		float disFromBeam = tanf(rad) * disToEnemy;
		disFromBeam = fabsf(disFromBeam);

		if (disFromBeam < m_maxSize * 3)
		{
			(*itr)->OnCollisionTag(TAG_BEAM);

		}
		else if (disFromBeam < m_maxSize * 6)
		{
			(*itr)->OnCollisionTag(TAG_SHOCK);
		}

		if (m_debugOutput == false)
		{
			CDebugWindow::Print(ShimizuKeisuke, "FromBeam", disFromBeam);
			CDebugWindow::Print(ShimizuKeisuke, "ToEnemy", disToEnemy);

		}

		m_debugOutput = true;

		//// �r�[���ƓG�Ƃ̋������v�Z
		//DirectX::XMVECTOR vEnemyToBeamDis = DirectX::XMVectorSubtract(vEnemyPos,vPos);
		//float EnemyToBeamDis;
		//DirectX::XMStoreFloat(&EnemyToBeamDis, vEnemyToBeamDis);
		//float distance = sinf(rad) * EnemyToBeamDis;

		//// ��Βl  
		//float AbsoluteValue_EnemyDis = fabsf(distance);
		//float AbsoluteValue_BeamPos = fabsf(m_size);
		//float AbsoluteValue_Shockwave = fabsf(m_size * 2.0f);

		//// �����蔻�����邽�߂̌v�Z
		//float DisResult = enemyParam.collisionData.sphire.sphireRadius - (AbsoluteValue_EnemyDis - AbsoluteValue_BeamPos);
		//float ShockwaveDisResult = enemyParam.collisionData.sphire.sphireRadius - (AbsoluteValue_EnemyDis - AbsoluteValue_Shockwave);

		// �r�[���ƓG�̓����蔻��
		//if (DisResult > 0)
		//{
		//	(*itr)->OnCollisionTag(TAG_BEAM);
		//}
		//else if (ShockwaveDisResult > 0)	// �Ռ��g�ƓG�̓����蔻��
		//{
		//	(*itr)->OnCollisionTag(TAG_SHOCK);
		//}
	}
}

void CBeam::SetPlayerPos(DirectX::XMFLOAT3 playerpos)
{
	m_playerPos = playerpos;
}
