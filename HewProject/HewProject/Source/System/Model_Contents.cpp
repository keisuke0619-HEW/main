#include "Model.h"
#include "DirectXTex/Texture.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

bool Model::Load(const char* file, float scale, bool flip)
{
	if (m_staticModels.count(file) != 0)
	{
		m_model = m_staticModels[file];
		return true;
	}
	Assimp::Importer importer;
	int flag = 0;
	flag |= aiProcess_Triangulate;
	flag |= aiProcess_PreTransformVertices;
	flag |= aiProcess_JoinIdenticalVertices;
	flag |= aiProcess_FlipUVs;
	if (flip)flag |= aiProcess_MakeLeftHanded;
	// assimp�œǂݍ���
	const aiScene* pScene = importer.ReadFile(file, flag);
	if (!pScene)
	{
		MessageBox(nullptr, importer.GetErrorString(), "assimp Error", MB_OK);
		return false;
	}
	// �ǂݍ��񂾃f�[�^�����ƂɃ��b�V���̃f�[�^���m��
	m_model.meshNum = pScene->mNumMeshes;
	m_model.meshes = new Mesh[m_model.meshNum];

	// ���b�V�����Ƃɒ��_�f�[�^�A�C���f�b�N�X�f�[�^��ǂݎ��
	aiVector3D zero(0.0f, 0.0f, 0.0f);
	for (unsigned int i = 0; i < m_model.meshNum; i++)
	{
		// ���b�V�������Ƃɒ��_�̃f�[�^���m��
		m_model.meshes[i].vertexNum = pScene->mMeshes[i]->mNumVertices;
		m_model.meshes[i].pVertices = new Model::Vertex[m_model.meshes[i].vertexNum];

		// ���b�V�����̒��_�f�[�^��ǂݎ��
		for (unsigned int j = 0; j < m_model.meshes[i].vertexNum; j++)
		{
			// �l�̋z�o��
			aiVector3D pos	= pScene->mMeshes[i]->mVertices[j];
			aiVector3D uv = pScene->mMeshes[i]->HasTextureCoords(0) ?
				pScene->mMeshes[i]->mTextureCoords[0][j] : zero;

			// �l��ݒ�
			m_model.meshes[i].pVertices[j] =
			{
				DirectX::XMFLOAT3(pos.x * scale, pos.y * scale, pos.z * scale),
				DirectX::XMFLOAT2(uv.x, uv.y)
			};
		}
		// ���b�V�������ƂɃC���f�b�N�X�̃f�[�^���m��
		// mNumFace�̓|���S���̐���\���B�i�P�|���S���łR�C���f�b�N�X
		m_model.meshes[i].indexNum = pScene->mMeshes[i]->mNumFaces * 3;
		m_model.meshes[i].pIndices = new unsigned int[m_model.meshes[i].indexNum];

		// ���b�V�����̃C���f�b�N�X�f�[�^��ǂݎ��
		for (unsigned int j = 0; j < pScene->mMeshes[i]->mNumFaces; j++)
		{
			aiFace face = pScene->mMeshes[i]->mFaces[j];
			int idx = j * 3;
			m_model.meshes[i].pIndices[idx + 0] = face.mIndices[0];
			m_model.meshes[i].pIndices[idx + 1] = face.mIndices[1];
			m_model.meshes[i].pIndices[idx + 2] = face.mIndices[2];
		}

		// �}�e���A���̊��蓖��
		m_model.meshes[i].materialID = pScene->mMeshes[i]->mMaterialIndex;

		// ���b�V�������Ƃɒ��_�o�b�t�@�쐬
		MeshBuffer::Description desc = {};
		desc.pVtx = m_model.meshes[i].pVertices;
		desc.vtxSize = sizeof(Vertex);
		desc.vtxCount = m_model.meshes[i].vertexNum;
		desc.pIdx = m_model.meshes[i].pIndices;
		desc.idxSize = sizeof(unsigned int);
		desc.idxCount = m_model.meshes[i].indexNum;
		desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		m_model.meshes[i].pMesh = new MeshBuffer(desc);
	}
	std::string dir = file;
	dir = dir.substr(0, dir.find_last_of('/') + 1);	// �ǂݍ��ރt�@�C���̃p�X����t�@�C��������菜��
	// �ǂݍ��񂾃f�[�^�����ƂɃ}�e���A���̃f�[�^���m��
	m_model.materialNum = pScene->mNumMaterials;
	m_model.materials = new Material[m_model.materialNum];

	HRESULT hr;
	for (unsigned int i = 0; i < m_model.materialNum; i++)
	{
		// �e�N�X�`���̓ǂݎ��
		aiString path;
		if (pScene->mMaterials[i]->Get(AI_MATKEY_TEXTURE_DIFFUSE(0), path) == AI_SUCCESS)
		{
			hr = LoadTextureFromFile(path.C_Str(), &m_model.materials[i].pTexture);
			if (FAILED(hr))
			{
				std::string file = dir;
				file += path.C_Str();
				hr = LoadTextureFromFile(file.c_str(), &m_model.materials[i].pTexture);
			}
			if (FAILED(hr)) { return false; }
		}
		else
		{
			m_model.materials[i].pTexture = nullptr;
		}
	}
	m_staticModels[file] = m_model;
	return true;
}

void Model::Draw()
{
	m_pVS->Bind();
	m_pPS->Bind();
	for (unsigned int i = 0; i < m_model.meshNum; ++i)
	{
		SetTexturePS(m_model.materials[m_model.meshes[i].materialID].pTexture, 0);
		m_model.meshes[i].pMesh->Draw();
	}
}