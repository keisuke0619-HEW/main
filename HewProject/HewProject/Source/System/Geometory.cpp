#include "Geometory.h"
#include "MeshBuffer.h"
#include "Shader.h"
#include "ConstantBuffer.h"
#include <memory>
//--- マクロ
#define GEOMETORY_SAFE_DELETE(p) if(p){delete p; p = nullptr;}

//--- 定数
const int GEOMETORY_SPLIT = 16;
const int GEOMETORY_SPLIT_VTX_X = GEOMETORY_SPLIT + 1;
const int GEOMETORY_SPLIT_VTX_Y = GEOMETORY_SPLIT / 2 + 1;
const int GEOMETORY_SPLIT_IDX_X = GEOMETORY_SPLIT;
const int GEOMETORY_SPLIT_IDX_Y = GEOMETORY_SPLIT / 2;

//--- 構造体
struct GeometoryVertex
{
	float pos[3];
	float uv[2];
};

//--- プロトタイプ宣言
void CreateGeometoryBox();
void CreateGeometorySphere();
void CreateGeometoryCylinder();
void CreateGeometoryCapsule();
void CreateGeometoryCone();
void CreateGeometoryShader();
void CreateGeometoryConstantBuffer();
void UpdateGeometoryMatrix();

void SetPolygon(std::shared_ptr<GeometoryVertex>* vtxBuffer, std::shared_ptr<int>* idxBuffer, int* vtxNumBuf, int* idxNumBuf, int level, bool isLoopX = false, bool isLoopY = false);

//--- グローバル変数
MeshBuffer* g_pGeometoryBox;
MeshBuffer* g_pGeometorySphere;
MeshBuffer* g_pGeometoryCylinder;
MeshBuffer* g_pGeometoryCapsule;
MeshBuffer* g_pGeometoryCone;
VertexShader* g_pGeometoryVS;
PixelShader* g_pGeometoryPS;
ConstantBuffer* g_pGeometoryWVP;
DirectX::XMFLOAT4X4 g_geometoryMat[3];
DirectX::XMFLOAT3 g_geometoryTransform[3];

HRESULT InitGeometory()
{
	CreateGeometoryShader();
	CreateGeometoryConstantBuffer();
	CreateGeometoryBox();
	CreateGeometorySphere();
	CreateGeometoryCylinder();
	CreateGeometoryCapsule();
	CreateGeometoryCone();
	return S_OK;
}
void UninitGeometory()
{
	GEOMETORY_SAFE_DELETE(g_pGeometoryCone);
	GEOMETORY_SAFE_DELETE(g_pGeometoryCapsule);
	GEOMETORY_SAFE_DELETE(g_pGeometoryCylinder);
	GEOMETORY_SAFE_DELETE(g_pGeometorySphere);
	GEOMETORY_SAFE_DELETE(g_pGeometoryBox);
	GEOMETORY_SAFE_DELETE(g_pGeometoryPS);
	GEOMETORY_SAFE_DELETE(g_pGeometoryVS);
}
void SetGeometoryTranslate(float x, float y, float z)
{
	g_geometoryTransform[0] = DirectX::XMFLOAT3(x, y, z);
}
void SetGeometoryRotation(float x, float y, float z)
{
	g_geometoryTransform[1] = DirectX::XMFLOAT3(x, y, z);
}
void SetGeometoryScaling(float x, float y, float z)
{
	g_geometoryTransform[2] = DirectX::XMFLOAT3(x, y, z);
}
void SetGeometoryVPMatrix(DirectX::XMFLOAT4X4 view, DirectX::XMFLOAT4X4 proj)
{
	g_geometoryMat[1] = view;
	g_geometoryMat[2] = proj;
}
void DrawBox()
{
	UpdateGeometoryMatrix();
	g_pGeometoryVS->Bind();
	g_pGeometoryPS->Bind();
	g_pGeometoryWVP->BindVS(0);
	g_pGeometoryBox->Draw();
}
void DrawSphere()
{
	UpdateGeometoryMatrix();
	g_pGeometoryVS->Bind();
	g_pGeometoryPS->Bind();
	g_pGeometoryWVP->BindVS(0);
	g_pGeometorySphere->Draw();
}
void DrawCylinder()
{
	UpdateGeometoryMatrix();
	g_pGeometoryVS->Bind();
	g_pGeometoryPS->Bind();
	g_pGeometoryWVP->BindVS(0);
	g_pGeometoryCylinder->Draw();
}
void DrawCone()
{
	UpdateGeometoryMatrix();
	g_pGeometoryVS->Bind();
	g_pGeometoryPS->Bind();
	g_pGeometoryWVP->BindVS(0);
	g_pGeometoryCone->Draw();
}
void DrawCapsule()
{
}
void DrawArrow()
{
}


