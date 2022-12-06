#ifndef __BILLBOARD_H__
#define __BILLBOARD_H__

#include "DirectX.h"
#include "Sprite.h"
#include "DirectXTex/Texture.h"

class CBillboard
{
public:
	CBillboard(const char*);
	~CBillboard();

	// �T�v : 2D�`��
	// �ߒl : �Ȃ�
	// ���� : DirectX::XMFLOAT4X4 view	: �J�����̃r���[�s��
	//		  DirectX::XMFLOAT4X4 proj	: �J�����̃v���W�F�N�V�����s��
	//		  DirectX::XMFLOAT3 pos		: �\������摜�̍��W
	//		  DirectX::XMFLOAT2 size	: �\������摜�̃T�C�Y
	//		  bool BillOnOff			: �r���{�[�h�̃I���I�t
	//		  bool enable				: �[�x�o�b�t�@�̂Ȃ�Ƃ�(flase�ɂ���ƕ\�����ꂽ�摜����O�ɕ`�悳���)
	//		  float rot					: �\������摜�̊p�x(�x���@)(�r���{�[�h���I���̎��͕K�v�Ȃ�)
	void Draw(DirectX::XMFLOAT4X4 view, DirectX::XMFLOAT4X4 proj, DirectX::XMFLOAT3 pos, DirectX::XMFLOAT2 size, bool BillOnOff, bool enable, float rot = 0.f);

private:
	ID3D11ShaderResourceView* m_pPicture;
};


#endif // !__BILLBOARD_H__
