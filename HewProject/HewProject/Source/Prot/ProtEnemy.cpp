#include "ProtEnemy.hpp"
#include <Easing.hpp>
#include <SceneBase.hpp>
#include <Controller.hpp>
#include <Camera.hpp>
#include <Blend.hpp>

TModelData CProtEnemy::sModel;

// �����蔻��͌�ŕt���܂��B

CProtEnemy::CProtEnemy()
	: CObjectBase()	// �N���X�S�̂Ŏg���܂킷�ꍇ�͈����Ȃ�
	, m_move(0.05f)
	, m_distance(8.0f)
	, m_cnt(0)
	, m_randNum(0)
	, m_target(DirectX::XMFLOAT3(0,0,0))
	, m_dontMove(false)
	, m_blowAwayCountDown(0)
	, m_moveDirection({0.f, 0.f, 0.f})
	, m_blowAwayMove({0.f, 0.f, 0.f})
	, m_ActionNum(rand() % 4 + 1)
{
	// �������f���f�[�^�����݂��Ȃ������烍�[�h
	if (!sModel.model)
	{
		LoadModel("Assets/Model/zako.fbx", 0.1f, false, &sModel);
	}
	// ���g�̃��f���f�[�^��Static���f���f�[�^�����[�h
	m_modelData = sModel;
	// ���f�����N���X�S�̂Ŏg���܂킷�Ȃ炱���܂ł��K�{�B


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
	m_startPos = m_param.pos;
	m_param.tag = TAG_ENEMY;
	m_pPolyline = new GeometoryPolyline(30);

	// �����ŕ`������炷
	m_param.drawOffset = { 0, 1.2f, 0 };
}

CProtEnemy::~CProtEnemy()
{

}

void CProtEnemy::Update()
{
	m_param.frame++;

	// �����v���C���[�̃I�u�W�F�N�g�������Ă����������x�擾
	if (m_player.expired() == true)
	{
		auto objList = CSceneBase::GetObjList();
		m_player = objList.lock()->FindTag(TAG_PLAYER);
	}
	// �ړ���[����
	Move();
	m_param.collisionData.sphire.sphirePos = m_param.pos;
	if (m_param.pos.y < 1.3f)
	{
		m_param.pos.y = 1.3f;
	}
}

void CProtEnemy::Draw()
{
	//Utility::SetBlendState(BLEND_NONE);
	CObjectBase::Draw();
	//Utility::SetBlendState(BLEND_ALPHA);
	//��Ղ̒ǉ�
	GeometoryPolyline::Point point = {};
	//�|�����C��
	auto fCamPos = CCameraBase::GetPrimaryData().pos;
	
	DirectX::XMVECTOR vCamPos = DirectX::XMLoadFloat3(&fCamPos);
	DirectX::XMVECTOR vPos = DirectX::XMLoadFloat3(&CProtEnemy::m_param.pos);
	DirectX::XMStoreFloat3(&point.normal, DirectX::XMVectorSubtract(vCamPos, vPos));
	point.pos = CProtEnemy::m_param.pos;
	point.width = 200.0f;
	m_pPolyline->PushPoint(point);
	m_pPolyline->SetView(CCameraBase::GetPrimaryViewMatrix());
	m_pPolyline->SetProjection(CCameraBase::GetPrimaryProjectionMatrix());
	m_pPolyline->Draw();

}

