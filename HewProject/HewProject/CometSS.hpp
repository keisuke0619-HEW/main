#pragma once

#include <DirectXMath.h>
#include <DirectXTex/Texture.h>
#include <UiManager.hpp>
class CCometSS
{
public:
	CCometSS();
	~CCometSS();

	void Update();
	void Draw();
private:
	DirectX::XMFLOAT2 m_pos;
	ID3D11ShaderResourceView* m_tex;
	CGameUI::Ref m_handle;
};