void CreateGeometoryBox()
{
	GeometoryVertex vtx[] =
	{
		// -z
		{{-0.5f, 0.5f,-0.5f}, {0.0f, 0.0f}},
		{{ 0.5f, 0.5f,-0.5f}, {1.0f, 0.0f}},
		{{-0.5f,-0.5f,-0.5f}, {0.0f, 1.0f}},
		{{ 0.5f,-0.5f,-0.5f}, {1.0f, 1.0f}},
		// +z
		{{ 0.5f, 0.5f, 0.5f}, {0.0f, 0.0f}},
		{{-0.5f, 0.5f, 0.5f}, {1.0f, 0.0f}},
		{{ 0.5f,-0.5f, 0.5f}, {0.0f, 1.0f}},
		{{-0.5f,-0.5f, 0.5f}, {1.0f, 1.0f}},
		// -x
		{{-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f}},
		{{-0.5f, 0.5f,-0.5f}, {1.0f, 0.0f}},
		{{-0.5f,-0.5f, 0.5f}, {0.0f, 1.0f}},
		{{-0.5f,-0.5f,-0.5f}, {1.0f, 1.0f}},
		// +x
		{{ 0.5f, 0.5f,-0.5f}, {0.0f, 0.0f}},
		{{ 0.5f, 0.5f, 0.5f}, {1.0f, 0.0f}},
		{{ 0.5f,-0.5f,-0.5f}, {0.0f, 1.0f}},
		{{ 0.5f,-0.5f, 0.5f}, {1.0f, 1.0f}},
		// -y
		{{-0.5f,-0.5f,-0.5f}, {0.0f, 0.0f}},
		{{ 0.5f,-0.5f,-0.5f}, {1.0f, 0.0f}},
		{{-0.5f,-0.5f, 0.5f}, {0.0f, 1.0f}},
		{{ 0.5f,-0.5f, 0.5f}, {1.0f, 1.0f}},
		// +y
		{{-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f}},
		{{ 0.5f, 0.5f, 0.5f}, {1.0f, 0.0f}},
		{{-0.5f, 0.5f,-0.5f}, {0.0f, 1.0f}},
		{{ 0.5f, 0.5f,-0.5f}, {1.0f, 1.0f}},
	};
	int idx[] =
	{
		0,1,2, 1,3,2,// -z
		4,5,6, 6,5,7,// +z
		8,9,10, 10,9,11,// -x
		12,13,14, 14,13,15,// +x
		16,17,18, 18,17,19,// -y
		20,21,22, 22,21,23,// +y
	};

	int men = 6;
	MeshBuffer::Description desc = {};
	desc.pVtx = vtx;
	desc.vtxCount = 4 * 6;
	desc.vtxSize = sizeof(GeometoryVertex);
	desc.pIdx = idx;
	desc.idxCount = 6 * men;
	desc.idxSize = sizeof(int);
	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	g_pGeometoryBox = new MeshBuffer(desc);
}
void CreateGeometorySphere()
{
	//// 分割数
	//const int level = 16;
	//// 頂点情報
	//const int vtxNum = level * level;
	//GeometoryVertex vtx[vtxNum];
	//// インデックス情報
	//const int idxNum = 3 * (level - 1) * (level - 1) * 2;
	//int idx[idxNum] = {};
	////--- 頂点設定 ---//
	//for (int i = 0; i < vtxNum; i++)
	//{
	//	vtx[i] = { { -0.5f + ((float)(i % level) / (level - 1)), -0.5f + ((float)(i / level) / (level - 1)), 0}, {(float)(i % level) / (level - 1),(float)(i / level) / (level - 1)} };
	//}
	////--- インデックス設定 ---//
	//int idxX = 0;
	//int idxY = 0;
	//for (int i = 0; i < idxNum; i++)
	//{
	//	if (i == idxNum / 2)
	//	{
	//		idxX = 1;
	//		idxY = 0;
	//	}
	//	idx[i] = level * idxY + idxX;
	//	if (i < idxNum / 2)
	//	{
	//		switch (i % 3)
	//		{
	//		case 0:
	//			idxX++;
	//			break;
	//		case 1:
	//			idxX--;
	//			idxY++;
	//			break;
	//		case 2:
	//			idxX++;
	//			idxY--;
	//			if (idxX == level - 1)
	//			{
	//				idxX = 0;
	//				idxY++;
	//			}
	//			break;
	//		}
	//	}
	//	else
	//	{
	//		switch (i % 3)
	//		{
	//		case 0:
	//			idxY++;
	//			break;
	//		case 1:
	//			idxX--;
	//			break;
	//		case 2:
	//			idxX += 2;
	//			idxY--;
	//			if (idxX > level - 1)
	//			{
	//				idxX = 1;
	//				idxY++;
	//			}
	//			break;
	//		}
	//	}
	//}
	//--- 登録 ---//
	std::shared_ptr<GeometoryVertex> vtx;
	std::shared_ptr<int> idx;
	int vtxNum;
	int idxNum;
	int level = 6;
	SetPolygon(&vtx, &idx, &vtxNum, &idxNum, level, true);

	const float degtorad = 3.1415f / 180;
	float angleXZ = 0;
	float angleXY = 90;
	//for (int y = 0; y < level; y++)
	//{
	//	for (int x = 0; x < level; x++)
	//	{
	//		auto ptr = vtx.get();
	//		ptr[y * level + x % level].pos[0] = cos(angleXZ * degtorad) * cos(angleXY * degtorad) * 0.5f;	//x
	//		ptr[y * level + x % level].pos[1] = sinf(angleXY * degtorad) * 0.5f;	//y
	//		ptr[y * level + x % level].pos[2] = sinf(angleXZ * degtorad) * cosf(angleXY * degtorad)* 0.5f;	//z
	//		angleXZ += 360.0f / (level - 1);

	//	}
	//	angleXY += 180.0f / (level - 1);
	//}




	MeshBuffer::Description desc = {};
	desc.pVtx = vtx.get();
	desc.vtxCount = vtxNum;
	desc.vtxSize = sizeof(GeometoryVertex);
	desc.pIdx = idx.get();
	desc.idxCount = idxNum;
	desc.idxSize = sizeof(int);
	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	g_pGeometorySphere = new MeshBuffer(desc);

}
void CreateGeometoryCylinder()
{
	//--- 分割数指定 ---//
	const int level = 64;
	//--- 頂点情報 ---//
	const int vtxBottomNum = 2 + level * 2;	// 底面の頂点
	const int vtxSideNum = level * 2 + 2;
	const int vtxNum = vtxBottomNum + vtxSideNum;
	GeometoryVertex vtx[vtxNum];
	//--- インデックス情報--- //
	const int idxBottomNum = level * 2 * 3;
	const int idxSideNum = level * 2 * 3;
	const int idxNum = idxBottomNum + idxSideNum;
	int idx[idxNum];
	//--- 計算情報 ---//
	const float degToRad = 3.1415f / 180.0f;
	float angle = 0;

	//--- 底面 ---//
	vtx[0] = { {0.0f,  0.5f, 0.0f}, {0.5f, 0.5f} };	// 天面の中心
	vtx[1] = { {0.0f, -0.5f, 0.0f}, {0.5f, 0.5f} };	// 天面の中心
	// 頂点
	for (int i = 0; i < level; i++)
	{
		vtx[i + 2] = { {sinf(angle * degToRad) * 0.5f, 0.5f,cosf(angle * degToRad) * 0.5f}, {sinf(angle * degToRad) * 0.5f + 0.5f, cosf(angle * degToRad) * 0.5f + 0.5f} };
		vtx[i + level + 2] = { {sinf(angle * degToRad) * 0.5f,-0.5f,cosf(angle * degToRad) * 0.5f}, {sinf(angle * degToRad) * 0.5f + 0.5f, cosf(angle * degToRad) * 0.5f + 0.5f} };
		angle += 360.0f / level;
	}
	// インデックス
	for (int i = 0; i < level; i++)
	{
		idx[i * 3 + 0] = 0;
		idx[i * 3 + 1] = i + 2;
		idx[i * 3 + 2] = i + 3;

		idx[(i + level) * 3 + 0] = 1;
		idx[(i + level) * 3 + 1] = level + i + 3;
		idx[(i + level) * 3 + 2] = level + i + 2;
	}
	idx[level * 3 - 1] = 2;
	idx[level * 3 * 2 - 2] = level + 2;

	//--- 側面 ---//
	angle = 0;
	// 頂点
	for (int i = 0; i < level; i++)
	{
		GeometoryVertex top = { {sinf(angle * degToRad) * 0.5f, 0.5f,cosf(angle * degToRad) * 0.5f}, {(1.0f / level) * i, 0} };
		GeometoryVertex bottom = { {sinf(angle * degToRad) * 0.5f,-0.5f,cosf(angle * degToRad) * 0.5f}, {(1.0f / level) * i, 1} };
		vtx[vtxBottomNum + (i * 2) + 0] = top;
		vtx[vtxBottomNum + (i * 2) + 1] = bottom;
		angle -= 360.0f / (level);
	}
	vtx[vtxNum - 2] = { {sinf(angle * degToRad) * 0.5f, 0.5f,cosf(angle * degToRad) * 0.5f}, {1.0f, 0} };
	vtx[vtxNum - 1] = { {sinf(angle * degToRad) * 0.5f,-0.5f,cosf(angle * degToRad) * 0.5f}, {1.0f, 1} };
	// インデックス
	for (int i = 0; i < level; i++)
	{
		idx[idxBottomNum + i * 3 + 0] = vtxBottomNum + (i * 2) + 0;
		idx[idxBottomNum + i * 3 + 1] = vtxBottomNum + (i * 2) + 2;
		idx[idxBottomNum + i * 3 + 2] = vtxBottomNum + (i * 2) + 1;

		idx[idxBottomNum + (i + level) * 3 + 0] = vtxBottomNum + (i * 2) + 1;
		idx[idxBottomNum + (i + level) * 3 + 1] = vtxBottomNum + (i * 2) + 2;
		idx[idxBottomNum + (i + level) * 3 + 2] = vtxBottomNum + (i * 2) + 3;
	}




	//--- 描画 ---//
	MeshBuffer::Description desc = {};
	desc.pVtx = vtx;
	desc.vtxCount = vtxNum;
	desc.vtxSize = sizeof(GeometoryVertex);
	desc.pIdx = idx;
	desc.idxCount = idxNum;
	desc.idxSize = sizeof(int);
	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	g_pGeometoryCylinder = new MeshBuffer(desc);

}
void CreateGeometoryCone()
{
	//--- 分割数指定 ---//
	const int level = 16;
	//--- 頂点情報 ---//
	const int vtxBottomNum = 2 + level;	// 底面の頂点
	const int vtxSideNum = level + 1;
	const int vtxNum = vtxBottomNum + vtxSideNum;
	GeometoryVertex vtx[vtxNum];
	//--- インデックス情報--- //
	const int idxBottomNum = level * 3;
	const int idxSideNum = level * 3;
	const int idxNum = idxBottomNum + idxSideNum;
	int idx[idxNum];
	//--- 計算情報 ---//
	const float degToRad = 3.1415f / 180.0f;
	float angle = 0;

	//--- 底面 ---//
	vtx[0] = { {0.0f,  0.5f, 0.0f}, {0.5f, 0.0f} };	// 天面の中心
	vtx[1] = { {0.0f, -0.5f, 0.0f}, {0.5f, 0.5f} };	// 天面の中心
	// 頂点
	for (int i = 0; i < level; i++)
	{
		vtx[i + 2] = { {sinf(angle * degToRad) * 0.5f, -0.5f,cosf(angle * degToRad) * 0.5f}, {sinf(angle * degToRad) * 0.5f + 0.5f, cosf(angle * degToRad) * 0.5f + 0.5f} };
		angle += 360.0f / level;
	}
	// インデックス
	for (int i = 0; i < level; i++)
	{
		idx[i * 3 + 0] = 1;
		idx[i * 3 + 1] = i + 3;
		idx[i * 3 + 2] = i + 2;
	}
	idx[level * 3 - 2] = 2;

	//--- 側面 ---//
	angle = 0;
	// 頂点
	for (int i = 0; i < level; i++)
	{
		GeometoryVertex bottom = { {sinf(angle * degToRad) * 0.5f,-0.5f,cosf(angle * degToRad) * 0.5f}, {(1.0f / level) * i, 1} };
		vtx[vtxBottomNum + i] = bottom;
		angle += 360.0f / (level);
	}
	vtx[vtxNum - 1] = { {sinf(angle * degToRad) * 0.5f,-0.5f,cosf(angle * degToRad) * 0.5f}, {1, 1} };
	// インデックス
	for (int i = 0; i < level; i++)
	{
		idx[idxBottomNum + i * 3 + 0] = 0;
		idx[idxBottomNum + i * 3 + 1] = vtxBottomNum + i + 1;
		idx[idxBottomNum + i * 3 + 2] = vtxBottomNum + i + 2;
	}
	idx[idxNum - 1] = vtxBottomNum + 1;
	//--- 描画 ---//
	MeshBuffer::Description desc = {};
	desc.pVtx = vtx;
	desc.vtxCount = vtxNum;
	desc.vtxSize = sizeof(GeometoryVertex);
	desc.pIdx = idx;
	desc.idxCount = idxNum;
	desc.idxSize = sizeof(int);
	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	g_pGeometoryCone = new MeshBuffer(desc);

}
void CreateGeometoryCapsule()
{
}

