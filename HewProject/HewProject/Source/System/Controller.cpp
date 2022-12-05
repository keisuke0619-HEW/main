#include "Controller.hpp"

// コントローラとキーボードどちらも動くようにしておいてください。



// コントローラーを使用するために必要そうなことをここに書く。
// 毎フレームのアップデートの前に呼ばれる
void Utility::ControllerUpdate()
{
}
// 押された瞬間だけTrue
bool Utility::GetKeyTrigger(ControllerID)
{
    return false;
}
// 押している間True
bool Utility::GetKeyPress(ControllerID)
{
    return false;
}
// 離された瞬間だけTrue
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
