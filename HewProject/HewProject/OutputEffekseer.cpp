#include "OutputEffekseer.h"

void OutputEffekseer::Init(const char16_t* effect)
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

	//--- effect�ǂݍ���
	m_effect = Effekseer::Effect::Create(m_efkManager, effect);
}

void OutputEffekseer::Uninit()
{
	m_effect.Reset();
	m_efkRenderer.Reset();
	m_efkManager.Reset();
}

void OutputEffekseer::Update()
{
	//---effekseer�̕`��
	auto viewerPosition = Effekseer::Vector3D(10.0f, 5.0f, 20.0f);
	Effekseer::Matrix44 projectionMatrix;
	/*projectionMatrix.PerspectiveFovRH(
		90.0f / 180.0f * 3.14f, (float)1280 / 720,
		1.0f, 500.0f
	);*/
	projectionMatrix.PerspectiveFovLH(
		90.0f / 180.0f * 3.14f, (float)1280 / 720,
		1.0f, 500.0f
	);
	Effekseer::Matrix44 cameraMatrix;
	/*cameraMatrix.LookAtRH(viewerPosition,
		Effekseer::Vector3D(0.0f, 0.0f, 0.0f),
		Effekseer::Vector3D(0.0f, 1.0f, 0.0f));*/
	cameraMatrix.LookAtLH(viewerPosition,
		Effekseer::Vector3D(0.0f, 0.0f, 0.0f),
		Effekseer::Vector3D(0.0f, 1.0f, 0.0f));

	Effekseer::Manager::LayerParameter layerParameter;
	layerParameter.ViewerPosition = viewerPosition;
	m_efkManager->SetLayerParameter(0, layerParameter);

	Effekseer::Manager::UpdateParameter updateParameter;
	m_efkManager->Update(updateParameter);

	m_efkRenderer->SetProjectionMatrix(projectionMatrix);
	m_efkRenderer->SetCameraMatrix(cameraMatrix);

	m_efkRenderer->BeginRendering();


	Effekseer::Manager::DrawParameter drawParameter;
	drawParameter.ZNear = 0.0f;
	drawParameter.ZFar = 1.0f;
	drawParameter.ViewProjectionMatrix =
		m_efkRenderer->GetCameraProjectionMatrix();
	m_efkManager->Draw(drawParameter);

	m_efkRenderer->EndRendering();
}

void OutputEffekseer::Draw(float rotx, float roty, float rotz, float sizex, float sizey, float sizez)
{
	//---effekseer�̕`��
	// ���_�ʒu���m��
	auto viewerPosition = Effekseer::Vector3D(10.0f, 5.0f, 20.0f);

	// ���e�s���ݒ�
	Effekseer::Matrix44 projectionMatrix;
	/*projectionMatrix.PerspectiveFovRH(
		90.0f / 180.0f * 3.14f, (float)1280 / 720,
		1.0f, 500.0f
	);*/
	projectionMatrix.PerspectiveFovLH(
		90.0f / 180.0f * 3.14f, (float)1280 / 720,
		1.0f, 500.0f
	);

	// �J�����s���ݒ�
	Effekseer::Matrix44 cameraMatrix;
	/*cameraMatrix.LookAtRH(viewerPosition,
		Effekseer::Vector3D(0.0f, 0.0f, 0.0f),
		Effekseer::Vector3D(0.0f, 1.0f, 0.0f));*/
	cameraMatrix.LookAtLH(viewerPosition,
		Effekseer::Vector3D(0.0f, 0.0f, 0.0f),
		Effekseer::Vector3D(0.0f, 1.0f, 0.0f));

	// ���C���[�p�����[�^�̐ݒ�
	Effekseer::Manager::LayerParameter layerParameter;
	layerParameter.ViewerPosition = viewerPosition;
	m_efkManager->SetLayerParameter(0, layerParameter);

	// �}�l�[�W���[�̍X�V
	Effekseer::Manager::UpdateParameter updateParameter;
	m_efkManager->Update(updateParameter);

	// ���e�s���ݒ�
	m_efkRenderer->SetProjectionMatrix(projectionMatrix);

	// �J�����s���ݒ�
	m_efkRenderer->SetCameraMatrix(cameraMatrix);

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

	// �G�t�F�N�g�̃T�C�Y�ݒ�
	//m_efkManager->SetScale(m_efkHandle, sizex, sizey, sizez);

	// �x���@����ʓx�@�ɕϊ�
	float radx = rotx * 3.14 / 180.0f;
	float rady = roty * 3.14 / 180.0f;
	float radz = rotz * 3.14 / 180.0f;


	m_efkManager->SetRotation(m_efkHandle, radx, rady, radz);
	m_efkManager->SetScale(m_efkHandle, sizex, sizey, sizez);

}

void OutputEffekseer::Play()
{

	m_efkHandle = m_efkManager->Play(m_effect, 0, 0, 0);
}
