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

	////	中心点などを指定して描画
	//m_pPlane->centerpos = center;
	//m_pPlane->size = size;
	//m_pPlane->rot = rot;



	//->Draw();
}

void ProducePlane::SetEnable(bool isDraw)
{
	if (isDraw)
	{
		//	描画のセットする






		//->Draw();
	}
	else
	{
		return;
	}
}
