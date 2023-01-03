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
	, m_move(0.01f)
	, m_distance(4.0f)
	, m_cnt(0)
	, m_randNum(0)
	, m_target(DirectX::XMFLOAT3(0, 0, 0))
{
	// �I�u�W�F�N�g�̃��X�g���擾
	auto objList = CSceneBase::GetObjList();
	// �v���C���[�̃I�u�W�F�N�g���擾
	m_player = objList.lock()->FindTag(TAG_PLAYER);
	m_param.pos.x = (rand() % 100) / 10.0f;
	m_param.pos.y = 1.0f;
	m_param.pos.z = (rand() % 100) / 10.0f;
	m_param.collisionType = COLLISION_SPHIRE;
	m_param.collisionData.sphire.sphirePos = m_param.pos;
	m_param.collisionData.sphire.sphireRadius = m_param.scale.x / 2.0f;
	m_param.tag = TAG_ENEMY;
	m_startPos = m_param.pos;
	m_bossUI.reset(new CBossUI());
	
	m_param.drawOffset = { 0,1.2f,0 };
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
	m_param.collisionData.sphire.sphirePos = m_param.pos;
	
	if(m_param.pos.y < 1.3f)
		m_param.pos.y = 1.3f;

	// �{�XUI�̍X�V
	m_bossUI->Update();
}

void CProtEnemyBoss::Draw()
{
	//Utility::SetBlendState(BLEND_NONE);
	CObjectBase::Draw();
	//Utility::SetBlendState(BLEND_ALPHA);
	
	// �{�XUI�̕`��
	//CObjectBase::Draw();
	m_bossUI->SetLife(m_param.hp);
}

// �ړ����[�`���BExcel���Q�l�ɍ쐬
// ���[���񂮂��g�p�B
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
	//	���������Ɋm�F

	//if (obj->GetParam().tag == TAG_BEAM)
	//{
	//	m_param.hp -= 0.001f;
	//}
}

void CProtEnemyBoss::OnCollisionTag(EObjectTag tag)
{
	if (tag == TAG_BEAM)
	{
		m_param.hp -= 0.005f;
		if (m_param.hp <= 0.0f)
		{
			//CSceneManager::SetScene(SCENE_RESULT);
			//CObjectManager::NoDestroy();
		}
	}
}