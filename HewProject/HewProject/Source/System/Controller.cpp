#include "Controller.hpp"

// コントローラとキーボードどちらも動くようにしておいてください。



// コントローラーを使用するために必要そうなことをここに書く。
// 毎フレームのアップデートの前に呼ばれる
void Controller::ControllerUpdate()
{
}
// 押された瞬間だけTrue
bool Controller::GetKeyTrigger(ControllerID)
{
    return false;
}
// 押している間True
bool Controller::GetKeyPress(ControllerID)
{
    return false;
}
// 離された瞬間だけTrue
bool Controller::GetKeyRelease(ControllerID)
{
    return false;
}

DirectX::XMFLOAT3 Controller::GetLeftStick()
{
    return DirectX::XMFLOAT3();
}

DirectX::XMFLOAT3 Controller::GetRightStick()
{
    return DirectX::XMFLOAT3();
}
