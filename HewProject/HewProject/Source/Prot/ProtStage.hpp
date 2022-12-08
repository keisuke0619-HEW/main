#pragma once
#include <TerrainBase.hpp>
#include <ProtEnemyManager.hpp>
#include <memory>
class CProtScene
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
	CProtScene();
	~CProtScene();

	void Update();
	void Draw();
private:
	StageData m_stageData;
	CTerrainBase* m_terrain;
	std::unique_ptr<CProtEnemyManager> m_enemyManager;
};