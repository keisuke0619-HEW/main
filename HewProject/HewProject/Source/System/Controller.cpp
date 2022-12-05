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
