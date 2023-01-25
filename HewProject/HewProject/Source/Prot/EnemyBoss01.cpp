#include"EnemyBoss01.hpp"
#include <Easing.hpp>
#include <SceneBase.hpp>
#include <Controller.hpp>
#include <Camera.hpp>
#include <Blend.hpp>
#include <SceneManager.hpp>
#include <SceneResult.hpp>
// �����蔻��͌�ŕt���܂��B

CProtEnemyBoss::CProtEnemyBoss()
	: CObjectBase("Assets/Model/test2.fbx", 0.2f)
	, m_move(0.023f)
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
	m_param.pos.z = ((rand() % 100) / 10.0f)+23.f;

	// ��ނ����ʂ���^�O��ݒ�
	m_param.tag = TAG_ENEMY_BOSS;
	// UI��ݒ�
	m_bossUI.reset(new CBossUI());
	// �`��̃I�t�Z�b�g���w��i�����I��"Pos"�ƕ`��̃M���b�v�𖄂߂�j
	m_param.drawOffset = { 0,1.7f,0 };

	// �����蔻��̏��ݒ�
	m_param.collisionType = COLLISION_CHARACTER;
	m_param.collisionData.character.pos = m_param.pos;
	m_param.collisionData.character.pos.y = m_param.drawOffset.y + 0.08f;
	m_param.collisionData.character.radius = 1.0f;

	Model::AnimeNo no = m_modelData.model->AddAnimation("Assets/Model/walk_neko.fbx");
	if (no == Model::ANIME_NONE)
		MessageBox(nullptr, "walk.fbx", "Error", MB_OK);
	m_modelData.model->Play(no, true);


	m_param.hp *= 1.6f;

	m_Fream = 0;
}

CProtEnemyBoss::~CProtEnemyBoss()
{

}

void CProtEnemyBoss::Update()
{
	m_oldPos = m_param.pos;
	// �����v���C���[�̃I�u�W�F�N�g�������Ă����������x�擾
	if (m_player.expired() == true)
	{
		auto objList = CSceneBase::GetObjList();
		m_player = objList.lock()->FindTag(TAG_PLAYER);
	}

	// �ړ���[����
	Move();

	m_param.pos.y -= 0.08f;
	// �^��������
	if(m_param.pos.y < 0)
		m_param.pos.y = 0;

	AddVector3(m_param.move, m_param.accel);
	AddVector3(m_param.pos, m_param.move);

	// �����蔻��̍X�V
	m_param.collisionData.character.pos = m_param.pos;
	m_param.collisionData.character.pos.y += m_param.drawOffset.y + 0.1f;
	m_param.collisionData.character.radius = 1.4f;

	// �{�XUI�̍X�V
	m_bossUI->Update();

	// �{�X������ł�����
	if (m_param.hp <= 0.0f)
	{
		m_Fream++;
		// �R�b��������
		if (m_Fream >= 180)
		{
			CSceneResult::SetClear();
			CSceneManager::SetScene(SCENE_RESULT);
		}
	}
}

void CProtEnemyBoss::Draw()
{
	m_modelData.model->Step(1.0f / 60.0f);
	CObjectBase::Draw();
	
	// �{�XUI�̕`��
	m_bossUI->SetLife(m_param.hp / 1.6f);
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
	switch (obj->GetParam().tag)
	{
	case TAG_NONE:
		break;
	case TAG_PLAYER:
		break;
	case TAG_CAMERA:
		break;
	case TAG_ENEMY:
		break;
	case TAG_BEAM:
		break;
	case TAG_SHOCK:
		break;
	case TAG_STATIC_OBJECT:
		m_param.pos.x = m_oldPos.x;
		m_param.pos.z = m_oldPos.z;
		m_param.move = { 0.f,0.f,0.f };
		break;
	default:
		break;
	}
}

void CProtEnemyBoss::OnCollisionTag(EObjectTag tag)
{
	if (tag == TAG_BEAM)
	{
		m_param.hp -= 0.005f;
	}
}