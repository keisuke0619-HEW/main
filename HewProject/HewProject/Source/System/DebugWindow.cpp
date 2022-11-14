#include "DebugWindow.hpp"
#include <stdio.h>

void CDebugWindow::Create()
{
    AllocConsole();
    FILE* fp = NULL;
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONIN$", "r", stdin);
}
