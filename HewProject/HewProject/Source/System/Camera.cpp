#include "Camera.hpp"

CCameraBase::CCameraBase()
    :m_pos(0.0f, 0.0f, 3.0f)
    ,m_look(4.5f,2,5.0f)
    ,m_distance(5)
    ,m_radXZ(2.5f)
    ,m_radY (0.7f)
    ,m_up(0,1,0)
    ,m_fovY(60.0f * 3.1415f / 180)
    ,m_aspect(16.0f / 9.0f)
    ,m_near(0.2f)
    ,m_far(1000.0f)
{
}

CCameraBase::~CCameraBase()
{
}

DirectX::XMFLOAT4X4 CCameraBase::GetViewMatrix()
{
    DirectX::XMFLOAT4X4 mat;
    DirectX::XMMATRIX view = DirectX::XMMatrixLookAtLH(
        DirectX::XMVectorSet(m_pos.x, m_pos.y, m_pos.z, 0),
        DirectX::XMVectorSet(m_look.x, m_look.y, m_look.z, 0),
        DirectX::XMVectorSet(m_up.x, m_up.y, m_up.z, 0)
    );
    view = DirectX::XMMatrixTranspose(view);
    DirectX::XMStoreFloat4x4(&mat, view);
    return mat;
}

DirectX::XMFLOAT4X4 CCameraBase::GetProjectionMatrix()
{
    DirectX::XMFLOAT4X4 mat;
    DirectX::XMMATRIX proj = DirectX::XMMatrixPerspectiveFovLH(
        m_fovY,
        m_aspect,
        m_near,
        m_far);
    proj = DirectX::XMMatrixTranspose(proj);
    DirectX::XMStoreFloat4x4(&mat, proj);

    return mat;
}

DirectX::XMFLOAT3 CCameraBase::GetPos()
{
    return m_pos;
}

DirectX::XMFLOAT3 CCameraBase::GetLook()
{
    return m_look;
}
