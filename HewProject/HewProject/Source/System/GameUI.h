#ifndef  __GAME_UI_H__
#define  __GAME_UI_H__

#include "DirectX.h"
#include "Sprite.h"
#include "DirectXTex/Texture.h"
#include <memory>
class CGameUI
{
public:
	using Ptr = std::shared_ptr<CGameUI>;
public:
	CGameUI(const char*);
	~CGameUI();
	void Draw();

	// �T�v : �摜�̍��W��ݒ�
	//		: ��ʍ��[�̍��W : 0.f
	//		: ��ʉE�[�̍��W : 1280.f
	//		: ��ʉ��[�̍��W : 720.f	
	//		: ��ʏ�[�̍��W : 0.f
	// �ߒl : �Ȃ�
	// ���� : DirectX::XMFLOAT2 pos : �摜�̍��W(��ʂ̍��W���Q�l�ɂ��Đݒ肵�Ă�������) 
	void SetPos(DirectX::XMFLOAT2 pos);

	// �T�v : �摜�̃T�C�Y��ݒ�
	// �ߒl : �Ȃ�
	// ���� : DirectX::XMFLOAT2 size : �摜�̃T�C�Y(�l��-�ɂ���Ɣ��]���܂�)
	void SetSize(DirectX::XMFLOAT2 size);

private:
	ID3D11ShaderResourceView* m_pPicture;	// �摜
	DirectX::XMFLOAT2 m_pos;				// �摜�̍��W(HP�o�[�̂悤�ɏ�ɉ�ʂɒ���t���悤�ɕ`�悷��̂�Z���͂Ȃ�)
	DirectX::XMFLOAT2 m_size;				// �摜�̃T�C�Y(Y���̒l��-�ɂ���Ɣ��])
};
#endif // ! __GAME_UI_H__

