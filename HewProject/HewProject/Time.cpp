#include "Time.h"

static float g_time;
static int g_cnt;

CTime::CTime()
{
}

CTime::~CTime()
{
}

void CTime::Init()
{
	g_time = 0.f;
	g_cnt = 0;
}

void CTime::Update()
{
	if (g_cnt % 60 == 0)
	{
		g_time += 0.01f;
		int time = g_time * 10;
		if (time % 10 >= 6)
		{
			g_time += 1.f;
			g_time -= 0.6f;
		}
	}
	g_cnt++;
	
}

float CTime::GetTime()
{
	return g_time;
}
