#ifndef __OUTPUTEFFEKSEER_H__
#define __OUTPUTEFFEKSEER_H__

#include "DirectX.h"
#include <Effekseer.h>
#include <EffekseerRendererDX11.h>
#include <DirectXMath.h>
#include <memory>
#include <list>
class CEffect
{
public:
	using Ptr = std::shared_ptr<CEffect>;
	static void InitSystem();
	static void UninitSystem();
	static void DrawAll();
	static void UpdateSystem();
private:
	static std::list<CEffect*> m_list;

public:
	CEffect(const char16_t* effect);
	~CEffect();
	void Update();

	void SetPos(float x, float y, float z);
	void SetRotation(float x, float y, float z);
	void SetScale(float x, float y, float z);
	void Play();
private:
	void Draw();
	//--- EffekseerÇÃèâä˙âª
	static Effekseer::ManagerRef				m_efkManager;
	static EffekseerRendererDX11::RendererRef	m_efkRenderer;
	Effekseer::Handle					m_efkHandle;
	Effekseer::EffectRef				m_effect;

	Effekseer::Vector3D m_pos;
	Effekseer::Vector3D m_rot;
	Effekseer::Vector3D m_scale;

	Effekseer::Matrix44 GetMat(DirectX::XMFLOAT4X4);
};



#endif // __OUTPUTEFFEKSEER_H__