#ifndef __MODEL_H__
#define __MODEL_H__

#include <DirectXMath.h>
#include "Shader.h"
#include "MeshBuffer.h"
#include <map>
class Model
{
public:
	struct Vertex
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT2 uv;
	};
	struct Material
	{
		DirectX::XMFLOAT4 diffuse;
		DirectX::XMFLOAT4 ambient;
		DirectX::XMFLOAT4 specular;
		ID3D11ShaderResourceView* pTexture;
	};
	struct Mesh
	{
		Vertex* pVertices;
		unsigned int vertexNum;
		unsigned int* pIndices;
		unsigned int indexNum;
		unsigned int materialID;
		MeshBuffer* pMesh;
	};
	struct ModelData
	{
		Mesh* meshes;
		unsigned int meshNum;
		Material* materials;
		unsigned int materialNum;

	};
public:
	static void Release(const char* src);
public:
	Model();
	~Model();

	bool Load(const char* file, float scale = 1.0f, bool flip = false);
	void Draw();

	void SetVertexShader(VertexShader* vs);
	void SetPixelShader(PixelShader* ps);

	const Mesh* GetMesh(unsigned int index);
	unsigned int GetMeshNum();

	void SetTranslate(float x, float y, float z);
	void SetRotation(float x, float y, float z);
private:
	static VertexShader* m_pDefVS;
	static PixelShader* m_pDefPS;
	static unsigned int m_shaderRef;
	static std::map<const char*, ModelData> m_staticModels;
private:
	ModelData m_model;
	VertexShader* m_pVS;
	PixelShader* m_pPS;
};


#endif // __MODEL_H__