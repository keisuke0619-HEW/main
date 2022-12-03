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
	cout << "フィールドの横幅（メートル）" << endl << "＞＞";
	cin >> data.sizeX;
	cout << "フィールドの奥行（メートル）" << endl << "＞＞";
	cin >> data.sizeZ;

	fwrite(&data, sizeof(StageData), 1, fp);
	fclose(fp);

	return 0;
}