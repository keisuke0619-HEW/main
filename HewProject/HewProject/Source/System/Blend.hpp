#pragma once
enum EBlendID
{
	BLEND_NONE,
	BLEND_ALPHA,
	BLEND_ADD,




	BLEND_MAX
};
namespace Utility
{
	void InitBlendState();
	void UninitBlendState();
	void SetBlendState(EBlendID id);
}