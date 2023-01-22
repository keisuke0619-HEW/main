#pragma once
#include <Camera.hpp>
#include <memory>
#include <IObjectBase.hpp>
class CPlayerCamera : public CCameraBase
{
public:
	CPlayerCamera();
	~CPlayerCamera();

	void Update() override;
	static void SetBlur();
private:
	std::weak_ptr<IObjectBase> m_target;
	static float m_blurX;	// ��ʂ̉��u��
	static float m_blurY;	// ��ʂ̏c�u��
	static bool m_Isblur;	// ��ʃu�����N���Ă��邩�ǂ���
	static int m_frame;
	const int m_totalframe = 10;
};