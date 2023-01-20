#include "ObjectBase.hpp"
#include <Camera.hpp>
#include <DebugWindow.hpp>
#include <ObjectManager.hpp>

CObjectBase::CObjectBase(const char* src, float scale, bool isFlip, std::string name)
{
    // メンバ変数の初期化
    m_param.pos =   { 0, 0, 0 };
    m_param.move =  { 0, 0, 0 };
    m_param.accel = { 0, 0, 0 };
    m_param.rot =   { 0, 0, 0 };
    m_param.scale = { 1, 1, 1 };
    m_param.frame = 0;
    m_param.tag =   TAG_NONE;
    m_param.name = name;
    m_param.isDestroy = false;
    m_param.collisionType = COLLISION_NONE;
    m_param.hp = 1.0f;
    m_param.drawOffset = { 0,0,0 };
    // ソースが空だったら読み込まない
    if (strcmp(src, "") != 0)
    {
        LoadModel(src, scale, isFlip, &m_modelData);
    }
}

CObjectBase::~CObjectBase()
{
}

void CObjectBase::BaseUpdate()
{
    Update();
    //AddVector3(m_param.move, m_param.accel);
    //AddVector3(m_param.pos, m_param.move);
    if (m_param.hp <= 0.0f)
        Destroy();
    m_param.frame++;
}

void CObjectBase::BaseDraw()
{
    Draw();
}

void CObjectBase::OnCollision(Ptr collisionObj)
{
}

void CObjectBase::OnCollisionTag(EObjectTag tag)
{

}

TObjectParam CObjectBase::GetParam()
{
    return m_param;
}

void CObjectBase::Draw()
{
    DirectX::XMFLOAT4X4 mat[3];

    // それぞれのマトリックスを作成
    auto trs = DirectX::XMMatrixTranslation(m_param.pos.x + m_param.drawOffset.x, m_param.pos.y + m_param.drawOffset.y, m_param.pos.z + m_param.drawOffset.z);
    auto rotX = DirectX::XMMatrixRotationX(m_param.rot.x);
    auto rotY = DirectX::XMMatrixRotationY(m_param.rot.y);
    auto rotZ = DirectX::XMMatrixRotationZ(m_param.rot.z);
    auto scale = DirectX::XMMatrixScaling(m_param.scale.x, m_param.scale.y, m_param.scale.z);
    // マトリックスの掛け合わせ
    auto world = scale * rotX * rotY * rotZ * trs;
    // 転置
    world = DirectX::XMMatrixTranspose(world);
    // 計算型に変換
    DirectX::XMStoreFloat4x4(&mat[0], world);

    // ビューマトリックスとプロジェクションマトリックスを
    // 設定するために
    // BaseCameraのStaticでDefaultカメラを取得する関数を作る
    mat[1] = CCameraBase::GetPrimaryViewMatrix();
    mat[2] = CCameraBase::GetPrimaryProjectionMatrix();

    m_modelData.wvp->Write(mat);
    m_modelData.wvp->BindVS(0);

    m_modelData.model->Draw();

}

void CObjectBase::Destroy()
{
    m_param.isDestroy = true;
    CObjectManager::CallDestroy();
    Finalize();
}

void CObjectBase::Finalize()
{
}

void CObjectBase::LoadModel(const char* src, float scale, bool isFlip, TModelData* modelData)
{
    // モデル情報の読み込み
    modelData->model.reset(new Model());
    modelData->model->Load(src, scale, isFlip);
    // 頂点シェーダ読み込み
    modelData->vs.reset(new VertexShader());
    if (FAILED(modelData->vs->Load("Assets/Shader/ModelVS.cso")))
        MessageBox(nullptr, "ModelVS.cso", "Error", MB_OK);
    // 定数バッファ作成
    modelData->model->SetVertexShader(modelData->vs.get());
    modelData->wvp.reset(new ConstantBuffer());
    modelData->wvp->Create(sizeof(DirectX::XMFLOAT4X4) * 3);
}
