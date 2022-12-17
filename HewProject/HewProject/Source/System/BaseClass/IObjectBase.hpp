#pragma once
#include <DirectXMath.h>
#include <memory>
#include <string>
enum EObjectTag
{
	TAG_NONE,
	TAG_PLAYER,
	TAG_CAMERA,
	TAG_ENEMY,
	TAG_BEAM,
	TAG_SHOCK,	// �Ռ��g
	TAG_STATIC_OBJECT,	// �ړ����Ȃ��I�u�W�F�N�g�iStatic���m�̔���͂��Ȃ��j
	// �K�v�ȏꍇ�͂����Ƀ^�O��ǋL����
};

enum ECollisionType
{
	COLLISION_NONE,		// �����蔻����g�p���Ȃ�
	COLLISION_SPHIRE,	// ���̓����蔻��
	COLLISION_RAY,		// ���C�̓����蔻��
	COLLISION_PLANE,	// �̓����蔻��
	// �V���ɓ����蔻��̎�ނ����ꍇ�͂����ɒǉ�����B
};

struct SphireData
{
	DirectX::XMFLOAT3 sphirePos;	// ���̒��S
	float sphireRadius;				// ���̔��a
};

struct RayData
{
	DirectX::XMFLOAT3 rayStart;		// ���C�̊J�n�_
	DirectX::XMVECTOR rayDirection;	// ���C�̕���
	float rayLength;				// ���C�̒���
};

struct PlaneData
{
	DirectX::XMFLOAT3 planePos;		// �ʂ̒��S���W	()
	DirectX::XMFLOAT2 planeSize;	// �ʂ̉��c		(x:��,y:�c)
	DirectX::XMFLOAT3 planeRot;		// �ʂ̊p�x		(�f�t�H���g�͖@���x�N�g��������B����]�B45���̂Ƃ��� 45 ��OK)
};

union UCollisionData
{
	SphireData sphire;		// ���̏��
	RayData ray;			// ���C�̏��
	PlaneData plane;		// �ʂ̏��
};

struct TObjectParam
{
	// �I�u�W�F�N�g���W
	DirectX::XMFLOAT3 pos;
	// �I�u�W�F�N�g�̑��x
	DirectX::XMFLOAT3 move;
	// �I�u�W�F�N�g�̉����x
	DirectX::XMFLOAT3 accel;
	// �I�u�W�F�N�g�̉�]
	DirectX::XMFLOAT3 rot;
	// �I�u�W�F�N�g�̊g�嗦
	DirectX::XMFLOAT3 scale;
	// �I�u�W�F�N�g�̃^�O�O���[�v�i��̗񋓑́j
	EObjectTag tag;
	// ��������̌o�߃t���[��
	int frame;
	// ���O
	std::string name;
	// �폜�t���O
	bool isDestroy;
	// �����蔻��ݒ�
	ECollisionType collisionType;
	// �����蔻��f�[�^
	UCollisionData collisionData;
};

/// <summary>
/// �I�u�W�F�N�g�ƃ}�l�[�W���[���Ȃ��C���^�t�F�[�X�N���X�i�悭�킩���ĂȂ��j
/// </summary>
class IObjectBase
{
public:
	using Ptr = std::shared_ptr<IObjectBase>;
	using Ref = std::weak_ptr<IObjectBase>;
	
public:
	virtual void BaseUpdate() = 0;
	virtual void BaseDraw() = 0;
	virtual void OnCollision(Ptr collisionObj) = 0;
	virtual void OnCollisionTag(EObjectTag tag) = 0;
	virtual TObjectParam GetParam() = 0;
	

	virtual ~IObjectBase() {}

};