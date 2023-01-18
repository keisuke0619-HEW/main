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
	m_pEfk.reset(new CEffect(u"Assets/Effect/Beamtame.efkefc"));

	m_pEfk2.reset(new CEffect(u"Assets/Effect/Beamhassya.efkefc"));
}

CBeam::~CBeam()
{
	/*m_pEfk->~CEffect();
	m_pEfk2->~CEffect();*/
	//m_pEfk->End();
	//m_pEfk2->End();
}

void CBeam::Update()
{
	const int beamGrowFrame = 60 * 1;
	const int beamDeadFrame = 60 * 3;
	if (m_param.frame < beamGrowFrame)
	{
		m_size = m_maxSize * Utility::OutQuad((float)m_param.frame / beamGrowFrame);// += m_maxSize / beamGrowFrame;
		if (m_SelectEfk == 2)
		{
			Collision();
		}
	}
	if (m_param.frame >= beamDeadFrame)
	{
		Destroy();
	}
	//m_pEfk->SetRotation(0, -60, 0);
	switch (m_SelectEfk)
	{
	case(1):
		m_pEfk->SetScale(m_maxSize, m_maxSize, m_maxSize);
		m_pEfk->SetPos(m_playerPos.x, m_playerPos.y + 1.5f, m_playerPos.z);
		break;
	case(2):
		m_pEfk2->SetScale(m_maxSize, m_maxSize, m_maxSize);
		m_pEfk2->SetPos(m_playerPos.x, m_playerPos.y + 1.5f, m_playerPos.z);
		break;
	default:
		break;
	}
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

	switch (m_SelectEfk)
	{
	case(1):
		m_pEfk->SetRotation(rot.x, rot.y, rot.z);
		m_pEfk->Play();
		break;
	case(2):
		m_pEfk2->SetRotation(rot.x, rot.y, rot.z);
		m_pEfk2->Play();
		break;
	default:
		break;
	}
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
		DirectX::XMVECTOR vEnemyTarget = DirectX::XMVectorSubtract(vEnemyPos, vPos); // �r�[���̊J�n�n�_����G�̈ʒu�̃x�N�g��
		DirectX::XMVECTOR vEnemyTargetNormal = DirectX::XMVector3Normalize(vEnemyTarget); // �r�[���̊J�n�n�_����G�̈ʒu�̒P�ʃx�N�g��

		// ���ς̌v�Z�P�i�p�x���Ƃ邽�߂̌v�Z�B�P�ʃx�N�g���~�P�ʃx�N�g������Acos�Ŋp�x�擾�\�j
		float normalDot;	// ���ς̌��ʂ�ۑ�����ϐ�
		DirectX::XMVECTOR vdot = DirectX::XMVector3Dot(vTarget, vEnemyTargetNormal);	// ���ς��v�Z
		DirectX::XMStoreFloat(&normalDot, vdot);	// float�^�̕ϐ��Ɋi�[
		if (normalDot <= 0.0f)	// ���͔��肵�Ȃ�
		{
			continue;
		}
		// ���ς̌v�Z�Q�i�r�[���̂ǂ̒n�_����ԋ߂������擾�B�P�ʃx�N�g���~�x�N�g���Ńx�N�g�����P�ʃx�N�g���ɗ��Ƃ��e�̒����ɓ������̂𗘗p�B�j
		float disToEnemy;	// �r�[���x�N�g���ɗ�����e�̒������i�[����
		vdot = DirectX::XMVector3Dot(vTarget, vEnemyTarget);	// �r�[���P�ʃx�N�g���ƓG�x�N�g���̓��ρB�i���r�[���x�N�g���ɗ�����e�̒����j
		DirectX::XMStoreFloat(&disToEnemy, vdot);	// float�Ɋi�[

		// �r�[���ƓG�̊p�x���v�Z
		float rad = acosf(normalDot);// �r�[���x�N�g���ƓG�x�N�g���̊p�x

		float disFromBeam = tanf(rad) * disToEnemy;	// �r�[������G�̋���
		disFromBeam = fabsf(disFromBeam);			// ��Βl���Ƃ�

		// �ȉ������蔻��
		if (disFromBeam < m_maxSize * 3)
		{
			(*itr)->OnCollisionTag(TAG_BEAM);

		}
		else if (disFromBeam < m_maxSize * 6)
		{
			(*itr)->OnCollisionTag(TAG_SHOCK);
		}
	}
}

void CBeam::SetPlayerPos(DirectX::XMFLOAT3 playerpos)
{
	m_playerPos = playerpos;
}

void CBeam::SetEffekseer(int selectnum)
{
	m_SelectEfk = selectnum;
}