// �ړ����[�`���BExcel���Q�l�ɍ쐬
// ���[���񂮂��g�p�B
void CProtEnemy::Move()
{
	// ���[���񂮎g�p���@�i��j
	// Easing::InOutSine(level);

	// �Ռ��g�ɓ������Đ�����ԂƂ��̈ړ�
	if (m_dontMove)
	{
		m_param.pos.x += m_blowAwayMove.x * m_move * m_blowAwayCountDown; // ���̌��ɂ���Ƀr�[���̋�����t��������
		m_param.pos.y += m_blowAwayMove.y * m_move * m_blowAwayCountDown;
		m_param.pos.z += m_blowAwayMove.z * m_move * m_blowAwayCountDown;

		// �J�E���g��0�ɂȂ��Ă����琁����т���߂�
		if (m_blowAwayCountDown < 0)
		{
			m_dontMove = false;
		}

		// ������ԃJ�E���g�_�E��
		m_blowAwayCountDown--;
	}

	// �Ռ��g�ɓ������ĂȂ��Ƃ��̈ړ�(�ʏ펞�̈ړ�)
	else
	{
		// �ړ���ސ؂�ւ�
		if (m_param.frame > 500)
		{
			// �v���C���[�Ƃ̋������擾
			if (m_player.expired() == false)
				m_target = m_player.lock()->GetParam().pos;

			// �v���C���[�ƃG�l�~�[�̈ʒu���
			DirectX::XMVECTOR enemy = DirectX::XMLoadFloat3(&m_param.pos);	// �G�l�~�[��pos������
			DirectX::XMVECTOR player = DirectX::XMLoadFloat3(&m_target);	// �v���C���[��pos������

			// �������v�Z
			DirectX::XMVECTOR direction = DirectX::XMVectorSubtract(player, enemy);

			// ���K�����đ��������ɂ���
			direction = DirectX::XMVector3Normalize(direction);

			// float3�ɕϊ����Ċi�[
			DirectX::XMStoreFloat3(&m_moveDirection, direction);
			
			// ��]����(A)
			float rot = 0.0f;

			if (fabsf(m_moveDirection.x) + fabsf(m_moveDirection.z) > 0.0f)
			{
				rot = atan2f(m_moveDirection.z, m_moveDirection.x);
			}

			m_ActionNum = rand() % 100;

			if (0 <= m_ActionNum && m_ActionNum <= 39)	//	40%�Ńv���C���[��
			{
				m_ActionNum = 1;
			}
			else
			{
				if (40 <= m_ActionNum && m_ActionNum <= 64)	//	25%�ŉE
				{
					m_ActionNum = 2;
				}
				else
				{
					if (65 <= m_ActionNum && m_ActionNum <= 89)	//	25%�ō�
					{
						m_ActionNum = 3;
					}
					else	//�c���10%�Ńv���C���[�Ƃ͋t��
					{
						m_ActionNum = 4;
					}
				}
			}

			DirectX::XMVECTOR move;

			switch (m_ActionNum)
			{
			case 1:
				// ��]����(B)
				m_param.rot.y = DirectX::XMConvertToRadians(90.0f) - rot;

				// �ړ������ݒ�
				move = direction;

				DirectX::XMStoreFloat3(&m_moveDirection, move);
				m_moveDirection.y = 0.0f;

				// �X�s�[�h�ύX
				m_move = 0.05f;
				break;
			case 2:
				// ��]����(B)
				m_param.rot.y = DirectX::XMConvertToRadians(180.0f) - rot;

				// �ړ������ݒ�
				move = DirectX::XMVector3TransformCoord(direction, DirectX::XMMatrixRotationY(90.0f * 3.14f / 180.0f));
				DirectX::XMStoreFloat3(&m_moveDirection, move);
				m_moveDirection.y = 0.0f;

				// �X�s�[�h�ύX
				m_move = 0.05f;
				break;
			case 3:
				// ��]����(B)
				m_param.rot.y = DirectX::XMConvertToRadians(0.0f) - rot;

				// �ړ������ݒ�
				move = DirectX::XMVector3TransformCoord(direction, DirectX::XMMatrixRotationY(-90.0f * 3.14f / 180.0f));
				DirectX::XMStoreFloat3(&m_moveDirection, move);
				m_moveDirection.y = 0.0f;

				// �X�s�[�h�ύX
				m_move = 0.05f;
				break;
			case 4:
				// ��]����(B)
				m_param.rot.y = DirectX::XMConvertToRadians(270.0f) - rot;

				// �ړ������ݒ�
				move = DirectX::XMVector3TransformCoord(direction, DirectX::XMMatrixRotationY(180.0f * 3.14f / 180.0f));
				DirectX::XMStoreFloat3(&m_moveDirection, move);
				m_moveDirection.y = 0.0f;

				// �X�s�[�h�ύX
				m_move = 0.05f;
				break;
			default:
				break;
			}

			m_param.frame = 1;
		}		

		// �ړ�
		m_param.pos.x += m_moveDirection.x * m_move; // �G�l�~�[��pos���g��
		m_param.pos.z += m_moveDirection.z * m_move;
	}
}

// ���S���ɏ���ɌĂ΂�܂��B
void CProtEnemy::Finalize()
{
	// �}�l�[�W���Ɏ��񂾂��Ƃ�`����

}

void CProtEnemy::OnCollisionTag(EObjectTag tag)
{
	
	if (tag == TAG_BEAM)
	{
		Destroy();
	}

	if (tag == TAG_SHOCK && m_dontMove == false)
	{
		// �Ռ��g�ɓ���������G�̈ړ�������
		m_dontMove = true;

		// ������ԃJ�E���g���J�n
		m_blowAwayCountDown = m_blowAwayCount;

		// �J�����̌����Ă�������擾
		DirectX::XMStoreFloat3(&m_blowAwayMove, CCameraBase::GetPrimaryFront());
	}
}

void CProtEnemy::OnCollision(IObjectBase::Ptr obj)
{
	if (obj->GetParam().tag == TAG_PLAYER)
	{
		Destroy();
	}
}


