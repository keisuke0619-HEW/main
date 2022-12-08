#include <ProtStage.hpp>
#include <stdio.h>
#include <Windows.h>
#include <Geometory.h>
#include <Camera.hpp>
// Stage00.cpp���Q�l�ɃW�I���g���[�ō쐬
CProtScene::CProtScene()
{
	m_stageData = { 1, 1 };
	// �����œǂݍ��݁����������[�N����
	FILE* fp = fopen("Assets/Data/Test.dat", "rb");
	if (fp == nullptr)
	{
		MessageBox(NULL, "�X�e�[�W�ǂݍ��݃G���[", "CProtScene�R���X�g���N�^", MB_OK);
	}
	else
	{
		fread(&m_stageData, sizeof(StageData), 1, fp);
		fclose(fp);
	}
	m_terrain = new CTerrainBase("Assets/Data/TestTerrain.dat", 100, 100);
	m_enemyManager.reset(new CProtEnemyManager());
}

CProtScene::~CProtScene()
{
}

void CProtScene::Update()
{
	// �X�e�[�W�̃A�b�v�f�[�g
	m_enemyManager->Update();
}

void CProtScene::Draw()
{
	// �X�e�[�W�̃h���[
	SetGeometoryVPMatrix(CCameraBase::GetPrimaryViewMatrix(), CCameraBase::GetPrimaryProjectionMatrix());
	SetGeometoryTranslate(0,0,0);
	SetGeometoryScaling(m_stageData.sizeX,1, m_stageData.sizeZ);
	SetGeometoryRotation(0,0,0);
	SetColorPS(true, 0.7f, 0.7f, 0.7f, 0, m_stageData.sizeX, m_stageData.sizeZ);
	DrawBox();


	// ��
	const float wallHeight = 10.0f;
	SetGeometoryTranslate(m_stageData.sizeX / 2 + 0.5f, wallHeight / 2 + 0.5f,0);
	SetGeometoryScaling(wallHeight,1,m_stageData.sizeZ + 2);
	SetGeometoryRotation(0,0,3.14f / 2);
	SetColorPS(true, 0.3f, 0.76f, 1.0f, 0, wallHeight, m_stageData.sizeX);
	DrawBox();

	SetGeometoryTranslate(-m_stageData.sizeX / 2 - 0.5f, wallHeight / 2 + 0.5f,0);
	SetGeometoryRotation(0,0,3.14f / 2);
	DrawBox();

	SetGeometoryTranslate(0, wallHeight / 2 + 0.5f, m_stageData.sizeZ / 2 + 0.5f);
	SetGeometoryScaling(m_stageData.sizeX + 2,1, wallHeight);
	SetGeometoryRotation(3.14f / 2,0,0);
	SetColorPS(true, 0.3f, 0.76f, 1.0f, 0, m_stageData.sizeX, wallHeight);
	DrawBox();

	SetGeometoryTranslate(0, wallHeight / 2 + 0.5f, -m_stageData.sizeZ / 2 - 0.5f);
	SetGeometoryRotation(3.14f / 2,0,0);
	DrawBox();

	//m_terrain->Draw();


	SetColorPS(false);
}
