#include "OutputEffekseer.h"

void OutputEffekseer::Init(const char16_t* effect)
{
	//--- effekseer関数初期化
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

	//--- effect読み込み
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
	//---effekseerの描画
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
	//---effekseerの描画
	// 視点位置を確定
	auto viewerPosition = Effekseer::Vector3D(10.0f, 5.0f, 20.0f);

	// 投影行列を設定
	Effekseer::Matrix44 projectionMatrix;
	/*projectionMatrix.PerspectiveFovRH(
		90.0f / 180.0f * 3.14f, (float)1280 / 720,
		1.0f, 500.0f
	);*/
	projectionMatrix.PerspectiveFovLH(
		90.0f / 180.0f * 3.14f, (float)1280 / 720,
		1.0f, 500.0f
	);

	// カメラ行列を設定
	Effekseer::Matrix44 cameraMatrix;
	/*cameraMatrix.LookAtRH(viewerPosition,
		Effekseer::Vector3D(0.0f, 0.0f, 0.0f),
		Effekseer::Vector3D(0.0f, 1.0f, 0.0f));*/
	cameraMatrix.LookAtLH(viewerPosition,
		Effekseer::Vector3D(0.0f, 0.0f, 0.0f),
		Effekseer::Vector3D(0.0f, 1.0f, 0.0f));

	// レイヤーパラメータの設定
	Effekseer::Manager::LayerParameter layerParameter;
	layerParameter.ViewerPosition = viewerPosition;
	m_efkManager->SetLayerParameter(0, layerParameter);

	// マネージャーの更新
	Effekseer::Manager::UpdateParameter updateParameter;
	m_efkManager->Update(updateParameter);

	// 投影行列を設定
	m_efkRenderer->SetProjectionMatrix(projectionMatrix);

	// カメラ行列を設定
	m_efkRenderer->SetCameraMatrix(cameraMatrix);

	// エフェクトの描画開始処理を行う
	m_efkRenderer->BeginRendering();

	// エフェクトの描画を行おう
	Effekseer::Manager::DrawParameter drawParameter;
	drawParameter.ZNear = 0.0f;
	drawParameter.ZFar = 1.0f;
	drawParameter.ViewProjectionMatrix =
		m_efkRenderer->GetCameraProjectionMatrix();
	m_efkManager->Draw(drawParameter);

	// エフェクトの描画終了処理を行う
	m_efkRenderer->EndRendering();

	// エフェクトのサイズ設定
	//m_efkManager->SetScale(m_efkHandle, sizex, sizey, sizez);

	// 度数法から弧度法に変換
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
