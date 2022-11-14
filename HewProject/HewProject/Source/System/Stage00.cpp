#include "Stage00.hpp"
#include <Geometory.h>
#include <math.h>
CStage00::CStage00()
	:m_pBlocks(nullptr)
	,m_blockNum(7)
{
	m_pBlocks = new Info[m_blockNum];

	m_pBlocks[0].pos = { 4.5f, 0.5f, 4.0f };
	m_pBlocks[0].size = { 9, 1, 8 };
	m_pBlocks[0].rot = { 0, 0, 0 };






















	m_pBlocks[1].pos = { 8.0f, 1.5f, 4.0f };
	m_pBlocks[1].size = { 2, 1, 4 };
	m_pBlocks[1].rot = { 0, 0, 0 };
	m_pBlocks[2].pos = { 8.0f, 2.0f, 7.0f };
	m_pBlocks[2].size = { 2, 2, 2 };
	m_pBlocks[2].rot = { 0, 0, 0 };
	m_pBlocks[3].pos = { 3.5f, 2.0f, 6.0f };
	m_pBlocks[3].size = { 7, 2, 4 };
	m_pBlocks[3].rot = { 0, 0, 0 };
	m_pBlocks[4].pos = { 3.0f, 2.5f, 9.5f };
	m_pBlocks[4].size = { 6, 5, 3 };
	m_pBlocks[4].rot = { 0, 0, 0 };
	m_pBlocks[5].pos = { 7.5f, 3.5f, 9.5f };
	m_pBlocks[5].size = { 1, 1, 1 };
	m_pBlocks[5].rot = { 0, 0, 0 };
	const float booxSqrt = sqrtf(powf(2.0f, 2) + powf(2.0f,2));
	m_pBlocks[6].pos = { 1.0f, 3.0f, 8.0f };
	m_pBlocks[6].size = { 2, booxSqrt, booxSqrt };
	m_pBlocks[6].rot = { 3.14f / 4, 0, 0 };





}

CStage00::~CStage00()
{
	delete[] m_pBlocks;
}

void CStage00::Update()
{
}

void CStage00::Draw()
{
	for (int i = 0; i < m_blockNum; i++)
	{
		SetGeometoryTranslate(m_pBlocks[i].pos.x, m_pBlocks[i].pos.y, m_pBlocks[i].pos.z);
		SetGeometoryScaling(m_pBlocks[i].size.x, m_pBlocks[i].size.y, m_pBlocks[i].size.z);
		SetGeometoryRotation(m_pBlocks[i].rot.x, m_pBlocks[i].rot.y, m_pBlocks[i].rot.z);
		DrawBox();
	}
}
