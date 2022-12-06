#include  "Billboard.h"

CBillboard::CBillboard(const char* FileName)
{
	LoadTextureFromFile(FileName, &m_pPicture);

}

CBillboard::~CBillboard()
{
	m_pPicture->Release();
}


void CBillboard::Draw(DirectX::XMFLOAT4X4 view, DirectX::XMFLOAT4X4 proj, DirectX::XMFLOAT3 pos, DirectX::XMFLOAT2 size, bool BillOnOff, bool enable, float rot)
{
	// ビュー行列セット
	Sprite::SetView(view);
	// プロジェクション行列セット
	Sprite::SetProjection(proj);

	// ワールド行列
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
	DirectX::XMFLOAT4X4 world;

	// ビルボードオン
	if (BillOnOff)
	{
		DirectX::XMFLOAT4X4 inv; // 逆行列の格納先
		inv = view;
		// 転置されている行列なので、一度元に戻す
		DirectX::XMMATRIX matInv = DirectX::XMLoadFloat4x4(&inv);
		matInv = DirectX::XMMatrixTranspose(matInv);
		// 移動成分は打ち消す必要がないので0を設定して移動を無視する
		DirectX::XMStoreFloat4x4(&inv, matInv);
		inv._41 = inv._42 = inv._43 = 0.f;
		// 逆行列の計算はXMMATRIX型で行う
		matInv = DirectX::XMLoadFloat4x4(&inv);
		matInv = DirectX::XMMatrixInverse(nullptr, matInv);
		DirectX::XMStoreFloat4x4(&world, DirectX::XMMatrixTranspose(matInv * T));
	}
	// ビルボードオフ
	else
	{
		DirectX::XMMATRIX R = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(rot));
		DirectX::XMStoreFloat4x4(&world, DirectX::XMMatrixTranspose(R * T));
	}

	// ワールド行列セット
	Sprite::SetWorld(world);
	// テクスチャセット
	Sprite::SetTexture(m_pPicture);
	// サイズ
	Sprite::SetSize(size);
	// 深度バッファ
	EnableDepth(enable);
	Sprite::Draw();
	EnableDepth(true);

}