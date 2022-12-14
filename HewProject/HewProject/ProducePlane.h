#pragma once
#include <vector>
#include "DirectXTex/DirectXTex.h"

class ProducePlane
{
public:
	void SetRect(DirectX::XMFLOAT3 pos1, DirectX::XMFLOAT3 pos2);//矩形を選択して四角形を設定
	void SetCenterPos(DirectX::XMFLOAT3 center, DirectX::XMFLOAT2 size, DirectX::XMFLOAT3 rot);// 中心点などを指定して描画
	void SetEnable(bool isDraw);// 描画するか

private:
};