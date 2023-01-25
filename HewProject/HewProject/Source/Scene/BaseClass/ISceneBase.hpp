#pragma once

struct Data	// リザルトに送るデータ
{
	int MAX_kill;
	int MAX_cnt;
};

class IScene
{
public:
	IScene() { m_data.MAX_kill = 0; m_data.MAX_cnt = 0; };
	virtual ~IScene() {};

	virtual void BaseUpdate() = 0;
	virtual void BaseDraw() = 0;
	virtual void Uninit() = 0;
	virtual void SetData(void* dataPtr, long size = 0, const char* name = "NO_NAME") = 0;
	Data* GetData() { return &m_data; };
protected:
	Data m_data;
};