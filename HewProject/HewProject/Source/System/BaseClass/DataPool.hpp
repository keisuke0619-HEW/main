#pragma once

#include <memory>
#include <Model.h>
#include <string>
#include <map>
/// <summary>
/// ���f���f�[�^��摜�f�[�^��ۑ����Ă����N���X�B�V���O���g���B
/// </summary>
class CDataPool
{
	// �V���O���g���@�\
public:
	static std::shared_ptr<CDataPool> GetIns();
	static void CreateIns();
	static void Destroy();
	~CDataPool();
private:
	static std::shared_ptr<CDataPool> m_ins;
	CDataPool();

	// �����@�\
public:
	/// <summary>
	/// ���f�������擾
	/// </summary>
	/// <param name="src">���f���\�[�X</param>
	/// <returns>�\�[�X�����݂����烂�f���f�[�^�B���Ȃ�������BOX</returns>
	Model GetModel(const char* src, float scale = 1.0f, bool flip = false);
private:
	const char* NULL_MODEL_SOURCE;
	std::map<const char*, std::unique_ptr<Model>> m_models;
};