#include <iostream>
#include <stdio.h>

using namespace std;
struct StageData
{
	float sizeX;
	float sizeZ;
};




int main()
{
	FILE *fp = fopen("../Assets/Data/Test.dat", "wb");
	StageData data;
	if (fp == nullptr)
		return 0;
	cout << "�t�B�[���h�̉����i���[�g���j" << endl << "����";
	cin >> data.sizeX;
	cout << "�t�B�[���h�̉��s�i���[�g���j" << endl << "����";
	cin >> data.sizeZ;

	fwrite(&data, sizeof(StageData), 1, fp);
	fclose(fp);

	return 0;
}