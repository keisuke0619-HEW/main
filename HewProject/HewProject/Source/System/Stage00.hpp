#pragma once
#include <DirectX.h>
#include <DirectXMath.h>
class CStage00
{
	struct Info
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 size;
		DirectX::XMFLOAT3 rot;
	};



public:
	CStage00();
	~CStage00();
	void Update();
	void Draw();
private:
	Info* m_pBlocks;
	int m_blockNum;
};