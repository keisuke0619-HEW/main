#ifndef  __GAME_UI_H__
#define  __GAME_UI_H__

#include "DirectX.h"

class CGameUI
{
public:
	CGameUI();
	~CGameUI();
	void Draw();

private:
	ID3D11ShaderResourceView* m_pBar;
};
#endif // ! __GAME_UI_H__

