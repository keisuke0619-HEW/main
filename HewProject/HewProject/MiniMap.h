#pragma once

#include <GameUI.h>
#include <list>
#include <ObjIdlbase.h>
#include <IObjectBase.hpp>
#include <vector>
using namespace std;
class CMiniMap
{
public:
	CMiniMap();
	~CMiniMap();
	void Update();
	void Draw();
private:
	CGameUI::Ref m_map;
	list<CGameUI*> m_enemyIcon;
	vector<CGameUI::Ref> m_Icon;
	IObjectBase::Ref m_player;
	DirectX::XMFLOAT3 m_movePos;
	
};


