#include "Controller.hpp"

// �R���g���[���ƃL�[�{�[�h�ǂ���������悤�ɂ��Ă����Ă��������B



// �R���g���[���[���g�p���邽�߂ɕK�v�����Ȃ��Ƃ������ɏ����B
// ���t���[���̃A�b�v�f�[�g�̑O�ɌĂ΂��
void Utility::ControllerUpdate()
{
	////�Q�[���p�b�h�̏�Ԃ��擾
	//XINPUT_STATE state;
	//XInputGetState(0, &state);
	//int iPad_left = 0, iPad_right = 0, iPad_up = 0, iPad_down = 0;
	//int iPad_leftshoulder = 0, iPad_rightshoulder = 0;
	//int iPad_A = 0, iPad_B = 0, iPad_X = 0, iPad_Y = 0;
	//if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) iPad_left = 1;//�Q�[���p�b�h�\���L�[��
	//if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) iPad_right = 1;//�Q�[���p�b�h�\���L�[�E
	//if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) iPad_up = 1;//�Q�[���p�b�h�\���L�[��
	//if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) iPad_down = 1;//�Q�[���p�b�h�\���L�[��
	//if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) iPad_leftshoulder = 1;//�Q�[���p�b�hL
	//if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) iPad_rightshoulder = 1;//�Q�[���p�b�hR
	//if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) iPad_A = 1;//�Q�[���p�b�hA
	//if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B) iPad_B = 1;//�Q�[���p�b�hB
	//if (state.Gamepad.wButtons & XINPUT_GAMEPAD_X) iPad_X = 1;//�Q�[���p�b�hX
	//if (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) iPad_Y = 1;//�Q�[���p�b�hY
	////�Q�[���p�b�h�A�i���O�X�e�B�b�N�̃f�b�h�]�[������
	//if ((state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
	//	(state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	//{
	//	state.Gamepad.sThumbLX = 0;
	//	state.Gamepad.sThumbLY = 0;
	//}
}
// �����ꂽ�u�Ԃ���True
bool Utility::GetKeyTrigger(ControllerID)
{
    return false;
}
// �����Ă����True
bool Utility::GetKeyPress(ControllerID)
{
    return false;
}
// �����ꂽ�u�Ԃ���True
bool Utility::GetKeyRelease(ControllerID)
{
    return false;
}

DirectX::XMFLOAT3 Utility::GetLeftStick()
{
    return DirectX::XMFLOAT3();
}

DirectX::XMFLOAT3 Utility::GetRightStick()
{
    return DirectX::XMFLOAT3();
}
