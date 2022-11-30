#include "ObjectBase.hpp"
#include <Camera.hpp>
#include <DebugWindow.hpp>
#include <ObjectManager.hpp>

#define AddVector3(v1, v2) v1.x += v2.x; v1.y += v2.y; v1.z += v2.z;
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
    // モデル情報の読み込み
    m_model.reset(new Model());
    m_model->Load(src, scale, isFlip);
    // 頂点シェーダ読み込み
    m_vs.reset(new VertexShader());
    if (FAILED(m_vs->Load("Assets/Shader/ModelVS.cso")))
        MessageBox(nullptr, "ModelVS.cso", "Error", MB_OK);
    // 定数バッファ作成
    m_model->SetVertexShader(m_vs.get());
    m_wvp.reset(new ConstantBuffer());
    m_wvp->Create(sizeof(DirectX::XMFLOAT4X4) * 3);
}

CObjectBase::~CObjectBase()
{
}

void CObjectBase::BaseUpdate()
{
    Update();
    CDebugWindow::Print(ShimizuKeisuke, "Move", m_param.move);
    AddVector3(m_param.move, m_param.accel);
    AddVector3(m_param.pos, m_param.move);
    CDebugWindow::Print(ShimizuKeisuke, "Pos", m_param.pos);
    m_param.frame++;
}

void CObjectBase::BaseDraw()
{
    Draw();
}

TObjectParam CObjectBase::GetParam()
{
    return m_param;
}

void CObjectBase::Draw()
{
    DirectX::XMFLOAT4X4 mat[3];

    // それぞれのマトリックスを作成
    auto trs = DirectX::XMMatrixTranslation(m_param.pos.x, m_param.pos.y, m_param.pos.z);
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

    m_wvp->Write(mat);
    m_wvp->BindVS(0);

    m_model->Draw();

}

void CObjectBase::Destroy()
{
    m_param.isDestroy = true;
    CObjectManager::CallDestroy();
}
