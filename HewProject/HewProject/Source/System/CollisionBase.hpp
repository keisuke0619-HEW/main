#pragma once
#include <IObjectBase.hpp>

struct Triangle
{
	DirectX::XMFLOAT3 p[3];			// �O�p�`�̍��W
};

namespace Utility
{
	/// �I�u�W�F�N�g(All)�ƃI�u�W�F�N�g(All)�̓����蔻��
	bool IsCollision(TObjectParam obj1, TObjectParam obj2);

	/// �L�����N�^�[���m
	bool IsCollision_C_to_C(TObjectParam obj1, TObjectParam obj2);

	/// �L�����N�^�[�Ə�Q��
	bool IsCollision_C_to_O(TObjectParam obj1, TObjectParam obj2);

	/// �L�����N�^�[�Ɩ�
	bool IsCollision_C_to_P(TObjectParam obj1, TObjectParam obj2);
	
	/// �J�����ƃI�u�W�F�N�g(Plane)�̓����蔻�� (�g�p�񐄏�)
	DirectX::XMFLOAT3 GetTargetPlane(TObjectParam obj1, TObjectParam obj2);
}