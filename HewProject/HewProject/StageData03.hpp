#pragma once
#include <TerrainBase.hpp>
#include <ProtEnemyManager.hpp>
#include <memory>
#include <ProducePlane.h>
#include<ObjectBase.hpp>
#include <ISceneBase.hpp>

class CStageData03
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
	CStageData03(Data* data);
	~CStageData03();

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