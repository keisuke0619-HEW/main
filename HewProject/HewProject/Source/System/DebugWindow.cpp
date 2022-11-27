#include "DebugWindow.hpp"
#include <iostream>
#include <string>
FILE* CDebugWindow::m_fp = nullptr;
CreatorTag CDebugWindow::m_creator = NULL_CREATOR;

void CDebugWindow::Create()
{
    if (m_fp != nullptr)
        return;
    AllocConsole();
    freopen_s(&m_fp, "CONOUT$", "w", stdout);
    freopen_s(&m_fp, "CONIN$", "r", stdin);

    // コンソールの名前変更
    SetConsoleTitle("DebugWindow");
    SetCreator();
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

void CDebugWindow::Print(CreatorTag tag, const char* src)
{
    if (tag != m_creator)
        return;
    printf(src);
}

void CDebugWindow::Print(CreatorTag tag, const char* label, int data)
{
    if (tag != m_creator)
        return;
    char tmp[128] = {};
    sprintf(tmp, "%s\t:%d\n", label, data);
    printf(tmp);
}

void CDebugWindow::Print(CreatorTag tag, const char* label, float data)
{
    if (tag != m_creator)
        return;
    char tmp[128] = {};
    sprintf(tmp, "%s\t:%.4f\n", label, data);
    printf(tmp);
}


void CDebugWindow::Print(CreatorTag tag, const char* label, DirectX::XMFLOAT3 data)
{
    if (tag != m_creator)
        return;
    char tmp[128] = {};
    sprintf(tmp, "%s\t:( %9.4f, %9.4f, %9.4f )\n", label, data.x, data.y, data.z);
    printf(tmp);
}

void CDebugWindow::Print(CreatorTag tag, const char* label, DirectX::XMVECTOR data)
{
    DirectX::XMFLOAT3 tmp;
    DirectX::XMStoreFloat3(&tmp, data);
    Print(tag, label, tmp);
}

void CDebugWindow::Print(CreatorTag tag, const char* label, DirectX::XMMATRIX data)
{
    if (tag != m_creator)
        return;
    char tmp[256] = {};
    sprintf(tmp, "%s\t:\n{ %9.4f,%9.4f,%9.4f,%9.4f\n  %9.4f,%9.4f,%9.4f,%9.4f\n  %9.4f,%9.4f,%9.4f,%9.4f\n  %9.4f,%9.4f,%9.4f,%9.4f }\n", label, 
        data.r[0].m128_f32[0], data.r[1].m128_f32[0], data.r[2].m128_f32[0], data.r[3].m128_f32[0],
        data.r[0].m128_f32[1], data.r[1].m128_f32[1], data.r[2].m128_f32[1], data.r[3].m128_f32[1],
        data.r[0].m128_f32[2], data.r[1].m128_f32[2], data.r[2].m128_f32[2], data.r[3].m128_f32[2],
        data.r[0].m128_f32[3], data.r[1].m128_f32[3], data.r[2].m128_f32[3], data.r[3].m128_f32[3]
        );
    printf(tmp);
}
