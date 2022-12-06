#pragma once

#include <DirectX.h>
#include <MeshBuffer.h>
#include <DirectXMath.h>

struct TTerrainBase
{
	int gridX;
	int gridY;
};



// �n�`�f�[�^
class CTerrainBase
{
public:
	CTerrainBase(const char* src);
	~CTerrainBase();

	virtual void Update();
	virtual void Draw();
private:

};