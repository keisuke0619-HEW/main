#pragma once
#include <IObjectBase.hpp>
#include <memory>

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
#define AddVector3(v1, v2) v1.x += v2.x; v1.y += v2.y; v1.z += v2.z;

	// �폜�̍ۂɌĂяo�����
	virtual void Finalize();

	// �I�u�W�F�N�g���
	TObjectParam m_param;
	TModelData m_modelData;
	void LoadModel(const char* src, float scale, bool isFlip, TModelData* modelData);
};