#include "ProducePlane.h"
#include <MeshBuffer.h>
#include <Camera.hpp>

ProducePlane::ProducePlane(const char* FileName)
	:m_pos(0.0f, 0.0f, 0.0f)
	,m_size(1.0f, 1.0f, 0.0f)
	,m_rot(0.0f, 0.0f, 0.0f)
	,m_IsDarw(true)
{
	LoadTextureFromFile(FileName, &m_pPicture);
}

ProducePlane::~ProducePlane()
{
	m_pPicture->Release();
}

void ProducePlane::Draw()
{
	if (m_IsDarw == true)
	{
		// ビュー行列セット
		Sprite::SetView(CCameraBase::GetPrimaryViewMatrix());
		// プロジェクション行列セット
		Sprite::SetProjection(CCameraBase::GetPrimaryProjectionMatrix());

		// ワールド行列
		DirectX::XMFLOAT4X4 world;

		DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
		DirectX::XMMATRIX Rx = DirectX::XMMatrixRotationX(m_rot.x);
		DirectX::XMMATRIX Ry = DirectX::XMMatrixRotationY(m_rot.y);
		DirectX::XMMATRIX Rz = DirectX::XMMatrixRotationZ(m_rot.z);
		DirectX::XMMATRIX S = DirectX::XMMatrixScaling(m_size.x, m_size.y, 0.0f);
		DirectX::XMMATRIX mat = S * Rx * Ry * Rz * T;
		mat = DirectX::XMMatrixTranspose(mat);
		DirectX::XMStoreFloat4x4(&world, mat);
		
		// ワールド行列セット
		Sprite::SetWorld(world);
		// テクスチャセット
		Sprite::SetTexture(m_pPicture);
		// サイズ
		Sprite::SetSize({ m_size.x, m_size.y });	// これいる？　分からん

		Sprite::SetColor(m_color);
		// 描画
		Sprite::Draw();
		Sprite::SetColor({ 1,1,1,1 });
	}
	/*DirectX::XMStoreFloat4x4(&m_PlaneMat[0], DirectX::XMMatrixIdentity());
	m_PlaneMat[1] = CCameraBase::GetPrimaryViewMatrix();
	m_PlaneMat[2] = CCameraBase::GetPrimaryProjectionMatrix();
	m_pConstantWVP->Write(m_PlaneMat);*/
}

void ProducePlane::SetProducePlaneInformation(DirectX::XMFLOAT3 center, DirectX::XMFLOAT3 size, DirectX::XMFLOAT3 rot)
{
	// 画像の中心の座標を設定
	m_pos.x = center.x;
	m_pos.y = center.y;
	m_pos.z = center.z;

	// 画像のサイズを設定
	m_size.x = size.x;
	m_size.y = size.y;

	// 画像の角度を設定
	m_rot.x = DirectX::XMConvertToRadians(rot.x);
	m_rot.y = DirectX::XMConvertToRadians(rot.y);
	m_rot.z = DirectX::XMConvertToRadians(rot.z);
}

void ProducePlane::SetEnable(bool isDraw)
{
	m_IsDarw = isDraw;
}

void ProducePlane::SetColor(float r, float g, float b, float a)
{
	m_color = { r, g, b, a };
}

void ProducePlane::SetColor255(int r, int g, int b, int a)
{
	m_color =
	{
		r / 255.f,
		g / 255.f,
		b / 255.f,
		a / 255.f,
	};
}
