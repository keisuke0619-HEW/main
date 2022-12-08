#pragma once
#include <DirectX.h>
#include <MeshBuffer.h>
#include <DirectXMath.h>
#include <Shader.h>
#include <memory>
#include <ConstantBuffer.h>
#include <Geometory.h>

struct TTerrainData
{
	// グリッドX
	int gridX;
	// グリッドY
	int gridY;
	// 総数
	int count;
	// それぞれの高さ
	float* height;
};

struct TerrainVertex
{
	float pos[3];
	float uv[2];
};

// 地形データ
class CTerrainBase
{
public:
	CTerrainBase(const char* src, float width, float depth);
	~CTerrainBase();

	virtual void Update();
	virtual void Draw();
private:
	bool LoadTerrain(const char* src);
	void SetTerrainVertex();
	TTerrainData m_data;
	float m_width;
	float m_depth;

	DirectX::XMFLOAT4X4 m_geometoryMat[3];
	TGeometoryColor m_terrainColor;
	std::unique_ptr<MeshBuffer> m_mesh;
	std::unique_ptr<VertexShader> m_vs;
	std::unique_ptr<PixelShader> m_ps;
	std::unique_ptr<ConstantBuffer> m_wvp;
	std::unique_ptr<ConstantBuffer> m_colorCB;
	TerrainVertex* m_vtx;
};