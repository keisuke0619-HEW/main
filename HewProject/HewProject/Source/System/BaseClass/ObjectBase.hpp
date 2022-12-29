#pragma once
#include <IObjectBase.hpp>
#include <memory>
#include <Model.h>
#include <ConstantBuffer.h>

/// <summary>
/// ���ׂĂ�3D�I�u�W�F�N�g�̊��ƂȂ�N���X
/// </summary>
class CObjectBase : public IObjectBase
{
public:
	// ���R���X�g���N�^
	CObjectBase(const char* src = "", float scale = 1.0f, bool isFlip = false, std::string name = "no_name");
	// ���z�f�X�g���N�^
	virtual ~CObjectBase();

	// �V�X�e������Ăяo�����A�b�v�f�[�g
	void BaseUpdate()override final;
	// �V�X�e������Ăяo�����h���[
	void BaseDraw() override final;
	// �I�u�W�F�N�g�ƏՓ˂��Ă�����Ăяo�����
	void OnCollision(Ptr collisionObj) override;
	void OnCollisionTag(EObjectTag tag) override;

	// �p�����[�^�擾
	TObjectParam GetParam() override final;

	// ���t���[���̍X�V�����i�K�������j
	virtual void Update() = 0;
	// ���t���[���̕`�揈���i�f�t�H���g�ݒ���g���ꍇ�͎����s�v�j
	virtual void Draw();

	void Destroy();
protected:
	// �폜�̍ۂɌĂяo�����
	virtual void Finalize();

	// �I�u�W�F�N�g���
	TObjectParam m_param;
	// ���f�����
	std::shared_ptr<Model> m_model;
	// ���_�o�b�t�@���
	std::shared_ptr<VertexShader> m_vs;
	// ���[���h�r���[�萔�o�b�t�@
	std::shared_ptr<ConstantBuffer> m_wvp;

	void LoadModel(const char* src, float scale, bool isFlip, std::shared_ptr<Model>* pModel, std::shared_ptr<VertexShader>* pVS, std::shared_ptr<ConstantBuffer>* pWVP);
};