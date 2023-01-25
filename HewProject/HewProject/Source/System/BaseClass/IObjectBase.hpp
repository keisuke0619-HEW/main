#pragma once
#include <DirectXMath.h>
#include <Model.h>
#include <ConstantBuffer.h>
#include <memory>
#include <string>
enum EObjectTag
{
	TAG_NONE,
	TAG_PLAYER,
	TAG_CAMERA,
	TAG_ENEMY,
	TAG_ENEMY_BOSS,
	TAG_BEAM,
	TAG_SHOCK,	// �Ռ��g
	TAG_STATIC_OBJECT,	// �ړ����Ȃ��I�u�W�F�N�g�iStatic���m�̔���͂��Ȃ��j
	// �K�v�ȏꍇ�͂����Ƀ^�O��ǋL����
};

enum ECollisionType
{
	COLLISION_NONE,			// �����蔻����g�p���Ȃ�

	COLLISION_CHARACTER,	// �L�����N�^�[�̓����蔻��	(�~��)
	COLLISION_OBSTACLES,	// ��Q���̓����蔻��		(������)
	COLLISION_CAMERARAY,	// �J�����̃��C�̓����蔻��	(���C)
	COLLISION_PLANE,		// �̓����蔻��			(��)

	// �V���ɓ����蔻��̎�ނ����ꍇ�͂����ɒǉ�����B
};

struct CharacterData
{
	DirectX::XMFLOAT3 pos;			// �L�����N�^�[�̒��S���W
	float radius;					// �L�����N�^�[�̔��a
};

struct ObstaclesData
{
	DirectX::XMFLOAT3 pos;			// ��Q���̍��W
	DirectX::XMFLOAT2 size;			// ��Q���̃T�C�Y	(X:���AY:�c�A�����͂���Ȃ�)
	bool spin;						// ��Q���̉�]		(true:����Afalse:�Ȃ�)
};

struct RayData
{
	DirectX::XMFLOAT3 start;		// �J�������C�̊J�n�_
	DirectX::XMVECTOR direction;	// �J�������C�̕���
	float length;					// �J�������C�̒���
};

struct PlaneData
{
	DirectX::XMFLOAT3 pos;			// �ʂ̒��S���W
	DirectX::XMFLOAT2 size;			// �ʂ̉��c		(x:��,y:�c)
	DirectX::XMFLOAT3 rot;			// �ʂ̊p�x		(�f�t�H���g�͖@���x�N�g��������B����]�B45���̂Ƃ��� 45 ��OK)
};

union UCollisionData
{
	CharacterData character;		// �L�����N�^�[�̏��
	ObstaclesData obstacles;		// ��Q���̏��
	RayData ray;					// �J�������C�̏��
	PlaneData plane;				// �ʂ̏��
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
	// �`��̃I�t�Z�b�g
	DirectX::XMFLOAT3 drawOffset;
	// �̗�
	float hp;
};

struct TModelData
{
	// ���f�����
	std::shared_ptr<Model> model;
	// ���_�o�b�t�@���
	std::shared_ptr<VertexShader> vs;
	// ���[���h�r���[�萔�o�b�t�@
	std::shared_ptr<ConstantBuffer> wvp;
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