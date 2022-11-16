#include "Model.h"

VertexShader* Model::m_pDefVS = nullptr;
PixelShader* Model::m_pDefPS = nullptr;
unsigned int Model::m_shaderRef = 0;
std::map<const char*, Model::ModelData> Model::m_staticModels;

//--- プロトタイプ宣言
void MakeModelDefaultShader(VertexShader** vs, PixelShader** ps);

void Model::Release(const char* src)
{
	if (m_staticModels.count(src) == 0)
		return;
	for (unsigned int i = 0; i < m_staticModels[src].meshNum; ++i)
	{
		delete[] m_staticModels[src].meshes[i].pVertices;
		delete[] m_staticModels[src].meshes[i].pIndices;
		delete m_staticModels[src].meshes[i].pMesh;
	}
	if (m_staticModels[src].meshes) {
		delete[] m_staticModels[src].meshes;
	}
	for (unsigned int i = 0; i < m_staticModels[src].materialNum; ++i)
	{
		if (m_staticModels[src].materials[i].pTexture)
			m_staticModels[src].materials[i].pTexture->Release();
	}
	if (m_staticModels[src].materials) {
		delete[] m_staticModels[src].materials;
	}
	m_staticModels.erase(src);
}

Model::Model()
{
	m_model.meshNum = 0;
	m_model.meshes = nullptr;
	m_model.materialNum = 0;
	m_model.materials = nullptr;


	if (m_shaderRef == 0)
	{
		MakeModelDefaultShader(&m_pDefVS, &m_pDefPS);
	}
	m_pVS = m_pDefVS;
	m_pPS = m_pDefPS;
	++m_shaderRef;
}
Model::~Model()
{

	--m_shaderRef;
	if (m_shaderRef <= 0)
	{
		delete m_pDefPS;
		delete m_pDefVS;
	}
}

void Model::SetVertexShader(VertexShader* vs)
{
	m_pVS = vs;
}
void Model::SetPixelShader(PixelShader* ps)
{
	m_pPS = ps;
}
const Model::Mesh* Model::GetMesh(unsigned int index)
{
	if (index >= GetMeshNum())
	{
		return &m_model.meshes[index];
	}
	return nullptr;
}
uint32_t Model::GetMeshNum()
{
	return m_model.meshNum;
}


void MakeModelDefaultShader(VertexShader** vs, PixelShader** ps)
{
	const char* ModelVS = R"EOT(
struct VS_IN {
	float3 pos : POSITION0;
	float2 uv : TEXCOORD0;
};
struct VS_OUT {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
};
VS_OUT main(VS_IN vin) {
	VS_OUT vout;
	vout.pos = float4(vin.pos, 1.0f);
	vout.pos.z += 0.5f;
	vout.pos.y -= 0.8f;
	vout.uv = vin.uv;
	return vout;
})EOT";
	const char* ModelPS = R"EOT(
struct PS_IN {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
};
Texture2D tex : register(t0);
SamplerState samp : register(s0);
float4 main(PS_IN pin) : SV_TARGET
{
	return tex.Sample(samp, pin.uv);
})EOT";
	*vs = new VertexShader();
	(*vs)->Compile(ModelVS);
	*ps = new PixelShader();
	(*ps)->Compile(ModelPS);
}