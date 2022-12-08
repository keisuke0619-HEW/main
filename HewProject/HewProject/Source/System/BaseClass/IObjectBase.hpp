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
	// �K�v�ȏꍇ�͂����Ƀ^�O��ǋL����
};

enum ECollisionType
{
	COLLISION_NONE,		// �����蔻����g�p���Ȃ�
	COLLISION_BOX,		// ���̓����蔻��
	COLLISION_SPHIRE,	// ���̓����蔻��
	// �V���ɓ����蔻��̎�ނ����ꍇ�͂����ɒǉ�����B
};

union UCollisionData
{
	float sphireRadius;	// ���̔��a
	float boxScale[3];	// ���̃X�P�[��XYZ
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
	virtual TObjectParam GetParam() = 0;

	virtual ~IObjectBase() {}

};