#pragma once
#include "MeshBuffer.h"
#include "Shader.h"
#include "ConstantBuffer.h"
#include <vector>
#include <DirectXMath.h>

class GeometoryPolyline
{
public:
	struct Point
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 normal;
		float width;
	};
	struct Vertex
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT2 uv;
		DirectX::XMFLOAT4 color;
	};
public:
	GeometoryPolyline(int pointNum);
	~GeometoryPolyline();
	void Draw();

	void SetPoint(int index, Point point);
	void PushPoint(Point point);
	Point GetPoint(int index);
	int GetPointNum();

	void SetTexture(ID3D11ShaderResourceView* pTex);
	void SetView(DirectX::XMFLOAT4X4 view);
	void SetProjection(DirectX::XMFLOAT4X4 proj);
	void SetPixelShader(PixelShader* pPS);
	void SetDefaultPixelShader();

private:
	void CalcVertex();

private:
	std::vector<Point> m_points;
	MeshBuffer* m_pMesh;
	Vertex* m_pVertices;
	ID3D11ShaderResourceView* m_pTexture;
	VertexShader* m_pVS;
	PixelShader* m_pPS;
	DirectX::XMFLOAT4X4 m_matrix[2];
	ConstantBuffer* m_pBuf;
	PixelShader* m_pDefPS;
};