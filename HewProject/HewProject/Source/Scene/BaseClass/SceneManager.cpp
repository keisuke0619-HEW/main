#include "SceneManager.hpp"
#include <Camera.hpp>
#include <Billboard.h>
#include <Sprite.h>
#include <DirectX.h>
#include <Blend.hpp>
// シーン
#include <GameScene.hpp>
#include <SceneStageSelect.hpp>
#include <SceneTitle.hpp>
#include <SceneResult.hpp>

// ステージ情報
#include <StageData01.hpp>
#include <StageData02.hpp>
#include <StageData03.hpp>
//#include <StageData04.hpp>
std::unique_ptr<IScene> CSceneManager::m_scene;
ESwapState CSceneManager::m_isSwap = SWAP_NONE;
ESceneID CSceneManager::m_next;
std::vector<TScenePassingData> CSceneManager::m_passingData;
ID3D11ShaderResourceView* CSceneManager::m_fade;
float CSceneManager::m_alpha;

void CSceneManager::SetScene(ESceneID ID)
{
	if (m_isSwap != SWAP_NONE)
		return;
	m_isSwap = SWAP_WAIT;
	m_next = ID;
}

void CSceneManager::Init()
{
	if (m_fade == nullptr)
		LoadTextureFromFile("Assets/Img/White.png", &m_fade);
}

void CSceneManager::Update()
{
	if(m_scene)
		m_scene->BaseUpdate();
	switch (m_isSwap)
	{
	case SWAP_WAIT:
		m_alpha += 0.05f;
		break;
	case SWAP_END:
		m_alpha -= 0.05f;
		break;
	default:
		break;
	}
	if (m_isSwap == SWAP_WAIT && m_alpha >= 1.0f)
	{
		m_isSwap = SWAP_OK;
	}
	if (m_isSwap == SWAP_END && m_alpha <= 0.0f)
	{
		m_isSwap = SWAP_NONE;
	}
}

void CSceneManager::Draw()
{
	if(m_scene)
		m_scene->BaseDraw();
	if (m_isSwap != SWAP_NONE)
	{
		EnableDepth(false);
		Utility::SetBlendState(BLEND_ALPHA);
		DirectX::XMFLOAT4X4 fView;
		DirectX::XMStoreFloat4x4(&fView, DirectX::XMMatrixIdentity());
		DirectX::XMFLOAT4X4 fProj;
		DirectX::XMStoreFloat4x4(&fProj,
			DirectX::XMMatrixTranspose(
				DirectX::XMMatrixOrthographicOffCenterLH(
					0.f,	// 画面左端の座標
					1280.f,	// 画面右端の座標
					720.f,	// 画面下端の座標
					0.f,	// 画面上端の座標
					-1.f,	// Z方向で写せる最小値
					1.f)));	// Z方向で写せる最大値
		Sprite::SetView(fView);
		Sprite::SetProjection(fProj);

		Sprite::SetTexture(m_fade);
		auto mat = DirectX::XMMatrixTranslation(640, 360, 0);
		DirectX::XMFLOAT4X4 fMat;
		DirectX::XMStoreFloat4x4(&fMat, DirectX::XMMatrixTranspose(mat));
		Sprite::SetWorld(fMat);
		Sprite::SetSize(DirectX::XMFLOAT2(1280, -720));
		Sprite::SetColor(DirectX::XMFLOAT4(0,0,0,m_alpha));
		Sprite::Draw();
		Utility::SetBlendState(BLEND_NONE);
		EnableDepth(true);
	}
}

void CSceneManager::Uninit()
{
	if (m_fade != nullptr)
		m_fade->Release();
}

void CSceneManager::SwapScene()
{
	if (m_isSwap != SWAP_OK)
		return;
	CBillboard::ClearBillboard();
	CCameraBase::DeleteCameraAll();
	if (m_scene)
		m_scene->Uninit();
	Data* data;
	switch (m_next)
	{
	case SCENE_TITLE:
		m_scene.reset(new CSceneTitle());
		break;
	case SCENE_STAGE_SELECT:
		m_scene.reset(new CSceneStageSelect());
		break;
	case SCENE_STAGE01:
		m_scene.reset(new CGameScene());
		m_scene->SetData(SCENE_STAGE01);
		data = m_scene->GetData();
		m_scene->SetData(new CStageData01(data));
		break;
	case SCENE_STAGE02:
		m_scene.reset(new CGameScene());
		m_scene->SetData(SCENE_STAGE02);
		data = m_scene->GetData();
		m_scene->SetData(new CStageData02(data));
		break;
	case SCENE_STAGE03:
		m_scene.reset(new CGameScene());
		m_scene->SetData(SCENE_STAGE03);
		data = m_scene->GetData();
		m_scene->SetData(new CStageData03(data));
		break;
	case SCENE_STAGE04:
		//m_scene.reset(new CGameScene());
		//m_scene->SetData(SCENE_STAGE04);
		//data = m_scene->GetData();
		//m_scene->SetData(new CStageData04(data));
		break;
	case SCENE_RESULT:
		data = m_scene->GetData();
		m_scene.reset(new CSceneResult(*data));
		break;
	default:
		break;
	}
	for (int i = 0; i < m_passingData.size(); i++)
	{
		auto data = m_passingData[i];
		m_scene->SetData(data.dataPtr, data.size, data.name);
	}
	m_passingData.clear();
	m_isSwap = SWAP_END;
}

void CSceneManager::SetData(void* dataPtr, long size, const char* name)
{
	TScenePassingData tmp = { dataPtr, size, name };
	m_passingData.push_back(tmp);
}