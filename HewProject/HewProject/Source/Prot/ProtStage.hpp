#pragma once

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
};