#include "OutputEffekseer.h"
#include <Camera.hpp>
Effekseer::ManagerRef				CEffect::m_efkManager;
EffekseerRendererDX11::RendererRef	CEffect::m_efkRenderer;
std::list<CEffect*> CEffect::m_list;

void CEffect::InitSystem()
{
	//--- effekseer�֐�������
	m_efkManager = Effekseer::Manager::Create(8000);

	auto graphicsDevice = EffekseerRendererDX11::CreateGraphicsDevice(
		GetDevice(), GetContext());
	m_efkRenderer = EffekseerRendererDX11::Renderer::Create(
		graphicsDevice, 8000);

	m_efkManager->SetSpriteRenderer(m_efkRenderer->CreateSpriteRenderer());
	m_efkManager->SetRibbonRenderer(m_efkRenderer->CreateRibbonRenderer());
	m_efkManager->SetRingRenderer(m_efkRenderer->CreateRingRenderer());
	m_efkManager->SetTrackRenderer(m_efkRenderer->CreateTrackRenderer());
	m_efkManager->SetModelRenderer(m_efkRenderer->CreateModelRenderer());

	m_efkManager->SetTextureLoader(m_efkRenderer->CreateTextureLoader());
	m_efkManager->SetModelLoader(m_efkRenderer->CreateModelLoader());
	m_efkManager->SetMaterialLoader(m_efkRenderer->CreateMaterialLoader());
	m_efkManager->SetCurveLoader(Effekseer::MakeRefPtr<Effekseer::CurveLoader>());
}

void CEffect::UninitSystem()
{
	m_efkRenderer.Reset();
	m_efkManager.Reset();
}

void CEffect::DrawAll()
{
	for (auto itr = m_list.begin(); itr != m_list.end(); itr++)
	{
		(*itr)->Draw();
	}
}

void CEffect::UpdateSystem()
{
	Effekseer::Manager::UpdateParameter updateParameter;
	m_efkManager->Update(updateParameter);
}

CEffect::CEffect(const char16_t* effect)
{
	//--- effect�ǂݍ���
	m_effect = Effekseer::Effect::Create(m_efkManager, effect);
	m_list.push_back(this);
	IsPlay = false;
	m_scale.X = 1;
	m_scale.Y = 1;
	m_scale.Z = 1;
}

CEffect::~CEffect()
{
	m_list.remove(this);
	m_effect.Reset();
}

void CEffect::Update()
{
	//---effekseer�̕`��
}

void CEffect::Draw()
{
	//---effekseer�̕`��
	// ���_�ʒu���m��
	auto camPos = CCameraBase::GetPrimaryData().look;
	auto viewerPosition = Effekseer::Vector3D(camPos.x, camPos.y, camPos.z);

	// ���e�s���ݒ�
	Effekseer::Matrix44 projectionMatrix;
	projectionMatrix = GetMat(CCameraBase::GetPrimaryProjectionMatrix());
	// �J�����s���ݒ�
	Effekseer::Matrix44 cameraMatrix = GetMat(CCameraBase::GetPrimaryViewMatrix());

	// ���C���[�p�����[�^�̐ݒ�
	Effekseer::Manager::LayerParameter layerParameter;
	layerParameter.ViewerPosition = viewerPosition;
	m_efkManager->SetLayerParameter(0, layerParameter);


	// ���e�s���ݒ�
	m_efkRenderer->SetProjectionMatrix(projectionMatrix);

	// �J�����s���ݒ�
	m_efkRenderer->SetCameraMatrix(cameraMatrix);

	// �x���@����ʓx�@�ɕϊ�
	float radx = m_rot.X;
	float rady = m_rot.Y;
	float radz = m_rot.Z;


	m_efkManager->SetRotation(m_efkHandle, radx, rady, radz);
	m_efkManager->SetScale(m_efkHandle, m_scale.X, m_scale.Y, m_scale.Z);

	// �G�t�F�N�g�̕`��J�n�������s��
	m_efkRenderer->BeginRendering();

	// �G�t�F�N�g�̕`����s����
	Effekseer::Manager::DrawParameter drawParameter;
	drawParameter.ZNear = 0.0f;
	drawParameter.ZFar = 1.0f;
	drawParameter.ViewProjectionMatrix =
		m_efkRenderer->GetCameraProjectionMatrix();
	m_efkManager->Draw(drawParameter);

	// �G�t�F�N�g�̕`��I���������s��
	m_efkRenderer->EndRendering();


}

void CEffect::SetPos(float x, float y, float z)
{
	m_pos = { x, y, z };
}

void CEffect::SetRotation(float x, float y, float z)
{
	m_rot.X = x;
	m_rot.Y = y;
	m_rot.Z = z;
	//{ x, y, z };
}

void CEffect::SetScale(float x, float y, float z)
{
	m_scale.X = x;
	m_scale.Y = y;
	m_scale.Z = z;
}

void CEffect::AddPos(float x, float y, float z)
{
	m_efkManager->SetLocation(m_efkHandle, ::Effekseer::Vector3D(x, y, z));
}

void CEffect::Play()
{
	m_efkHandle = m_efkManager->Play(m_effect, m_pos.X, m_pos.Y, m_pos.Z);
}

void CEffect::PlayOnce()
{
	// Draw�ň�񂾂��Ă΂��
	if (IsPlay == false)
	{
		m_efkHandle = m_efkManager->Play(m_effect, m_pos.X, m_pos.Y, m_pos.Z);
		IsPlay = true;
	}
}

void CEffect::End()
{
	// Effekseer�������I��
	if (IsPlay == true)
	{
		m_efkManager->StopEffect(m_efkHandle);
		IsPlay = false;
	}
}

void CEffect::ContinuePlay(float time)
{
	if (IsPlay == false)
	{
		m_efkHandle = m_efkManager->Play(m_effect, { m_pos.X, m_pos.Y, m_pos.Z }, time);
		IsPlay = true;
	}
}

Effekseer::Matrix44 CEffect::GetMat(DirectX::XMFLOAT4X4 in)
{
	Effekseer::Matrix44 out;
	out.Values[0][0] = in._11;
	out.Values[1][0] = in._12;
	out.Values[2][0] = in._13;
	out.Values[3][0] = in._14;
	out.Values[0][1] = in._21;
	out.Values[1][1] = in._22;
	out.Values[2][1] = in._23;
	out.Values[3][1] = in._24;
	out.Values[0][2] = in._31;
	out.Values[1][2] = in._32;
	out.Values[2][2] = in._33;
	out.Values[3][2] = in._34;
	out.Values[0][3] = in._41;
	out.Values[1][3] = in._42;
	out.Values[2][3] = in._43;
	out.Values[3][3] = in._44;
	return out;
}
