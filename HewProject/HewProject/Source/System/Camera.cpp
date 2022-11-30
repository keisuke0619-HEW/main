#include "Camera.hpp"

std::map<const char*, CCameraBase::Ptr> CCameraBase::m_cameraMap;
const char* CCameraBase::m_primaryCameraName = "Player";

void CCameraBase::DeleteCamera(const char* cameraName)
{
    if (m_cameraMap.count(cameraName) == 0)
    {
#ifdef _DEBUG
        MessageBox(NULL, cameraName, "[DeleteCamera]存在しないカメラタグ", MB_ICONEXCLAMATION);
#endif // _DEBUG
        return;
    }
    m_cameraMap.erase(cameraName);
}
void CCameraBase::DeleteCameraAll()
{
    m_cameraMap.clear();
}
void CCameraBase::SetPrimaryCamera(const char* cameraName)
{
    if (m_cameraMap.count(cameraName) == 0)
    {
#ifdef _DEBUG
        MessageBox(NULL, cameraName, "[SetPrimaryCamera]存在しないカメラタグ", MB_ICONEXCLAMATION);
#endif // _DEBUG
        return;
    }
    m_primaryCameraName = cameraName;
}
DirectX::XMFLOAT4X4 CCameraBase::GetPrimaryViewMatrix()
{
    // もしここでエラーが出る場合はPrimaryCameraNameが存在するか確認。
    // 登録・削除のタイミングでNULLチェックをしているのでここでは割愛。
    return m_cameraMap[m_primaryCameraName]->GetViewMatrix();
}

DirectX::XMFLOAT4X4 CCameraBase::GetPrimaryProjectionMatrix()
{
    // もしここでエラーが出る場合はPrimaryCameraNameが存在するか確認。
    // 登録・削除のタイミングでNULLチェックをしているのでここでは割愛。
    return m_cameraMap[m_primaryCameraName]->GetProjectionMatrix();
}

DirectX::XMFLOAT4X4 CCameraBase::GetViewMatrixFromTag(const char* cameraName)
{
    const char* retStr = m_cameraMap.count(cameraName) != 0 ?
        cameraName :
        m_primaryCameraName;

    return m_cameraMap[retStr]->GetViewMatrix();
}

DirectX::XMFLOAT4X4 CCameraBase::GetProjectionMatrixFromTag(const char* cameraName)
{
    const char* retStr = m_cameraMap.count(cameraName) != 0 ?
        cameraName :
        m_primaryCameraName;

    return m_cameraMap[retStr]->GetProjectionMatrix();

}

CCameraBase::Data CCameraBase::GetPrimaryData()
{
    // エラーの際はPrimaryCameraNameを確認
    return m_cameraMap[m_primaryCameraName]->m_data;
}

CCameraBase::Data CCameraBase::GetDataFromTag(const char* cameraName)
{
    const char* retStr = m_cameraMap.count(cameraName) != 0 ?
        cameraName :
        m_primaryCameraName;

    return m_cameraMap[retStr]->m_data;

}

void CCameraBase::UpdatePrimary()
{
    m_cameraMap[m_primaryCameraName]->Update();
}

void CCameraBase::UpdateFromTag(const char* cameraName)
{
    if (m_cameraMap.count(cameraName) == 0)
        return;
    m_cameraMap[cameraName]->Update();

}

const char* CCameraBase::GetPrimaryName()
{
    return m_primaryCameraName;
}

DirectX::XMVECTOR CCameraBase::GetPrimaryFront()
{
    auto data = m_cameraMap[m_primaryCameraName]->m_data;
    auto vPos = DirectX::XMLoadFloat3(&data.pos);
    auto vLook = DirectX::XMLoadFloat3(&data.look);
    auto front = DirectX::XMVectorSubtract(vLook, vPos);
    return DirectX::XMVector3Normalize(front);
}

DirectX::XMVECTOR CCameraBase::GetPrimaryRight()
{
    auto front = GetPrimaryFront();
    auto rotY = DirectX::XMMatrixRotationY(3.14f / 180 * 90);
    return DirectX::XMVector3TransformCoord(front, rotY);
}

DirectX::XMVECTOR CCameraBase::GetPrimaryUp()
{
    auto front = GetPrimaryFront();
    auto rotY = DirectX::XMMatrixRotationX(3.14f / 180 * (-90));
    return DirectX::XMVector3TransformCoord(front, rotY);
}

DirectX::XMVECTOR CCameraBase::GetPrimaryFrontHorizontal()
{
    auto data = m_cameraMap[m_primaryCameraName]->m_data;
    data.pos.y = 0;
    data.look.y = 0;
    auto vPos = DirectX::XMLoadFloat3(&data.pos);
    auto vLook = DirectX::XMLoadFloat3(&data.look);
    auto front = DirectX::XMVectorSubtract(vLook, vPos);
    return DirectX::XMVector3Normalize(front);
}

DirectX::XMVECTOR CCameraBase::GetPrimaryRightHorizontal()
{
    auto front = GetPrimaryFrontHorizontal();
    auto rotY = DirectX::XMMatrixRotationY(3.14f / 180 * 90);
    return DirectX::XMVector3TransformCoord(front, rotY);
}

DirectX::XMVECTOR CCameraBase::GetPrimaryUpHorizontal()
{
    auto front = GetPrimaryFrontHorizontal();
    auto rotY = DirectX::XMMatrixRotationX(3.14f / 180 * (-90));
    return DirectX::XMVector3TransformCoord(front, rotY);

}





//------------ dynamic ----------------//
CCameraBase::CCameraBase()
    :m_distance(5)
    ,m_radXZ(2.5f)
    ,m_radY (0.7f)
    ,m_up(0,1,0)
    ,m_fovY(60.0f * 3.1415f / 180)
    ,m_aspect(16.0f / 9.0f)
    ,m_near(0.2f)
    ,m_far(1000.0f)
    ,m_tagName(nullptr)
{
    m_data.pos = { 0.0f, 0.0f, 3.0f };
    m_data.look = { 4.5f, 2, 5.0f };
}

CCameraBase::~CCameraBase()
{
}

DirectX::XMFLOAT4X4 CCameraBase::GetViewMatrix()
{
    DirectX::XMFLOAT4X4 mat;
    DirectX::XMMATRIX view = DirectX::XMMatrixLookAtLH(
        DirectX::XMVectorSet(m_data.pos.x, m_data.pos.y, m_data.pos.z, 0),
        DirectX::XMVectorSet(m_data.look.x, m_data.look.y, m_data.look.z, 0),
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
    return m_data.pos;
}

DirectX::XMFLOAT3 CCameraBase::GetLook()
{
    return m_data.look;
}
