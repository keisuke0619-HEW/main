#include "ProtEnemy.hpp"
#include <Easing.hpp>
#include <SceneBase.hpp>
#include <Controller.hpp>
#include <Camera.hpp>
#include <Blend.hpp>
// �����蔻��͌�ŕt���܂��B

CProtEnemy::CProtEnemy()
	: CObjectBase("Assets/Box.fbx", 0.4f)
	, m_move(0.05f)
	, m_distance(4.f)
	, m_cnt(0)
	, m_randNum(0)
	, m_target(DirectX::XMFLOAT3(0,0,0))
{
	// �I�u�W�F�N�g�̃��X�g���擾
	auto objList = CSceneBase::GetObjList();
	// �v���C���[�̃I�u�W�F�N�g���擾
	m_player = objList.lock()->FindTag(TAG_PLAYER);
	m_param.pos.x = (rand() % 100) / 10.0f;
	m_param.pos.y = 1.0f;
	m_param.pos.z = (rand() % 100) / 10.0f;
	m_param.collisionType = COLLISION_BOX;
	m_param.collisionData.boxScale = { 1,1,1 };
	m_startPos = m_param.pos;
}

CProtEnemy::~CProtEnemy()
{

}

void CProtEnemy::Update()
{
	// �����v���C���[�̃I�u�W�F�N�g�������Ă����������x�擾
	if (m_player.expired() == true)
	{
		auto objList = CSceneBase::GetObjList();
		m_player = objList.lock()->FindTag(TAG_PLAYER);
	}
	// �ړ���[����
	Move();
}

void CProtEnemy::Draw()
{
	Utility::SetBlendState(BLEND_NONE);
	CObjectBase::Draw();
	Utility::SetBlendState(BLEND_ALPHA);
}

// �ړ����[�`���BExcel���Q�l�ɍ쐬
// ���[���񂮂��g�p�B
void CProtEnemy::Move()
{
	// ���[���񂮎g�p���@�i��j
	// Easing::InOutSine(level);

	// �v���C���[�Ƃ̋������擾
	if(m_player.expired() == false)
		m_target = m_player.lock()->GetParam().pos;
	// �v���C���[�ƃG�l�~�[�̈ʒu���
	DirectX::XMVECTOR enemy = DirectX::XMLoadFloat3(&m_param.pos);	// �G�l�~�[��pos������
	DirectX::XMVECTOR player = DirectX::XMLoadFloat3(&m_target);	// �v���C���[��pos������

	// �������v�Z
	DirectX::XMVECTOR distance = DirectX::XMVectorSubtract(player, enemy);

	// float3�ɕϊ����Ċi�[
	DirectX::XMFLOAT3 movePos;
	DirectX::XMStoreFloat3(&movePos, distance);


	// �����v���C���[�Ƃ̋��������ȉ���������
	if (fabsf(movePos.x) <= m_distance && fabsf(movePos.y) <= m_distance && fabsf(movePos.z) <= m_distance)
	{
		// �v���C���[��ڕW�ɂ���
		m_param.pos.x += movePos.x * m_move / 2; // �G�l�~�[��pos���g��
		m_param.pos.y += movePos.y * m_move / 2;
		m_param.pos.z += movePos.z * m_move / 2;
		m_param.frame = 0;
	}
	else
	{
		if (m_param.frame % 300 == 0)
		{
			m_randTarget = { (float)(rand() % 30), 0.5f, (float)(rand() % 30) };
			m_startPos = m_param.pos;
		}
		m_param.move = {
			(m_startPos.x + (m_randTarget.x - m_startPos.x) * Utility::InOutSine((m_param.frame % 300) / 300.0f)) - (m_startPos.x + (m_randTarget.x - m_startPos.x) * Utility::InOutSine(((m_param.frame % 300) - 1) / 300.0f)),
			(m_startPos.y + (m_randTarget.y - m_startPos.y) * Utility::InOutSine((m_param.frame % 300) / 300.0f)) - (m_startPos.y + (m_randTarget.y - m_startPos.y) * Utility::InOutSine(((m_param.frame % 300) - 1) / 300.0f)),
			(m_startPos.z + (m_randTarget.z - m_startPos.z) * Utility::InOutSine((m_param.frame % 300) / 300.0f)) - (m_startPos.z + (m_randTarget.z - m_startPos.z) * Utility::InOutSine(((m_param.frame % 300) - 1) / 300.0f)),
		};
	}
}

// ���S���ɏ���ɌĂ΂�܂��B
void CProtEnemy::Finalize()
{
	// �}�l�[�W���Ɏ��񂾂��Ƃ�`����

}

void CProtEnemy::OnCollision(Ptr obj)
{
	if (obj->GetParam().tag == TAG_PLAYER)
	{
		Destroy();
	}
}