void CreateGeometoryShader()
{
	const char* GeometoryVS = R"EOT(
struct VS_IN {
	float3 pos : POSITION0;
	float2 uv : TEXCOORD0;
};
struct VS_OUT {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
	float4 wPos : TEXCOORD1;
};
cbuffer WVP : register(b0) {
	float4x4 world;
	float4x4 view;
	float4x4 proj;
};
VS_OUT main(VS_IN vin) {
	VS_OUT vout;
	vout.pos = float4(vin.pos, 1.0f);
	vout.pos = mul(vout.pos, world);
	vout.wPos = vout.pos;
	vout.pos = mul(vout.pos, view);
	vout.pos = mul(vout.pos, proj);
	vout.uv = vin.uv;
	return vout;
})EOT";
	const char* GeometoryPS = R"EOT(
struct PS_IN {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
	float4 wPos : TEXCOORD1;	
};
float4 main(PS_IN pin) : SV_TARGET
{
	float4 color = float4(1,1,1,1);
	
	float2 mGrid = floor(abs(pin.uv) * 2.0f);
	float2 sGrid = floor(abs(pin.uv) * 8.0f);

	float mid = fmod(mGrid.x + mGrid.y, 2.0f);
	float small = fmod(sGrid.x + sGrid.y, 2.0f);

	color.rgb = ((mid * 0.1f) * small + 0.45f) + (1 - small) * 0.05f;
	return color;
})EOT";

	g_pGeometoryVS = new VertexShader();
	_ASSERT_EXPR(SUCCEEDED(g_pGeometoryVS->Compile(GeometoryVS)),
		L"create failed geometory vertex shader.");
	g_pGeometoryPS = new PixelShader();
	_ASSERT_EXPR(SUCCEEDED(g_pGeometoryPS->Compile(GeometoryPS)),
		L"create failed geometory pixel shader.");
}
void CreateGeometoryConstantBuffer()
{
	g_pGeometoryWVP = new ConstantBuffer();
	g_pGeometoryWVP->Create(sizeof(g_geometoryMat));

	g_geometoryTransform[0] = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_geometoryTransform[1] = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_geometoryTransform[2] = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);

	//SetGeometoryVPMatrix(
	//	DirectX::XMMatrixLookAtLH(DirectX::XMVectorSet(3, 3, -3, 1), DirectX::XMVectorSet(0, 0, 0, 1), DirectX::XMVectorSet(0, 1, 0, 1)),
	//	DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(60.f), 16.f / 9.f, 0.1f, 100.0f)
	//);
	DirectX::XMStoreFloat4x4(&g_geometoryMat[0], DirectX::XMMatrixIdentity());
	g_pGeometoryWVP->Write(g_geometoryMat);
}
void UpdateGeometoryMatrix()
{
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(g_geometoryTransform[0].x, g_geometoryTransform[0].y, g_geometoryTransform[0].z);
	DirectX::XMMATRIX Rx = DirectX::XMMatrixRotationX(g_geometoryTransform[1].x);
	DirectX::XMMATRIX Ry = DirectX::XMMatrixRotationY(g_geometoryTransform[1].y);
	DirectX::XMMATRIX Rz = DirectX::XMMatrixRotationZ(g_geometoryTransform[1].z);
	DirectX::XMMATRIX S  = DirectX::XMMatrixScaling(g_geometoryTransform[2].x, g_geometoryTransform[2].y, g_geometoryTransform[2].z);
	DirectX::XMMATRIX mat = S * Rx * Ry * Rz * T;
	mat = DirectX::XMMatrixTranspose(mat);
	DirectX::XMStoreFloat4x4(&g_geometoryMat[0], mat);
	g_pGeometoryWVP->Write(g_geometoryMat);
}

