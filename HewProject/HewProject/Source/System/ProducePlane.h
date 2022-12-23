#ifndef __PRODUCEPLANE_H__
#define __PRODUCEPLANE_H__

#include "DirectX.h"
#include "Sprite.h"
#include "DirectXTex/Texture.h"
#include "DirectXTex/DirectXTex.h"
#include <Geometory.h>
#include <ConstantBuffer.h>

class ProducePlane
{
public:
	ProducePlane(const char*);
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
		DirectX::XMFLOAT3 pos3, DirectX::XMFLOAT3 pos4);//矩形を選択して四角形を設定
	void SetProducePlaneInformation(DirectX::XMFLOAT3 center, DirectX::XMFLOAT3 size, DirectX::XMFLOAT3 rot);// 描画に必要な情報を設定
	void SetEnable(bool isDraw);// 描画するか
	void SetColor(float r, float g, float b, float a = 255);
	void SetColor255(int r, int g, int b, int a = 255);

private:
	ID3D11ShaderResourceView* m_pPicture;	// 画像
	DirectX::XMFLOAT3 m_pos;				// 画像の座標
	DirectX::XMFLOAT3 m_size;				// 画像のサイズ
	DirectX::XMFLOAT3 m_rot;				// 画像の角度
	DirectX::XMFLOAT4X4 m_view;				// ビュー行列
	DirectX::XMFLOAT4X4 m_proj;				// プロジェクション行列
	DirectX::XMFLOAT4 m_color;

	MeshBuffer* m_pProducePlane;
	ConstantBuffer* m_pConstant;
	ConstantBuffer* m_pConstantWVP;
	DirectX::XMFLOAT4X4 m_PlaneMat[3];
//	DirectX::XMFLOAT3 m_PlaneTransform[3];
	bool m_IsDarw;
};

#endif // __PRODUCEPLANE_H__