#pragma once
#include <Windows.h>

// ����
// 
// ���s���邩�ǂ����̕ϐ��A�֐�
// <�o�b�t�@�ɏ�������ň�C�Ƀv�����g>�Ȃ��H
// �s��I�����ď㏑���`��
//		ConioEX::clrLine�Q��
// 
//

class CDebugWindow
{
public:
	// �f�o�b�O�E�B���h�E�̍쐬
	static void Create();

	template<class... A>
	static void Print(const char* src, A... args);

};

template<class ...A>
inline void CDebugWindow::Print(const char* src, A ...args)
{

}
