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
	// �f�o�b�O�E�B���h�E�̏���
	static void Close();

	static void SetCreator();

	//template<typename First, typename... A>
	//static std::string Print(CreatorTag tag, const char* src, First first, A... args);

	static void Print(CreatorTag tag, const char* src);
	static void Print(CreatorTag tag, const char* label, int data);
	static void Print(CreatorTag tag, const char* label, float data);
	//static void Print(CreatorTag tag, std::string label, bool data);
	static void Print(CreatorTag tag, const char* label, DirectX::XMFLOAT3 data);
	static void Print(CreatorTag tag, const char* label, DirectX::XMVECTOR data);
	static void Print(CreatorTag tag, const char* label, DirectX::XMMATRIX data);
private:
	static FILE* m_fp;
	static CreatorTag m_creator;
};

// Printf�Ƒ�̓����ɐݒ肵�Ă���܂��B
// �g�p�\�t�H�[�}�b�g�w��q�i%�̌�Ɂj
// d:�����l
// f:�����l�i�����_�ȉ�4�ʌŒ�j
// s:������
//

//template<typename First, typename... A>
//std::string CDebugWindow::Print(CreatorTag tag, const char* src, First first, A... args)
//{
//#ifdef DEBUG
//	std::string str;
//	while (src != '\0')
//	{
//		if (*src == '%')
//		{
//			src++;
//			switch (*src)
//			{
//			case 'd':
//			case 'D':
//				str += std::to_string(first);
//				src++;
//				str += Print(tag, src, args...);
//				break;
//			case 'f':
//			case 'F':
//				//str += std::_Floating_to_string("%.4f",first);
//				str += std::to_string(first);
//
//				src++;
//				str += Print(tag, src, args...);
//				break;
//			case 'c':
//			case 'C':
//				str += first;
//				src++;
//				str += Print(tag, src, args...);
//				break;
//			}
//		}
//		str += *src;
//		src++;
//	}
//#endif // _DEBUG
//
//}
