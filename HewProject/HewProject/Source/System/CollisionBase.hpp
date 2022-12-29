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

	/// �I�u�W�F�N�g(Shpire)�ƃI�u�W�F�N�g(Shpire)�̓����蔻��
	bool IsCollisionShpire(TObjectParam obj1, TObjectParam obj2);

	/// �I�u�W�F�N�g(Shpire)�ƃI�u�W�F�N�g(Ray)�̓����蔻��
	bool IsCollisionShpireRay(TObjectParam obj1, TObjectParam obj2);

	/// �I�u�W�F�N�g(Shpire)�ƃI�u�W�F�N�g(Plane)�̓����蔻��
	bool IsCollisionShpirePlane(TObjectParam obj1, TObjectParam obj2);

	/// �I�u�W�F�N�g(Ray)�ƃI�u�W�F�N�g(Ray)�̓����蔻��
	bool IsCollisionRay(TObjectParam obj1, TObjectParam obj2);

	/// �I�u�W�F�N�g(Ray)�ƃI�u�W�F�N�g(Plane)�̓����蔻��
	bool IsCollisionRayPlane(TObjectParam obj1, TObjectParam obj2);

	/// �I�u�W�F�N�g(Plane)�ƃI�u�W�F�N�g(Plane)�̓����蔻��
	bool IsCollisionPlane(TObjectParam obj1, TObjectParam obj2);

	/// �I�u�W�F�N�g(Ray)�ƃI�u�W�F�N�g(Plane)�̓����蔻�� (�g�p�񐄏�)
	DirectX::XMFLOAT3 GetTargetPlane(TObjectParam obj1, TObjectParam obj2);
}