#pragma once
#pragma comment(lib, "Xinput.lib")
#include <Windows.h>
#include <DirectXMath.h>
#include <Xinput.h>
#include "Input.h"
#include<SceneManager.hpp>

#define _USE_KEYBOARD_
#define  INPUT_RT_LT (127)


enum KeySet
{
	KEY_JUMP,		// �W�����v�{�^��
	KEY_BEAM,		// �r�[���{�^��
	KEY_SELECT,		// ����{�^��
	KEY_CANCEL,		// �L�����Z���{�^��

	KEY_RIGHT,
	KEY_LEFT,
	KEY_UP,
	KEY_DOWN,
	KEY_CONFIG,

	KEY_MOVE_W,
	KEY_MOVE_A,
	KEY_MOVE_S,
	KEY_MOVE_D,
	KEY_CAMERA_UP,
	KEY_CAMERA_DOWN,
	KEY_CAMERA_RIGHT,
	KEY_CAMERA_LEFT,

	KEY_DEBUG_RETURN,
	// �����v�f������΂����ɒǋL�B
	KEY_SET_MAX
};

enum ControllerID
{
	Pad_A = XINPUT_GAMEPAD_A,
	Pad_B = XINPUT_GAMEPAD_B,
	Pad_X = XINPUT_GAMEPAD_X,
	Pad_Y = XINPUT_GAMEPAD_Y,
	Pad_UP = XINPUT_GAMEPAD_DPAD_UP,
	Pad_RIGHT = XINPUT_GAMEPAD_DPAD_RIGHT,
	Pad_DOWN = XINPUT_GAMEPAD_DPAD_DOWN,
	Pad_LEFT = XINPUT_GAMEPAD_DPAD_LEFT,
	Pad_RB = XINPUT_GAMEPAD_RIGHT_SHOULDER,
	Pad_RSTICK = XINPUT_GAMEPAD_RIGHT_THUMB,
	Pad_LB = XINPUT_GAMEPAD_LEFT_SHOULDER,
	Pad_LSTICK = XINPUT_GAMEPAD_LEFT_THUMB,
	Pad_START = XINPUT_GAMEPAD_START,
	Pad_BACK = XINPUT_GAMEPAD_BACK,
	Pad_RT,
	Pad_LT,

	Key_A = 4097,
	Key_B,
	Key_C,
	Key_D,
	Key_E,
	Key_F,
	Key_G,
	Key_H,
	Key_I,
	Key_J,
	Key_K,
	Key_L,
	Key_M,
	Key_N,
	Key_O,
	Key_P,
	Key_Q,
	Key_R,
	Key_S,
	Key_T,
	Key_U,
	Key_V,
	Key_W,
	Key_X,
	Key_Y,
	Key_Z,
	Key_1,
	Key_2,
	Key_3,
	Key_4,
	Key_5,
	Key_6,
	Key_7,
	Key_8,
	Key_9,
	Key_0,
	Key_Up,
	Key_Right,
	Key_Down,
	Key_Left,
	Key_BACK,
	Key_TAB,
	Key_CLEAR,
	Key_RETURN,
	Key_SHIFT,
	Key_Ctrl,
	Key_ESCAPE,
	Key_SPACE,



	Key_END,
};
namespace Utility
{
	void ControllerInit();

	void ControllerUpdate();
	
	// �����ꂽ�u��
	bool GetKeyTrigger(KeySet key);
	// ������Ă����
	bool GetKeyPress(KeySet key);
	// �b���ꂽ�u��
	bool GetKeyRelease(KeySet key);
	/// <summary>
	/// �L�[�o�C���h��ݒ肵�܂�
	/// </summary>
	/// <param name="key">�ݒ肷�鍀��</param>
	/// <param name="id">�o�C���h����L�[</param>
	void SetKeyBind(KeySet key, ControllerID id);


	// ���X�e�B�b�N
	DirectX::XMFLOAT3 GetStickLeft();
	// �E�X�e�B�b�N
	DirectX::XMFLOAT3 GetStickRight();

	float GetCameraSpeedX();
	float GetCameraSpeedY();

	void SetCameraSpeedX(float speedX);
	void SetCameraSpeedY(float speedY);
	// ���͂����L�[�̔���
	char CheckWord(unsigned id);
}