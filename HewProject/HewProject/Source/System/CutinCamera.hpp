#pragma once

#include <Camera.hpp>

class CCutinCamera : public CCameraBase
{
public:
	CCutinCamera();
	~CCutinCamera();

	void Update()override;
	void SetData(DirectX::XMFLOAT3 startpos,  DirectX::XMFLOAT3 endpos, DirectX::XMFLOAT3 startrad, float rot);
	static void SetCutinBlur();
private:
	DirectX::XMFLOAT3 m_startPos;
	DirectX::XMFLOAT3 m_endPos;
	DirectX::XMFLOAT3 m_startRad;
	DirectX::XMFLOAT3 m_endRad;
	float m_rad;
	float m_step;
	static float m_blurZ;	// 画面の横ブレ
	static float m_blurY;	// 画面の縦ブレ
	static bool m_Isblur;	// 画面ブレが起きているかどうか
	static int m_frame;
	const int m_totalframe = 20;
};