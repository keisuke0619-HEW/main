#ifndef  __GAME_UI_H__
#define  __GAME_UI_H__

#include "DirectX.h"
#include "Sprite.h"
#include "DirectXTex/Texture.h"
#include <memory>

enum SortOrder
{
	SORT_ORDER_UI_FRONTEND,
	SORT_ORDER_UI_FRONT,
	SORT_ORDER_UI_FRONT1,
	SORT_ORDER_UI_FRONT2,
	SORT_ORDER_UI_FRONT3,
	SORT_ORDER_UI_FRONT4,
	SORT_ORDER_UI_DEFAULT,
	SORT_ORDER_UI_BACK,
	SORT_ORDER_UI_BACK1,
	SORT_ORDER_UI_BACK2,
	SORT_ORDER_UI_BACK3,
	SORT_ORDER_UI_BACK4,
	SORT_ORDER_UI_BACKEND,
	SORT_ORDER_FRONT,
	SORT_ORDER_DEFAULT,
	SORT_ORDER_BACK,
};
class CGameUI
{
public:
	using Ptr = std::shared_ptr<CGameUI>;
	using Ref = std::weak_ptr<CGameUI>;
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
	void SetPos(float x, float y);
	// �T�v : �摜�̃T�C�Y��ݒ�
	// �ߒl : �Ȃ�
	// ���� : DirectX::XMFLOAT2 size : �摜�̃T�C�Y(�l��-�ɂ���Ɣ��]���܂�)
	void SetSize(DirectX::XMFLOAT2 size);
	void SetSize(float x, float y);
	/// <summary>
	/// UV��ݒ�
	/// </summary>
	/// <param name="uv">�����UV���W</param>
	void SetUVPos(DirectX::XMFLOAT2 uv);
	void SetUVPos(float u, float v);
	/// <summary>
	/// UV�̑傫����ݒ�
	/// </summary>
	/// <param name="uv">UV�̑傫��</param>
	void SetUVScale(DirectX::XMFLOAT2 uv);
	void SetUVScale(float u, float v);
	/// <summary>
	/// ��]��ݒ肵�܂��B�i�x���@�j
	/// </summary>
	/// <param name="rot">��]�p�x�i�x���@�j</param>
	void SetRotation(float degRot);
	
	void SetColor(float r, float g, float b, float a = 1.0f);
	void SetColor255(int r, int g, int b, int a = 255);
	DirectX::XMFLOAT2 GetSize();

	int GetSortID();

	void SetSortID(SortOrder order);

	void SetData(float posX, float posY, float sizeX, float sizeY);

	void SetResourceView(ID3D11ShaderResourceView* pTex);

	DirectX::XMFLOAT2 GetPos();
private:
	ID3D11ShaderResourceView* m_pPicture;	// �摜
	DirectX::XMFLOAT2 m_pos;				// �摜�̍��W(HP�o�[�̂悤�ɏ�ɉ�ʂɒ���t���悤�ɕ`�悷��̂�Z���͂Ȃ�)
	DirectX::XMFLOAT2 m_size;				// �摜�̃T�C�Y(Y���̒l��-�ɂ���Ɣ��])
	float m_rot;				// ��]
	SortOrder m_sort;			// �`�揇�֘A
	DirectX::XMFLOAT2 m_uvPos;	// �����UV���W
	DirectX::XMFLOAT2 m_uvScale;// �`�悷��UV�̑傫��
	DirectX::XMFLOAT4 m_color;


	const char* m_fileName;
};
#endif // ! __GAME_UI_H__

