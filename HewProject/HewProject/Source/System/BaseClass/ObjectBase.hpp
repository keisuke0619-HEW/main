#pragma once
#include <ObjectToManagerInterface.hpp>
#include <memory>
#include <Model.h>
#include <ConstantBuffer.h>

/// <summary>
/// ���ׂĂ�3D�I�u�W�F�N�g�̊��ƂȂ�N���X
/// </summary>
class CObjectBase : IObjectToManager
{
public:
	// ���R���X�g���N�^
	CObjectBase();
	// ���z�f�X�g���N�^
	virtual ~CObjectBase();

	// �V�X�e������Ăяo�����A�b�v�f�[�g
	void UpdateBase()override final;
	// �V�X�e������Ăяo�����h���[
	void DrawBase() override final;
	// �p�����[�^�擾
	TObjectParam GetParam() override final;

	// ���t���[���̍X�V�����i�K�������j
	virtual void Update() = 0;
	// ���t���[���̕`�揈���i�f�t�H���g�ݒ���g���ꍇ�͎����s�v�j
	virtual void Draw();

protected:
	// �I�u�W�F�N�g���
	TObjectParam m_param;
	// ���f�����
	std::shared_ptr<Model> m_model;
	// ���_�o�b�t�@���
	std::unique_ptr<VertexShader> m_vs;
	// ���[���h�r���[�萔�o�b�t�@
	std::unique_ptr<ConstantBuffer> m_wvp;
};