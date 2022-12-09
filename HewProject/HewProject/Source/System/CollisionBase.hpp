#pragma once
#include <IObjectBase.hpp>

// �f�[�^�̎擾
struct Box
{
	DirectX::XMFLOAT3 pos;			//  ���S���W
	DirectX::XMFLOAT3 size;			//  �T�C�Y
	DirectX::XMFLOAT3 rot;			//  ��]
};

struct Shpire
{
	DirectX::XMFLOAT3 pos;			//  ���S���W
	float radius;					//  ���a
};

struct Plane
{
	DirectX::XMFLOAT3 normal;		//	�ʂ̖@��
	DirectX::XMFLOAT3 vtx[4];		//	���_�̍��W
};

struct Ray
{
	DirectX::XMFLOAT3 start;		//	���C�̊J�n�_
	DirectX::XMVECTOR direction;	//	���C�̕���
	float length;					//	���C�̒���
};

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
	bool IsCollisionBoxNoRotation(TObjectParam obj1, TObjectParam obj2);

	/// point���I�u�W�F�N�g(Box,Shpire)�̓����ɂ��邩
	bool IsIncludPoint(DirectX::XMFLOAT3 point, TObjectParam obj);
	
	/// �I�u�W�F�N�g(Box)�ƃI�u�W�F�N�g(Box)�̓����蔻��
	bool IsCollisionBox(TObjectParam obj1, TObjectParam obj2);

	/// �I�u�W�F�N�g(Box)�ƃI�u�W�F�N�g(Shpire)�̓����蔻��
	bool IsCollisionBoxShpire(TObjectParam obj1, TObjectParam obj2);

	/// �I�u�W�F�N�g(Box)�ƃI�u�W�F�N�g(Ray)�̓����蔻��
	bool IsCollisionBoxRay(TObjectParam obj1, TObjectParam obj2); //

	/// �I�u�W�F�N�g(Box)�ƃI�u�W�F�N�g(Plane)�̓����蔻��
	bool IsCollisionBoxPlane(TObjectParam obj1, TObjectParam obj2);	//

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
}