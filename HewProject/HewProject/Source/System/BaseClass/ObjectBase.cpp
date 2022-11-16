#include "ObjectBase.hpp"

#define AddVector3(v1, v2) v1.x += v2.x; v1.y += v2.y; v1.z += v2.z;
CObjectBase::CObjectBase(const char* src, float scale, bool isFlip)
{
    // �����o�ϐ��̏�����
    m_param.pos =   { 0, 0, 0 };
    m_param.move =  { 0, 0, 0 };
    m_param.accel = { 0, 0, 0 };
    m_param.rot = { 0, 0, 0 };
    m_param.frame = 0;
    m_param.tag =   TAG_NONE;
    // ���f�����̓ǂݍ���
    m_model.reset(new Model());
    m_model->Load(src, scale, isFlip);
    // ���_�V�F�[�_�ǂݍ���
    m_vs.reset(new VertexShader());
    if (FAILED(m_vs.get()->Load("Assets/Shader/ModelVS.cso")))
        MessageBox(nullptr, "ModelVS.cso", "Error", MB_OK);
    // �萔�o�b�t�@�쐬
    m_wvp.reset(new ConstantBuffer());
    m_wvp->Create(sizeof(DirectX::XMFLOAT4X4) * 3);
}

CObjectBase::~CObjectBase()
{
}

void CObjectBase::UpdateBase()
{
    Update();
    AddVector3(m_param.move, m_param.accel);
    AddVector3(m_param.pos, m_param.move);

    m_param.frame++;
}

void CObjectBase::DrawBase()
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

    // ���ꂼ��̃}�g���b�N�X���쐬
    auto trs = DirectX::XMMatrixTranslation(m_param.pos.x, m_param.pos.x, m_param.pos.x);
    auto rotX = DirectX::XMMatrixRotationX(m_param.rot.x);
    auto rotY = DirectX::XMMatrixRotationY(m_param.rot.y);
    auto rotZ = DirectX::XMMatrixRotationZ(m_param.rot.z);
    auto scale = DirectX::XMMatrixScaling(m_param.scale.x, m_param.scale.y, m_param.scale.z);
    // �}�g���b�N�X�̊|�����킹
    auto world = scale * rotX * rotY * rotZ * trs;
    // �]�u
    world = DirectX::XMMatrixTranspose(world);
    // �v�Z�^�ɕϊ�
    DirectX::XMStoreFloat4x4(&mat[0], world);

    // �r���[�}�g���b�N�X�ƃv���W�F�N�V�����}�g���b�N�X��
    // �ݒ肷�邽�߂�
    // BaseCamera��Static��Default�J�������擾����֐������

}
