#include "GameUI.h"
#include "Sprite.h"
#include "DirectXTex/Texture.h"

CGameUI::CGameUI()
{
	LoadTextureFromFile("Assets/MagicaBoxelModel/PlaneBox.png", &m_pBar);
}

CGameUI::~CGameUI()
{
	m_pBar->Release();
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
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(1100.f, 680.f, 0.f);
	DirectX::XMFLOAT4X4 fWorld;
	DirectX::XMStoreFloat4x4(&fWorld, DirectX::XMMatrixTranspose(T));

	// スプライトの設定
	Sprite::SetWorld(fWorld);
	Sprite::SetView(fView);
	Sprite::SetProjection(fProj);
	Sprite::SetSize(DirectX::XMFLOAT2(300.f, -20.f)); // Y軸の値を-にすると反転
	Sprite::SetTexture(m_pBar);
	Sprite::Draw();
}