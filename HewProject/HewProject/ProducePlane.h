#pragma once
#include "DirectXTex/DirectXTex.h"
#include <Geometory.h>
#include <ConstantBuffer.h>

class ProducePlane
{
public:
	ProducePlane();
	~ProducePlane();
	struct PlaneVertex
	{
		float pos[3];
		float uv[2];
		float size[2];
	};
	struct UVPos
	{
		DirectX::XMFLOAT4 pos[4];
		float luPosX;
		float luPosY;
		float width;
		float height;
	};
	void Draw();
	void SetRect(DirectX::XMFLOAT3 pos1, DirectX::XMFLOAT3 pos2, 
		DirectX::XMFLOAT3 pos3, DirectX::XMFLOAT3 pos4);//��`��I�����Ďl�p�`��ݒ�
	void SetCenterPos(DirectX::XMFLOAT3 center, DirectX::XMFLOAT2 size, DirectX::XMFLOAT3 rot);// ���S�_�Ȃǂ��w�肵�ĕ`��
	void SetEnable(bool isDraw);// �`�悷�邩

private:
	MeshBuffer* m_pProducePlane;
	ConstantBuffer* m_pConstant;
	ConstantBuffer* m_pConstantWVP;
	DirectX::XMFLOAT4X4 m_PlaneMat[3];
//	DirectX::XMFLOAT3 m_PlaneTransform[3];
	bool m_IsDarw;
};