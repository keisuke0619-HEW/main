#pragma once
#include <Windows.h>
#include <stdio.h>
#include <string>
#include <DirectXMath.h>
// ����
// 
// ���s���邩�ǂ����̕ϐ��A�֐�
// <�o�b�t�@�ɏ�������ň�C�Ƀv�����g>�Ȃ��H
// �s��I�����ď㏑���`��
//		ConioEX::clrLine�Q��
// 
//

enum CreatorTag
{
	NULL_CREATOR,
	ShibataOsuke,
	SatoShunma,
	HiranoYuki,
	ShimizuKeisuke,
	SatoKenta,
	TsuchiyaShouya,
	HaraHirotaka,
	HikosakaAoto,
	IkegamiRenta,
	HoriKurumi,
	MasutaRintaro,
};

//#define DebugPrint(name, func) if(name == CreatorTag::ShimizuKeisuke)func;

class CDebugWindow
{
public:
	// �f�o�b�O�E�B���h�E�̍쐬
	static void Create();
	// �f�o�b�O�E�B���h�E�̉��
	static void Close();

	/// <summary>
	/// �f�o�b�O�E�B���h�E�ɕ������\�����܂��B���Sprintf�Ȃǂŕ�������쐬���Ă��������B
	/// </summary>
	/// <param name="tag">�����̃N���G�C�^�[�^�O</param>
	/// <param name="src">�\�����镶����</param>
	static void Print(CreatorTag tag, const char* src);
	/// <summary>
	/// �f�o�b�O�E�B���h�E�ɐ����p�̃��x���Ɛ�����\�����܂�
	/// </summary>
	/// <param name="tag">�����̃N���G�C�^�[�^�O</param>
	/// <param name="label">���̕ϐ����������郉�x��</param>
	/// <param name="data">�\�����鐮���l</param>
	static void Print(CreatorTag tag, const char* label, int data);
	/// <summary>
	/// �f�o�b�O�E�B���h�E�ɐ����p�̃��x���Ǝ�����\�����܂�
	/// </summary>
	/// <param name="tag">�����̃N���G�C�^�[�^�O</param>
	/// <param name="label">���̕ϐ����������郉�x��</param>
	/// <param name="data">�\����������l</param>
	static void Print(CreatorTag tag, const char* label, float data);
	/// <summary>
	/// �f�o�b�O�E�B���h�E�ɐ����p�̃��x����Float3�̒l��\�����܂�
	/// </summary>
	/// <param name="tag">�����̃N���G�C�^�[�^�O</param>
	/// <param name="label">���̕ϐ����������郉�x��</param>
	/// <param name="data">�\������Float3</param>
	static void Print(CreatorTag tag, const char* label, DirectX::XMFLOAT3 data);
	/// <summary>
	/// �f�o�b�O�E�B���h�E�ɐ����p�̃��x����3�����x�N�g���̒l��\�����܂�
	/// </summary>
	/// <param name="tag">�����̃N���G�C�^�[�^�O</param>
	/// <param name="label">���̕ϐ����������郉�x��</param>
	/// <param name="data">�\������R�����x�N�g���f�[�^</param>
	static void Print(CreatorTag tag, const char* label, DirectX::XMVECTOR data);
	/// <summary>
	/// �f�o�b�O�E�B���h�E�ɐ����p�̃��x���ƂS���S�s���\�����܂�
	/// </summary>
	/// <param name="tag">�����̃N���G�C�^�[�^�O</param>
	/// <param name="label">���̕ϐ����������郉�x��</param>
	/// <param name="data">�\������S���S�s��</param>
	static void Print(CreatorTag tag, const char* label, DirectX::XMMATRIX data);

private:
	static FILE* m_fp;
	static CreatorTag m_creator;
	static bool m_enable;

	static void SetCreator();
	static void SetEnable();
};
