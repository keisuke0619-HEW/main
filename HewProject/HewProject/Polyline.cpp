#include "Polyline.h"

GeometoryPolyline::GeometoryPolyline(int pointNum)
	: m_pTexture(nullptr)
{
	const char* VS = R"EOT(
struct VS_IN {
	float3 pos : POSITION0;
	float2 uv : TEXCOORD0;
	float4 color : COLOR0;
};
struct VS_OUT {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
	float4 color : COLOR0;
};
cbuffer Matrix : register(b0) {
	float4x4 view;
	float4x4 proj;
};
VS_OUT main(VS_IN vin) {
	VS_OUT vout;
	vout.pos = float4(vin.pos, 1.0f);
	vout.pos = mul(vout.pos, view);
	vout.pos = mul(vout.pos, proj);
	vout.uv = vin.uv;
	vout.color = vin.color;
	return vout;
})EOT";
	const char* PS = R"EOT(
struct PS_IN {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
	float4 color : COLOR0;
};
Texture2D tex : register(t0);
SamplerState samp : register(s0);
float4 main(PS_IN pin) : SV_TARGET {
	return tex.Sample(samp, pin.uv);//* pin.color;
})EOT";

	if (pointNum < 2)
	{
		pointNum = 2;
	}
	m_points.resize(pointNum);

	int vtxNum = pointNum * 2;
	m_pVertices = new Vertex[vtxNum];
	for (int i = 0; i < vtxNum; ++i)
	{
		m_pVertices[i].uv = 
		DirectX::XMFLOAT2(i / (vtxNum - 1.0f),
			i%2);
		m_pVertices[i].color =
			DirectX::XMFLOAT4(1.0f, 1.0f,
				1.0f, 1.0f);
	}

	MeshBuffer::Description desc = {};
	desc.pVtx = m_pVertices;
	desc.vtxCount = vtxNum;
	desc.vtxSize = sizeof(Vertex);
	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
	desc.isWrite = true;
	m_pMesh = new MeshBuffer(desc);

	HRESULT hr;
	m_pVS = new VertexShader();
	hr = m_pVS->Compile(VS);
	m_pPS = new PixelShader();
	hr = m_pPS->Compile(PS);
	m_pDefPS = m_pPS;

	m_pBuf = new ConstantBuffer();
	m_pBuf->Create(sizeof(m_matrix));

	DirectX::XMStoreFloat4x4(&m_matrix[0], DirectX::XMMatrixIdentity());
	DirectX::XMStoreFloat4x4(&m_matrix[1], DirectX::XMMatrixIdentity());
}
GeometoryPolyline::~GeometoryPolyline()
{
	delete m_pBuf;
	delete m_pDefPS;
	delete m_pVS;
	delete[] m_pVertices;
	delete m_pMesh;
}
void GeometoryPolyline::Draw()
{
	CalcVertex();

	m_pVS->Bind();
	m_pPS->Bind();
	m_pBuf->Write(m_matrix);
	m_pBuf->BindVS(0);
	m_pMesh->Write(m_pVertices);
	m_pMesh->Draw();
}

void GeometoryPolyline::SetPoint(int index, Point point)
{
	if (0 <= index && index < m_points.size())
	{
		m_points[index] = point;
	}
}
void GeometoryPolyline::PushPoint(Point point)
{
	for (int i = m_points.size() - 1; i > 0; --i)
	{
		m_points[i] = m_points[i - 1];
	}
	m_points[0] = point;
}
GeometoryPolyline::Point GeometoryPolyline::GetPoint(int index)
{
	Point out = {};
	if (0 <= index && index < m_points.size())
	{
		out = m_points[index];
	}
	return out;
}
int GeometoryPolyline::GetPointNum()
{
	return m_points.size();
}
void GeometoryPolyline::SetTexture(ID3D11ShaderResourceView* pTex)
{
	m_pTexture = pTex;
}
void GeometoryPolyline::SetView(DirectX::XMFLOAT4X4 view)
{
	m_matrix[0] = view;
}
void GeometoryPolyline::SetProjection(DirectX::XMFLOAT4X4 proj)
{
	m_matrix[1] = proj;
}
void GeometoryPolyline::SetPixelShader(PixelShader* pPS)
{
	m_pPS = pPS;
}
void GeometoryPolyline::SetDefaultPixelShader()
{
	m_pPS = m_pDefPS;
}

