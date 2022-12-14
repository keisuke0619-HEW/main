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
	void SetRect(DirectX::XMFLOAT3 pos1, DirectX::XMFLOAT3 pos2);//矩形を選択して四角形を設定
	void SetCenterPos(DirectX::XMFLOAT3 center, DirectX::XMFLOAT2 size, DirectX::XMFLOAT3 rot);// 中心点などを指定して描画
	void SetEnable(bool isDraw);// 描画するか

private:
//	Plane* m_pPlane;
	PlaneData* m_pPlane;
	bool m_IsDarw;
};