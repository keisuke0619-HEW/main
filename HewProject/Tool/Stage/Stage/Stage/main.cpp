#include <iostream>
#include <stdio.h>

using namespace std;
struct StageData
{
	float sizeX;
	float sizeZ;
};

struct TTerrainData
{
	// �O���b�hX
	int gridX;
	// �O���b�hY
	int gridY;
	// ����
	int count;
};


int main()
{
	FILE *fp = fopen("../Assets/Data/TestTerrain.dat", "wb");
	//StageData data;
	TTerrainData data;
	if (fp == nullptr)
		return 0;
	cout << "�t�B�[���h�̉����i���[�g���j" << endl << "����";
	cin >> data.gridX;
	cout << "�t�B�[���h�̉��s�i���[�g���j" << endl << "����";
	cin >> data.gridY;
	data.count = data.gridX * data.gridY;

	float* height = new float[data.count];
	for (int i = 0; i < data.count; i++)
	{
		height[i] = (rand() % 100) / 100.0f;
	}

	fwrite(&data, sizeof(TTerrainData), 1, fp);
	fwrite(height, sizeof(float), data.count, fp);
	fclose(fp);

	return 0;
}