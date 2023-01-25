#pragma once
#include <GameUI.h>
#include <vector>
class CNumberUI
{
public:
	using Ptr = std::unique_ptr<CNumberUI>;

	static void Init();
	static void Uninit();
private:
	static ID3D11ShaderResourceView* m_numberImg;
	static int m_instanceNum;	// �C���X�^���X�̐��i�ׁ̂j

public:
	enum ENumAlign
	{
		ALIGN_LEFT,		// ������
		ALIGN_CENTER,	// �������낦
		ALIGN_RIGHT,	// �E����
	};
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="length">�������̌���</param>
	/// <param name="sort">�\�[�g�I�[�_�[</param>
	/// <param name="isFloat">�����_�ȉ���`�悷�邩</param>
	/// <param name="floatLength">�����_�ȉ��̌���</param>
	CNumberUI(int length = 3, SortOrder sort = SORT_ORDER_UI_DEFAULT, int floatLength = 0);
	~CNumberUI();

	/// <summary>
	/// �������ēx�w�肵�Ȃ����܂�
	/// </summary>
	/// <param name="length">�������̌���</param>
	/// <param name="sort">�\�[�g�I�[�_�[</param>
	/// <param name="isFloat">�����_�ȉ���`�悷�邩</param>
	/// <param name="floatLength">�����_�ȉ��̌���</param>
	void ResetLength(int length = 3, SortOrder sort = SORT_ORDER_UI_DEFAULT, int floatLength = 0);
	void SetPos(float x, float y);
	void SetPos(DirectX::XMFLOAT2 pos);
	void SetSize(float x, float y);
	void SetSize(DirectX::XMFLOAT2 size);
	void SetRot(float degZ);	// �x���@
	void SetIsZeroFill(bool isFill);	// �[�����߂��邩
	void SetNum(float num);
	void SetAlign(ENumAlign align);
	void SetSortOrder(SortOrder sort);
	void SetMarginLevel(float level);
	void SetColor(float r, float g, float b, float a = 1);
	void SetColor255(int r, int g, int b, int a = 255);
private:
	float m_num;	// �\������l
	DirectX::XMFLOAT2 m_pos;	// ���S���W
	DirectX::XMFLOAT2 m_size;	// �u�ꕶ���́v�c����
	float m_rot;				// �u�S�̂́v��]
	ENumAlign m_align;
	SortOrder m_sort;
	float m_margin;
	int m_len;		// �S�̂̒����i�����_�܂܂�
	int m_floatLen;	// �����_�ȉ��̒����i�����_�܂܂�
	bool m_isZeroFill;	// �[�����߂��邩
	std::vector<CGameUI::Ref> m_ui;	// �����|��
	CGameUI::Ref m_zeroPoint;	// �����_

	void RePosition();
};