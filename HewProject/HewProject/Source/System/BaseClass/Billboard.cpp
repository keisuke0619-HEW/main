#include  "Billboard.h"
#include <Camera.hpp>
#include <Blend.hpp>
std::list<CBillboard*> CBillboard::m_billList;
std::map<const char*, ID3D11ShaderResourceView*> CBillboard::m_billImg;


void CBillboard::DrawAll()
{
	for (auto itr = m_billList.begin(); itr != m_billList.end(); itr++)
	{
		(*itr)->Draw();
	}
}
void CBillboard::ClearBillboard()
{
	auto itr = m_billImg.begin();
	while (itr != m_billImg.end())
	{
		(itr->second)->Release();
		itr++;
	}
	m_billImg.clear();
}
CBillboard::CBillboard(const char* FileName)
	: m_pos(0.f, 0.f, 0.f)
	, m_playerPos(0.f, 0.f, 0.f)
	, m_size(1.f, 1.f)
	, m_distance(4.f)
	, m_rot(0.f)
	, m_isUseUniqueViewProj(false)
{
	if (m_billImg.count(FileName) == 0)
	{
		LoadTextureFromFile(FileName, &m_pPicture);
		m_billImg[FileName] = m_pPicture;
	}
	else
	{
		m_pPicture = m_billImg[FileName];
	}
	m_billList.push_back(this);
}

CBillboard::~CBillboard()
{
	m_billList.remove(this);
}


void CBillboard::Draw(bool BillOnOff, bool enable)
{
	
	if (m_isUseUniqueViewProj == false)
	{
		// ビュー行列セット
		m_view = CCameraBase::GetPrimaryViewMatrix();
		// プロジェクション行列セット
		m_proj = CCameraBase::GetPrimaryProjectionMatrix();
	}
	// ビュー行列セット
	Sprite::SetView(m_view);
	// プロジェクション行列セット
	Sprite::SetProjection(m_proj);
	// ワールド行列
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
	DirectX::XMFLOAT4X4 world;
	// ビルボードオン
	if (BillOnOff)
	{
		DirectX::XMFLOAT4X4 inv; // 逆行列の格納先
		inv = m_view;
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
		DirectX::XMMATRIX R = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(m_rot));
		DirectX::XMStoreFloat4x4(&world, DirectX::XMMatrixTranspose(R * T));
	}

	// ワールド行列セット
	Sprite::SetWorld(world);
	// テクスチャセット
	Sprite::SetTexture(m_pPicture);
	// サイズ
	Sprite::SetSize(m_size);
	




	if (!enable)
	{
		// プレイヤーと画像の位置情報
		DirectX::XMVECTOR enemy = DirectX::XMLoadFloat3(&m_pos);
		DirectX::XMVECTOR player = DirectX::XMLoadFloat3(&m_playerPos);

		// 距離を計算
		DirectX::XMVECTOR distance = DirectX::XMVectorSubtract(player, enemy);

		// float3に変換して格納
		DirectX::XMFLOAT3 movePos;
		DirectX::XMStoreFloat3(&movePos, distance);
		// 画像が手前に表示される距離
		float disPlayer = m_distance;
		// プレイヤーと画像が一以上離れているか確認
		if (fabsf(movePos.x) <= disPlayer && fabsf(movePos.y) <= disPlayer && fabsf(movePos.z) <= disPlayer)
		{
			// 一定以上近くにいたら画像を手前に表示する
			EnableDepth(enable);
		}
	}

	Utility::SetBlendState(BLEND_ALPHA);
	Sprite::Draw();
	EnableDepth(true);
	Utility::SetBlendState(BLEND_NONE);

}

void CBillboard::SetPosViewProj(DirectX::XMFLOAT4X4 view, DirectX::XMFLOAT4X4 proj)
{
	m_isUseUniqueViewProj = true;
	m_view = view;
	m_proj = proj;
}

void CBillboard::SetPos(DirectX::XMFLOAT3 pos)
{
	m_pos = pos;
}

void CBillboard::SetPlayerrPos(DirectX::XMFLOAT3 playerPos, float distance)
{
	m_playerPos = playerPos;
	m_distance = distance;
}

void CBillboard::SetSize(DirectX::XMFLOAT2 size)
{
	m_size = size;
}

void CBillboard::SetRotation(float rot)
{
	m_rot = rot;
}