#pragma once

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
};