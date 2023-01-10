#pragma once
#include <TerrainBase.hpp>
#include <ProtEnemyManager.hpp>
#include <memory>
#include <ProducePlane.h>
#include<ObjectBase.hpp>

class CStageData01
	:public CObjectBase
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
	CStageData01();
	~CStageData01();

	void Update();
	void Draw();
private:
	StageData m_stageData;
	CTerrainBase* m_terrain;
	std::unique_ptr<CProtEnemyManager> m_enemyManager;
	ProducePlane* m_producePlane;
	std::unique_ptr<ProducePlane> m_wall[4];
};