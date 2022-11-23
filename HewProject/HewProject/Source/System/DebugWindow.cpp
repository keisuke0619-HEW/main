#include "DebugWindow.hpp"
#include <string>
FILE* CDebugWindow::m_fp = nullptr;

void CDebugWindow::Create()
{
    if (m_fp != nullptr)
        return;
    AllocConsole();
    freopen_s(&m_fp, "CONOUT$", "w", stdout);
    freopen_s(&m_fp, "CONIN$", "r", stdin);

    // コンソールの名前変更
    SetConsoleTitle("DebugWindow");
}

void CDebugWindow::Close()
{
    if (m_fp == nullptr)
        return;
    auto hWnd = FindWindow(NULL, "DebugWindow");
    FreeConsole();
    fclose(m_fp);
    m_fp = nullptr;
}
