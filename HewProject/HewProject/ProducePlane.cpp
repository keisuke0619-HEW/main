#include "ProducePlane.h"
void ProducePlane::SetRect(DirectX::XMFLOAT3 pos1, DirectX::XMFLOAT3 pos2)
{
	m_pPlane->planeVtx[0] = {	};
	m_pPlane->planeVtx[1] = {	};
	m_pPlane->planeVtx[2] = {	};
	m_pPlane->planeVtx[3] = {	};
}

void ProducePlane::SetCenterPos(DirectX::XMFLOAT3 center, DirectX::XMFLOAT2 size, DirectX::XMFLOAT3 rot)
{
	//m_pPlane = new Plane;

	////	���S�_�Ȃǂ��w�肵�ĕ`��
	//m_pPlane->centerpos = center;
	//m_pPlane->size = size;
	//m_pPlane->rot = rot;



	//->Draw();
}

void ProducePlane::SetEnable(bool isDraw)
{
	if (isDraw)
	{
		//	�`��̃Z�b�g����






		//->Draw();
	}
	else
	{
		return;
	}
}
