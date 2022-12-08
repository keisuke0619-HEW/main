#include "TerrainBase.hpp"
#include <stdio.h>


CTerrainBase::CTerrainBase(const char* src, float width, float depth)
{
	LoadTerrain(src);
	m_width = width;
	m_depth = depth;
	m_vs.reset(new VertexShader());
	m_ps.reset(new PixelShader());
	m_wvp.reset(new ConstantBuffer());
	m_colorCB.reset(new ConstantBuffer());
	m_wvp->Create(sizeof(m_geometoryMat));
	m_colorCB->Create(sizeof(m_terrainColor));
	

}

CTerrainBase::~CTerrainBase()
{
	delete[] m_vtx;
	delete[] m_data.height;
}

void CTerrainBase::Update()
{

}

void CTerrainBase::Draw()
{

	(*m_vs).Bind();
	(*m_ps).Bind();
	(*m_wvp).BindVS(0);
	(*m_mesh).Draw();
}

bool CTerrainBase::LoadTerrain(const char* src)
{
	FILE* fp = fopen(src, "rb");
	if(fp == nullptr)
		return false;
	fread(&(m_data.gridX), sizeof(int), 1, fp);
	fread(&(m_data.gridY), sizeof(int), 1, fp);
	fread(&(m_data.count), sizeof(int), 1, fp);
	m_data.height = new float[m_data.count];
	fread((m_data.height), sizeof(float), m_data.count, fp);
	fclose(fp);


	// 値の読み込みまではできているので、地形を生成するところからお願いします。

	//SetTerrainVertex();
}

void CTerrainBase::SetTerrainVertex()
{
	// 頂点情報
	// インデックス情報
	const int idxNum = 10;//3 * (m_data.gridX - 1) * (m_data.gridY - 1) * 2;
	int* idx;

	//--- 頂点設定 ---//
	m_vtx = new TerrainVertex[m_data.count];

	for (int i = 0; i < m_data.count; i++)
	{
		m_vtx[i] =
		{
			{
				0.5f - ((float)(i % m_data.gridX) / (m_data.gridX - 1)),
				0.5f - ((float)(i / m_data.gridX) / (m_data.gridX - 1)),
				0.0f
			},
			{
				(float)(i % m_data.gridX) / (m_data.gridX - 1),
				(float)(i / m_data.gridX) / (m_data.gridX - 1)
			}
		};
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
		idx[i] = m_data.gridX * idxY + idxX;		// エラー
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
				if (idxX == m_data.gridX - 1)
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
				if (idxX > m_data.gridX - 1)
				{
					idxX = 1;
					idxY++;
				}
				break;
			}
		}
	}

	MeshBuffer::Description desc = {};
	desc.pVtx = m_vtx;
	desc.vtxCount = m_data.count;
	desc.vtxSize = sizeof(TerrainVertex);
	desc.pIdx = idx;
	desc.idxCount = idxNum;
	desc.idxSize = sizeof(int);
	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	m_mesh.reset(new MeshBuffer(desc));


	delete idx;
}
