#include "Blend.hpp"
#include <BlendState.h>

namespace Utility
{
	BlendState* g_pBlend[BLEND_MAX] = {};
}
void Utility::InitBlendState()
{
	D3D11_RENDER_TARGET_BLEND_DESC blend = {};
	blend.BlendEnable = true;
	blend.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	blend.SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blend.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blend.SrcBlendAlpha = D3D11_BLEND_ONE;
	blend.DestBlendAlpha = D3D11_BLEND_ZERO;
	blend.BlendOp = D3D11_BLEND_OP_ADD;
	blend.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	g_pBlend[BLEND_ALPHA] = new BlendState();
	g_pBlend[BLEND_ALPHA]->Create(blend);
	
	blend.SrcBlend  = D3D11_BLEND_ONE;
	blend.DestBlend = D3D11_BLEND_ONE;
	g_pBlend[BLEND_ADD] = new BlendState();
	g_pBlend[BLEND_ADD]->Create(blend);

	blend.BlendEnable = false;
	g_pBlend[BLEND_NONE] = new BlendState();
	g_pBlend[BLEND_NONE]->Create(blend);
}

void Utility::UninitBlendState()
{
	for (int i = 0; i < BLEND_ALPHA; i++)
	{
		if (g_pBlend[i])delete g_pBlend[i];
	}
}

void Utility::SetBlendState(EBlendID id)
{
	if (id == BLEND_MAX)
		return;
	if(g_pBlend[id])g_pBlend[id]->Bind();
}
