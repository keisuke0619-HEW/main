#pragma once

#include <GameUI.h>
#include <list>
#include <ObjIdlbase.h>
#include <IObjectBase.hpp>
using namespace std;
class CMiniMap
{
public:
	CMiniMap();
	~CMiniMap();
	void Update();
	void Draw();
private:
	CGameUI* m_map;
	list<CGameUI*> m_enemyIcon;
	IObjectBase::Ref m_player;
	DirectX::XMFLOAT3 m_movePos;
	
};


