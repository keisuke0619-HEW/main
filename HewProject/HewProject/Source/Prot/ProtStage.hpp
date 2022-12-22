#pragma once
#include <TerrainBase.hpp>
#include <ProtEnemyManager.hpp>
#include <memory>
#include <ProducePlane.h>

class CProtScene
{
public:
	struct StageData
	{
		// �X�e�[�W�̉���
		float sizeX;
		// �X�e�[�W�̉��s
		float sizeZ;
	};
public:
	CProtScene();
	~CProtScene();

	void Update();
	void Draw();
private:
	StageData m_stageData;
	CTerrainBase* m_terrain;
	std::unique_ptr<CProtEnemyManager> m_enemyManager;
	ProducePlane* m_producePlane;
};