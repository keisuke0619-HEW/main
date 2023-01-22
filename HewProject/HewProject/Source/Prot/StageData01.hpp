#pragma once
#include <TerrainBase.hpp>
#include <ProtEnemyManager.hpp>
#include <memory>
#include <ProducePlane.h>
#include<ObjectBase.hpp>

class CStageData01
{
public:
	struct StageData
	{
		// ステージの横幅
		float sizeX;
		// ステージの奥行
		float sizeZ;
	};
public:
	CStageData01();
	~CStageData01();

	void Update();
	void Draw();
private:
	CObjectBase*m_Object;
	StageData m_stageData;
	CTerrainBase* m_terrain;
	std::unique_ptr<CProtEnemyManager> m_enemyManager;
	ProducePlane* m_producePlane[12];
	std::unique_ptr<ProducePlane> m_wall[12];
	std::unique_ptr<ProducePlane> m_roof[12];
};