void GeometoryPolyline::CalcVertex()
{
	//開始地点の計算
	DirectX::XMVECTOR vCenter =
		DirectX::XMLoadFloat3(&m_points[0].pos);
	DirectX::XMVECTOR vNext =
		DirectX::XMLoadFloat3(&m_points[1].pos);
	DirectX::XMVECTOR vVec =
		DirectX::XMVectorSubtract(vNext, vCenter);
	DirectX::XMVECTOR vNormal =
		DirectX::XMLoadFloat3(&m_points[0].normal);

	//外積計算前に正規化
	vVec = DirectX::XMVector3Normalize(vVec);
	vNormal = DirectX::XMVector3Normalize(vNormal);
	//外積の計算での計算で垂直なベクトル
	DirectX::XMVECTOR vCross =
		DirectX::XMVector3Cross(vVec, vNormal);
	vCross = DirectX::XMVector3Normalize(vCross);
	//垂直なベクトルから頂点計算
	DirectX::XMStoreFloat3(&m_pVertices[0].pos,
		DirectX::XMVectorAdd(vCenter,
			DirectX::XMVectorScale(vCross, 
				m_points[0].width*-0.5f)));

	DirectX::XMStoreFloat3(&m_pVertices[1].pos,
		DirectX::XMVectorAdd(vCenter,
			DirectX::XMVectorScale(vCross, 
				m_points[0].width*0.5f)));

	//中間地点の計算
	DirectX::XMVECTOR vPrev = vCenter;
	vCenter = vNext;
	for (int i = 0; i < m_points.size() - 1; ++i)
	{
		DirectX::XMFLOAT3 debugpos;
		DirectX::XMStoreFloat3(&debugpos, vCenter);
		vNext = DirectX::XMLoadFloat3
		(&m_points[i + 1].pos);
		//正規化
		vVec = DirectX::XMVectorSubtract
		(vNext, vPrev);
		vNormal = DirectX::XMLoadFloat3
		(&m_points[i].normal);
		//外積
		vCross = DirectX::XMVector3Cross(vVec, vNormal);
		vCross = DirectX::XMVector3Normalize(vCross);
		//
		DirectX::XMStoreFloat3(&m_pVertices[i * 2 + 0].pos,
			DirectX::XMVectorAdd(vCenter, DirectX::XMVectorScale(vCross, m_points[i].width*-0.5f)));
		DirectX::XMStoreFloat3(&m_pVertices[i * 2 + 1].pos,
			DirectX::XMVectorAdd(vCenter, DirectX::XMVectorScale(vCross, m_points[i].width*0.5f)));

		//次の計算のじゅうんび
		vPrev = vCenter;
		vCenter = vNext;


	}

	//終了地点の計算

	vVec = DirectX::XMVectorSubtract(vCenter, vPrev);
	vNormal = DirectX::XMLoadFloat3(
		&m_points.back().normal);
	//正規化
	vVec = DirectX::XMVector3Normalize(vVec);
	vNormal = DirectX::XMVector3Normalize(vNormal);
	vCross = DirectX::XMVector3Cross(vVec, vNormal);
	vCross = DirectX::XMVector3Normalize(vCross);
	DirectX::XMStoreFloat3(
		&m_pVertices[m_points.size() * 2 - 2].pos,
		DirectX::XMVectorAdd(vCenter, DirectX::XMVectorScale(vCross, m_points.back().width*-0.5f)));

	DirectX::XMStoreFloat3(
		&m_pVertices[m_points.size() * 2 - 1].pos,
		DirectX::XMVectorAdd(vCenter, DirectX::XMVectorScale(vCross, m_points.back().width *  0.5f))
	);
	

}
