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
	static float m_blurZ;	// ��ʂ̉��u��
	static float m_blurY;	// ��ʂ̏c�u��
	static bool m_Isblur;	// ��ʃu�����N���Ă��邩�ǂ���
	static int m_frame;
	const int m_totalframe = 20;
};