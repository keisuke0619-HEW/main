#include "Controller.hpp"

// �R���g���[���ƃL�[�{�[�h�ǂ���������悤�ɂ��Ă����Ă��������B



// �R���g���[���[���g�p���邽�߂ɕK�v�����Ȃ��Ƃ������ɏ����B
// ���t���[���̃A�b�v�f�[�g�̑O�ɌĂ΂��
void Utility::ControllerUpdate()
{
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
