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
	static float m_blurX;	// 画面の横ブレ
	static float m_blurY;	// 画面の縦ブレ
	static bool m_Isblur;	// 画面ブレが起きているかどうか
	static int m_frame;
	const int m_totalframe = 10;
};