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
	static void Init();
	static void Uninit();
	void Update();
	void Draw();
private:
	CGameUI::Ref m_map;
	CGameUI::Ref m_playerIcon;
	CGameUI::Ref m_bossIcon;
	list<CGameUI*> m_enemyIcon;
	vector<CGameUI::Ref> m_Icon;
	IObjectBase::Ref m_player;
	DirectX::XMFLOAT3 m_movePos;
	static ID3D11ShaderResourceView* m_img;
	
};


