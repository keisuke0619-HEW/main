#pragma once
#include "ObjectBase.hpp"
#include "DirectXTex/DirectXTex.h"

class ProducePlane
{
public:
	struct Plane
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 centerpos;
		DirectX::XMFLOAT3 rot;
		DirectX::XMFLOAT2 size;
	};
	void SetRect(DirectX::XMFLOAT3 pos1, DirectX::XMFLOAT3 pos2);//��`��I�����Ďl�p�`��ݒ�
	void SetCenterPos(DirectX::XMFLOAT3 center, DirectX::XMFLOAT2 size, DirectX::XMFLOAT3 rot);// ���S�_�Ȃǂ��w�肵�ĕ`��
	void SetEnable(bool isDraw);// �`�悷�邩

private:
//	Plane* m_pPlane;
	PlaneData* m_pPlane;
	bool m_IsDarw;
};