#include <iostream>
#include <stdio.h>

void SetPolygon(std::shared_ptr<GeometoryVertex>* vtxBuffer, std::shared_ptr<int>* idxBuffer, int* vtxNumBuf, int* idxNumBuf, int level, bool isLoopX, bool isLoopY)
{
	// 頂点情報
	const int levelX = isLoopX ? level + 1 : level;
	const int levelY = isLoopY ? level + 1 : level;
	const int vtxNum = levelX * levelY;
	std::shared_ptr<GeometoryVertex>vtx(new GeometoryVertex[vtxNum], std::default_delete<GeometoryVertex[]>());
	// インデックス情報
	const int idxNum = 3 * (levelX - 1) * (levelY - 1) * 2;
	std::shared_ptr<int> idx(new int[idxNum], std::default_delete<int[]>());

	//--- 頂点設定 ---//
	for (int i = 0; i < vtxNum; i++)
	{
		(vtx.get()[i]) = { {(0.5f - (float)(i % levelX) / (levelX - 1)), (0.5f - (float)(i / levelX) / (levelX - 1)), 0}, {(float)(i % levelX) / (levelX - 1),(float)(i / levelX) / (levelX - 1)} };
	}
	//--- インデックス設定 ---//
	int idxX = 0;
	int idxY = 0;
	for (int i = 0; i < idxNum; i++)
	{
		if (i == idxNum / 2)
		{
			idxX = 1;
			idxY = 0;
		}
		idx.get()[i] = levelX * idxY + idxX;
		if (i < idxNum / 2)
		{
			switch (i % 3)
			{
			case 0:
				idxX++;
				break;
			case 1:
				idxX--;
				idxY++;
				break;
			case 2:
				idxX++;
				idxY--;
				if (idxX == levelX - 1)
				{
					idxX = 0;
					idxY++;
				}
				break;
			}
		}
		else
		{
			switch (i % 3)
			{
			case 0:
				idxY++;
				break;
			case 1:
				idxX--;
				break;
			case 2:
				idxX += 2;
				idxY--;
				if (idxX > levelX - 1)
				{
					idxX = 1;
					idxY++;
				}
				break;
			}
		}
	}

	*vtxBuffer = vtx;
	*idxBuffer = idx;
	*vtxNumBuf = vtxNum;
	*idxNumBuf = idxNum;

	//debagu
	{
		FILE* fp = fopen("vtxData.csv", "wt");
		fprintf(fp, "ID,X,Y,U,V\n");
		for (int i = 0; i < vtxNum; i++)
		{
			fprintf(fp, "%d,%f,%f,%f,%f\n", i, vtx.get()[i].pos[0], vtx.get()[i].pos[1],  vtx.get()[i].uv[0], vtx.get()[i].uv[1]);
		}
		fclose(fp);
	}


	//// 頂点情報
	//const int vtxNum = level * level;
	//std::shared_ptr<GeometoryVertex>vtx(new GeometoryVertex[vtxNum], std::default_delete<GeometoryVertex[]>());
	//// インデックス情報
	//const int idxNum = 3 * (level - 1) * (level - 1) * 2;
	//std::shared_ptr<int> idx(new int[idxNum], std::default_delete<int[]>());

	////--- 頂点設定 ---//
	//for (int i = 0; i < vtxNum; i++)
	//{
	//	(vtx.get()[i]) = { {(0.5f - (float)(i % level) / (level - 1)), (0.5f - (float)(i / level) / (level - 1)), 0}, {(float)(i % level) / (level - 1),(float)(i / level) / (level - 1)} };
	//}
	////--- インデックス設定 ---//
	//int idxX = 0;
	//int idxY = 0;
	//for (int i = 0; i < idxNum; i++)
	//{
	//	if (i == idxNum / 2)
	//	{
	//		idxX = 1;
	//		idxY = 0;
	//	}
	//	idx.get()[i] = level * idxY + idxX;
	//	if (i < idxNum / 2)
	//	{
	//		switch (i % 3)
	//		{
	//		case 0:
	//			idxX++;
	//			break;
	//		case 1:
	//			idxX--;
	//			idxY++;
	//			break;
	//		case 2:
	//			idxX++;
	//			idxY--;
	//			if (idxX == level - 1)
	//			{
	//				idxX = 0;
	//				idxY++;
	//			}
	//			break;
	//		}
	//	}
	//	else
	//	{
	//		switch (i % 3)
	//		{
	//		case 0:
	//			idxY++;
	//			break;
	//		case 1:
	//			idxX--;
	//			break;
	//		case 2:
	//			idxX += 2;
	//			idxY--;
	//			if (idxX > level - 1)
	//			{
	//				idxX = 1;
	//				idxY++;
	//			}
	//			break;
	//		}
	//	}
	//}

	//*vtxBuffer = vtx;
	//*idxBuffer = idx;
	//*vtxNumBuf = vtxNum;
	//*idxNumBuf = idxNum;
}
