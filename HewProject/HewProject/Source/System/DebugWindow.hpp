#pragma once
#include <Windows.h>
#include <stdio.h>
#include <string>
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
	SSK,
};


class CDebugWindow
{
public:
	// �f�o�b�O�E�B���h�E�̍쐬
	static void Create();
	// �f�o�b�O�E�B���h�E�̏���
	static void Close();


	template<class... A>
	static void Print(CreatorTag tag, const char* src, A... args);

private:
	static FILE* m_fp;
};

// Printf�Ƒ�̓����ɐݒ肵�Ă���܂��B
// �g�p�\�t�H�[�}�b�g�w��q�i%�̌�Ɂj
// d:�����l
// f:�����l�i�����_�ȉ�4�ʌŒ�j
// s:������
//
//
template<class ...A>
inline void CDebugWindow::Print(CreatorTag tag,const char* src, A ...args)
{
#ifdef _DEBUG
	std::string str;
	while (src != '\0')
	{
		if (*src == '%')
		{
			src++;
			switch (*src)
			{
			case 'd':
				break;

			}
		}
		str += *src;
		src++;
	}
#endif // _DEBUG

}
