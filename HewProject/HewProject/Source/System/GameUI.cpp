#include "GameUI.h"
#include <Blend.hpp>
CGameUI::CGameUI(const char* FileName)
	: m_pos(0.f, 0.f)
	, m_size(1.f, 1.f)
	, m_sort(SORT_ORDER_DEFAULT)
	, m_rot(0.0f)
	, m_uvPos({0,0})
	, m_uvScale({1,1})
	, m_color({1,1,1,1})
{
	LoadTextureFromFile(FileName, &m_pPicture);
	m_fileName = FileName;
}

CGameUI::~CGameUI()
{
	m_pPicture->Release();
}

void CGameUI::Draw()
{
	// "D表示のための行列を設定
	// 1.ビュー行列はカメラが関係ないので、初期化されている行列を使う(単位行列)
	DirectX::XMFLOAT4X4 fView;
	DirectX::XMStoreFloat4x4(&fView, DirectX::XMMatrixIdentity());
	// 2.プロジェクション行列が重要
	// この行列で2Dのスクリーンの大きさを決める
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

	// ワールド行列で画面の表示位置を計算
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, 0.f);
	DirectX::XMMATRIX R = DirectX::XMMatrixRotationZ(m_rot);
	DirectX::XMFLOAT4X4 fWorld;
	DirectX::XMStoreFloat4x4(&fWorld, DirectX::XMMatrixTranspose(R * T));

	// スプライトの設定
	Sprite::SetWorld(fWorld);
	Sprite::SetView(fView);
	Sprite::SetProjection(fProj);
	auto tmpSize = m_size;
	tmpSize.y *= -1;
	Sprite::SetSize(tmpSize);
	Sprite::SetTexture(m_pPicture);
	Sprite::SetUVPos(m_uvPos);
	Sprite::SetUVScale(m_uvScale);
	Sprite::SetColor(m_color);
	EnableDepth(false);
	Sprite::Draw();
	EnableDepth(true);
	Sprite::SetUVPos({0,0});
	Sprite::SetUVScale({1,1});
	Sprite::SetColor({ 1,1,1,1 });
}

void CGameUI::SetPos(DirectX::XMFLOAT2 pos)
{
	m_pos = pos;
}

void CGameUI::SetPos(float x, float y)
{
	SetPos({ x, y });
}

void CGameUI::SetSize(DirectX::XMFLOAT2 size)
{
	m_size = size;
}

void CGameUI::SetSize(float x, float y)
{
	SetSize({ x,y });
}

void CGameUI::SetUVPos(DirectX::XMFLOAT2 uv)
{
	m_uvPos = uv;
}

void CGameUI::SetUVPos(float u, float v)
{
	SetUVPos({ u,v });
}

void CGameUI::SetUVScale(DirectX::XMFLOAT2 uv)
{
	m_uvScale = uv;
}

void CGameUI::SetUVScale(float u, float v)
{
	SetUVScale({ u, v });
}

void CGameUI::SetRotation(float degRot)
{
	m_rot = DirectX::XMConvertToRadians(degRot);
}

void CGameUI::SetColor(float r, float g, float b, float a)
{
	m_color = { r,g,b,a };
}

void CGameUI::SetColor255(int r, int g, int b, int a)
{
	m_color = {
		r / 255.f,
		g / 255.f,
		b / 255.f,
		a / 255.f,
	};
}

DirectX::XMFLOAT2 CGameUI::GetSize()
{
	return m_size;
}

int CGameUI::GetSortID()
{
	return m_sort;
}

void CGameUI::SetSortID(SortOrder order)
{
	m_sort = order;
}

void CGameUI::SetData(float posX, float posY, float sizeX, float sizeY)
{
	SetPos(posX, posY);
	SetSize(sizeX, sizeY);
}
