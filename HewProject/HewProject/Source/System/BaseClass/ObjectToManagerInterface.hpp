#pragma once
#include <DirectXMath.h>

enum EObjectTag
{
	TAG_NONE,
	TAG_PLAYER,
	TAG_CAMERA,
	TAG_ENEMY,
	// �K�v�ȏꍇ�͂����Ƀ^�O��ǋL����
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
	//// ���f���I�u�W�F�N�g�̃X�^�e�B�b�N���[�h�����邩�i���x�j
	//bool isStaticModel;
};

/// <summary>
/// �I�u�W�F�N�g�ƃ}�l�[�W���[���Ȃ��C���^�t�F�[�X�N���X�i�悭�킩���ĂȂ��j
/// </summary>
class IObjectToManager
{
public:
	virtual void BaseUpdate() = 0;
	virtual void BaseDraw() = 0;
	virtual TObjectParam GetParam() = 0;

	virtual ~IObjectToManager() {}

};