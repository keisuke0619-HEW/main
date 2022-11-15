#include "player.hpp"
#include <Input.h>
#include <DebugWindow.hpp>
CPlayer::CPlayer()
{
    m_pos = { 0,0,0 };
    m_model.reset(new Model());
    m_model->Load("Assets/unitychan/unitychan.fbx", 0.01f);
    m_vs.reset(new VertexShader());
    if (FAILED(m_vs.get()->Load("Assets/Shader/ModelVS.cso")))
        MessageBox(nullptr, "ModelVS.cso", "Error", MB_OK);
    m_model->SetVertexShader(m_vs.get());
    m_wvp.reset(new ConstantBuffer());
    m_wvp->Create(sizeof(DirectX::XMFLOAT4X4) * 3);
}

CPlayer::~CPlayer()
{
}

void CPlayer::Update()
{
    const float MOVE_SPEED = 0.1f;
    auto camPos = m_cam->GetPos();
    camPos.y = 0;
    auto camLook = m_cam->GetLook();
    camLook.y = 0;
    auto vCamPos = DirectX::XMLoadFloat3(&camPos);
    auto vCamLook = DirectX::XMLoadFloat3(&camLook);

    DirectX::XMVECTOR vFront;
    vFront = DirectX::XMVectorSubtract(vCamPos, vCamLook);
    vFront = DirectX::XMVector3Normalize(vFront);

    auto matRotSide = DirectX::XMMatrixRotationY(3.14f / 180 * 90);
    auto vSide = DirectX::XMVector3TransformCoord(vFront, matRotSide);


    auto vMove = DirectX::XMVectorZero();
    if (IsKeyPress('W'))vMove = DirectX::XMVectorSubtract(vMove, vFront);
    if (IsKeyPress('S'))vMove = DirectX::XMVectorAdd(vMove, vFront);
    if (IsKeyPress('A'))vMove = DirectX::XMVectorAdd(vMove, vSide);
    if (IsKeyPress('D'))vMove = DirectX::XMVectorSubtract(vMove, vSide);

    if (IsKeyTrigger('R'))CDebugWindow::Close();
    if (IsKeyTrigger('T'))CDebugWindow::Create();
    if (IsKeyTrigger('C'))printf("a\n");

    // ã‰ºˆ—
    DirectX::XMFLOAT3 up = { 0, 1, 0 };
    auto vUp = DirectX::XMLoadFloat3(&up);
    if (IsKeyPress(VK_SPACE))vMove = DirectX::XMVectorAdd(vMove, vUp);
    if (IsKeyPress(VK_SHIFT))vMove = DirectX::XMVectorSubtract(vMove, vUp); 

    vMove = DirectX::XMVectorScale(vMove, MOVE_SPEED);


    DirectX::XMFLOAT3 move;
    DirectX::XMStoreFloat3(&move, vMove);
    m_pos.x += move.x;
    m_pos.y += move.y;
    m_pos.z += move.z;

    //if (IsKeyPress('W'))m_pos.z += MOVE_SPEED;
    //if (IsKeyPress('S'))m_pos.z -= MOVE_SPEED;
    //if (IsKeyPress('D'))m_pos.x += MOVE_SPEED;
    //if (IsKeyPress('A'))m_pos.x -= MOVE_SPEED;
    //if (IsKeyPress(VK_SPACE))m_pos.y += MOVE_SPEED;
    //if (IsKeyPress(VK_SHIFT))m_pos.y -= MOVE_SPEED;
}

void CPlayer::Draw()
{
    DirectX::XMFLOAT4X4 mat[3];

    DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
    DirectX::XMMATRIX Rx = DirectX::XMMatrixRotationX(0);
    DirectX::XMMATRIX Ry = DirectX::XMMatrixRotationY(0);
    DirectX::XMMATRIX Rz = DirectX::XMMatrixRotationZ(0);
    DirectX::XMMATRIX S = DirectX::XMMatrixScaling(1, 1, 1);

    DirectX::XMMATRIX world = S * Rx * Ry * Rz * T;
    world = DirectX::XMMatrixTranspose(world);
    DirectX::XMStoreFloat4x4(&mat[0], world);

    mat[1] = m_cam->GetViewMatrix();
    mat[2] = m_cam->GetProjectionMatrix();
    m_wvp->Write(mat);
    m_wvp->BindVS(0);

    m_model->Draw();
}

void CPlayer::SetCamera(CCameraBase* pCam)
{
    m_cam = pCam;
}

DirectX::XMFLOAT3 CPlayer::GetPos()
{
    return m_pos;
}
