#pragma once
#include <IObjectBase.hpp>

enum ECollisionType
{
	COLLISION_NONE,		// �����蔻����g�p���Ȃ�
	COLLISION_BOX,		// ���̓����蔻��
	COLLISION_SPHIRE,	// ���̓����蔻��
	// �V���ɓ����蔻��̎�ނ����ꍇ�͂����ɒǉ�����B
};

namespace Utility
{
	/// <summary>
	/// �I�u�W�F�N�g�P�ƂQ���Փ˂��Ă�����True��Ԃ�
	/// </summary>
	/// <param name="obj1">�I�u�W�F�N�g�P�̃f�[�^</param>
	/// <param name="obj2">�I�u�W�F�N�g�Q�̃f�[�^</param>
	/// <returns>�������Ă�����True�E�������Ă��Ȃ�������False</returns>
	bool IsCollision(TObjectParam obj1, TObjectParam obj2);
}