#ifndef __OUTPUTEFFEKSEER_H__
#define __OUTPUTEFFEKSEER_H__

#include "DirectX.h"
#include <Effekseer.h>
#include <EffekseerRendererDX11.h>

class OutputEffekseer
{
public:
	void Init(const char16_t* effect);
	void Uninit();
	void Update();
	void Draw(float rotx, float roty, float rotz, float sizex, float sizey, float sizez);

	void Play();
private:
	//--- EffekseerÇÃèâä˙âª
	Effekseer::ManagerRef				m_efkManager;
	EffekseerRendererDX11::RendererRef	m_efkRenderer;
	Effekseer::Handle					m_efkHandle;
	Effekseer::EffectRef				m_effect;

};



#endif // __OUTPUTEFFEKSEER_H__