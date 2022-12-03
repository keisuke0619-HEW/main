#ifndef __GEOMETORY_H__
#define __GEOMETORY_H__

#include "DirectX.h"
#include <DirectXMath.h>
#include <MeshBuffer.h>

struct TGeometoryColor
{
	float r;
	float g;
	float b;
	float a;
	float gridX;
	float gridY;
	float d[2];
};

HRESULT InitGeometory();
void UninitGeometory();
void SetGeometoryTranslate(float x, float y, float z);
void SetGeometoryRotation(float x, float y, float z);
void SetGeometoryScaling(float x, float y, float z);
void SetGeometoryVPMatrix(DirectX::XMFLOAT4X4 view, DirectX::XMFLOAT4X4 proj);
void DrawBox();
void DrawSphere();
void DrawCylinder();
void DrawCone();
void DrawCapsule();
void DrawArrow();

void SetColorPS(bool isUse, float r = 1, float g = 1, float b = 1, float a = 1, float x = 1, float y = 1);
#endif // __GEOMETORY_H__