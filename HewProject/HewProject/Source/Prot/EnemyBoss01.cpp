#include"EnemyBoss01.hpp"
#include <Easing.hpp>
#include <SceneBase.hpp>
#include <Controller.hpp>
#include <Camera.hpp>
#include <Blend.hpp>
#include <SceneManager.hpp>
// �����蔻��͌�ŕt���܂��B

CProtEnemyBoss::CProtEnemyBoss()
	: CObjectBase("Assets/Model/bosu.fbx", 0.1f)
	, m_move(0.015f)
	, m_distance(4.0f)
	, m_cnt(0)
	, m_randNum(0)
	, m_target(DirectX::XMFLOAT3(0, 0, 0))
{
	// �I�u�W�F�N�g�̃��X�g���擾
	auto objList = CSceneBase::GetObjList();
	// �v���C���[�̃I�u�W�F�N�g���擾
	m_player = objList.lock()->FindTag(TAG_PLAYER);
	// �������W��ݒ�
	m_param.pos.x = (rand() % 100) / 10.0f;
	m_param.pos.y = 1.0f;
	m_param.pos.z = (rand() % 100) / 10.0f;
	// �����蔻��̏��ݒ�
	m_param.collisionType = COLLISION_SPHIRE;	// ���̓����蔻����g�p
	m_param.collisionData.sphire.sphirePos = m_param.pos;	// �����蔻��̒��S���W
	m_param.collisionData.sphire.sphireRadius = m_param.scale.x / 2.0f;	// �����蔻��̔��a
	// ��ނ����ʂ���^�O��ݒ�
	m_param.tag = TAG_ENEMY;
	// UI��ݒ�
	m_bossUI.reset(new CBossUI());
	// �`��̃I�t�Z�b�g���w��i�����I��"Pos"�ƕ`��̃M���b�v�𖄂߂�j
	m_param.drawOffset = { 0,0.8f,0 };
}

CProtEnemyBoss::~CProtEnemyBoss()
{

}

void CProtEnemyBoss::Update()
{
	// �����v���C���[�̃I�u�W�F�N�g�������Ă����������x�擾
	if (m_player.expired() == true)
	{
		auto objList = CSceneBase::GetObjList();
		m_player = objList.lock()->FindTag(TAG_PLAYER);
	}
	// �ړ���[����
	Move();
	// �����蔻��̒��S���X�V
	m_param.collisionData.sphire.sphirePos = m_param.pos;

	m_param.pos.y -= 0.08f;
	// �^��������
	if(m_param.pos.y < 0)
		m_param.pos.y = 0;
	// �{�XUI�̍X�V
	m_bossUI->Update();
}

void CProtEnemyBoss::Draw()
{
	CObjectBase::Draw();
	
	// �{�XUI�̕`��
	m_bossUI->SetLife(m_param.hp);
}

void CProtEnemyBoss::Move()
{
	// �v���C���[�Ƃ̋������擾
	if (m_player.expired() == false)
		m_target = m_player.lock()->GetParam().pos;
	// �v���C���[�ƃG�l�~�[�̈ʒu���
	DirectX::XMVECTOR enemy = DirectX::XMLoadFloat3(&m_param.pos);	// �G�l�~�[��pos������
	DirectX::XMVECTOR player = DirectX::XMLoadFloat3(&m_target);	// �v���C���[��pos������

	// �������v�Z
	DirectX::XMVECTOR distance = DirectX::XMVectorSubtract(player, enemy);
	distance = DirectX::XMVector3Normalize(distance);
	// float3�ɕϊ����Ċi�[
	DirectX::XMFLOAT3 movePos;

	DirectX::XMStoreFloat3(&movePos, distance);

	//�{�X�ɏ�Ɍ������Ă���
	m_param.pos.x += movePos.x * m_move; // �G�l�~�[��pos���g��
	m_param.pos.y += movePos.y * m_move;
	m_param.pos.z += movePos.z * m_move;
	m_param.frame = 0;

	DirectX::XMFLOAT3 Move;
	DirectX::XMStoreFloat3(&Move, distance);
	Move.y = 0.0f;
	if (fabsf(Move.x) + fabsf(Move.z) > 0.0f)
	{
		float rot = atan2f(Move.z, Move.x);
		m_param.rot.y = DirectX::XMConvertToRadians(90.f) - rot;
	}
	
}

// ���S���ɏ���ɌĂ΂�܂��B
void CProtEnemyBoss::Finalize()
{
	// �}�l�[�W���Ɏ��񂾂��Ƃ�`����

}

void CProtEnemyBoss::OnCollision(Ptr obj)
{
}

void CProtEnemyBoss::OnCollisionTag(EObjectTag tag)
{
	if (tag == TAG_BEAM)
	{
		m_param.hp -= 0.005f;
		if (m_param.hp <= 0.0f)
		{
			CSceneManager::SetScene(SCENE_RESULT);
		}
	}
}