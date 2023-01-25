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
	static int m_instanceNum;	// インスタンスの数（のべ）

public:
	enum ENumAlign
	{
		ALIGN_LEFT,		// 左揃え
		ALIGN_CENTER,	// 中央ぞろえ
		ALIGN_RIGHT,	// 右揃え
	};
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="length">整数部の桁数</param>
	/// <param name="sort">ソートオーダー</param>
	/// <param name="isFloat">小数点以下を描画するか</param>
	/// <param name="floatLength">小数点以下の桁数</param>
	CNumberUI(int length = 3, SortOrder sort = SORT_ORDER_UI_DEFAULT, int floatLength = 0);
	~CNumberUI();

	/// <summary>
	/// 長さを再度指定しなおします
	/// </summary>
	/// <param name="length">整数部の桁数</param>
	/// <param name="sort">ソートオーダー</param>
	/// <param name="isFloat">小数点以下を描画するか</param>
	/// <param name="floatLength">小数点以下の桁数</param>
	void ResetLength(int length = 3, SortOrder sort = SORT_ORDER_UI_DEFAULT, int floatLength = 0);
	void SetPos(float x, float y);
	void SetPos(DirectX::XMFLOAT2 pos);
	void SetSize(float x, float y);
	void SetSize(DirectX::XMFLOAT2 size);
	void SetRot(float degZ);	// 度数法
	void SetIsZeroFill(bool isFill);	// ゼロ埋めするか
	void SetNum(float num);
	void SetAlign(ENumAlign align);
	void SetSortOrder(SortOrder sort);
	void SetMarginLevel(float level);
	void SetColor(float r, float g, float b, float a = 1);
	void SetColor255(int r, int g, int b, int a = 255);
private:
	float m_num;	// 表示する値
	DirectX::XMFLOAT2 m_pos;	// 中心座標
	DirectX::XMFLOAT2 m_size;	// 「一文字の」縦横幅
	float m_rot;				// 「全体の」回転
	ENumAlign m_align;
	SortOrder m_sort;
	float m_margin;
	int m_len;		// 全体の長さ（小数点含まず
	int m_floatLen;	// 小数点以下の長さ（小数点含まず
	bool m_isZeroFill;	// ゼロ埋めするか
	std::vector<CGameUI::Ref> m_ui;	// いたポリ
	CGameUI::Ref m_zeroPoint;	// 小数点

	void RePosition();
};