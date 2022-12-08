#include "ProtEnemy.hpp"
#include <Easing.hpp>
#include <SceneBase.hpp>
#include <Controller.hpp>
// �����蔻��͌�ŕt���܂��B

CProtEnemy::CProtEnemy()
	: CObjectBase("Assets/Box.fbx", 0.2f)
	, m_move(0.008f)
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
	if (Utility::GetKeyTrigger(Utility::Key_U))
		Destroy();
	// �ړ���[����
	Move();
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
		m_param.pos.x += movePos.x * m_move; // �G�l�~�[��pos���g��
		m_param.pos.y += movePos.y * m_move;
		m_param.pos.z += movePos.z * m_move;
	}
	else
	{
		// �����_���ňړ�����
		if (m_cnt % 60 == 0)
		{
			m_randNum = rand() % 4;
		
		}
		switch (m_randNum)
		{
		case(0):
			m_param.pos.x += m_move * Utility::InOutSine(m_cnt / 60.f);
			break;
		case(1):
			m_param.pos.x -= m_move * Utility::InOutSine(m_cnt / 60.f);
			break;
		case(2):
			m_param.pos.z += m_move * Utility::InOutSine(m_cnt / 60.f);
			break;
		case(3):
			m_param.pos.z -= m_move * Utility::InOutSine(m_cnt / 60.f);
			break;
		default:
			break;
		}
	}

	// �J�E���g�𑝂₷
	
	m_cnt++;
	if (m_cnt > 60)
	{
		m_cnt = 0;
	}
}

// ���S���ɏ���ɌĂ΂�܂��B
void CProtEnemy::Finalize()
{
	// �}�l�[�W���Ɏ��񂾂��Ƃ�`����

}
