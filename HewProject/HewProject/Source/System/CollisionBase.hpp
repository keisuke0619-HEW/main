#pragma once
#include <IObjectBase.hpp>

struct Triangle
{
	DirectX::XMFLOAT3 p[3];			// �O�p�`�̍��W
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

	/// <summary>
	/// �I�u�W�F�N�g�P�ƂQ���Փ˂��Ă�����True��Ԃ�
	/// </summary>
	/// <param name="obj1">�I�u�W�F�N�g�P�̃f�[�^</param>
	/// <param name="obj2">�I�u�W�F�N�g�Q�̃f�[�^</param>
	/// <returns>�������Ă�����True�E�������Ă��Ȃ�������False</returns>
	bool IsCollisionShpire(TObjectParam obj1, TObjectParam obj2);
 
	/// �I�u�W�F�N�g(Shpire)�ƃI�u�W�F�N�g(Ray)�̓����蔻��
	bool IsCollisionShpireRay(TObjectParam obj1, TObjectParam obj2);

	/// �I�u�W�F�N�g(Shpire)�ƃI�u�W�F�N�g(Plane)�̓����蔻��
	bool IsCollisionShpirePlane(TObjectParam obj1, TObjectParam obj2);

	/// �I�u�W�F�N�g(Ray)�ƃI�u�W�F�N�g(Ray)�̓����蔻��
	bool IsCollisionRay(TObjectParam obj1, TObjectParam obj2);

	/// �I�u�W�F�N�g(Ray)�ƃI�u�W�F�N�g(Plane)�̓����蔻��
	bool IsCollisionRayPlane(TObjectParam obj1, TObjectParam obj2); //

	/// �I�u�W�F�N�g(Plane)�ƃI�u�W�F�N�g(Plane)�̓����蔻��
	bool IsCollisionPlane(TObjectParam obj1, TObjectParam obj2); //

	/// �I�u�W�F�N�g(Ray)�ƃI�u�W�F�N�g(Plane)�̓����蔻�� (�g�p�񐄏�)
	DirectX::XMFLOAT3 GetTargetPlane(TObjectParam obj1, TObjectParam obj2);
}