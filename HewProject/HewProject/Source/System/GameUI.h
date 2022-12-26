#ifndef  __GAME_UI_H__
#define  __GAME_UI_H__

#include "DirectX.h"
#include "Sprite.h"
#include "DirectXTex/Texture.h"
#include <memory>

enum SortOrder
{
	SORT_ORDER_BACK,
	SORT_ORDER_DEFAULT,
	SORT_ORDER_FRONT,
	SORT_ORDER_UI_BACKEND,
	SORT_ORDER_UI_BACK,
	SORT_ORDER_UI_DEFAULT,
	SORT_ORDER_UI_FRONT,
	SORT_ORDER_UI_FRONTEND,
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

	// 概要 : 画像の座標を設定
	//		: 画面左端の座標 : 0.f
	//		: 画面右端の座標 : 1280.f
	//		: 画面下端の座標 : 720.f	
	//		: 画面上端の座標 : 0.f
	// 戻値 : なし
	// 引数 : DirectX::XMFLOAT2 pos : 画像の座標(画面の座標を参考にして設定してください) 
	void SetPos(DirectX::XMFLOAT2 pos);

	// 概要 : 画像のサイズを設定
	// 戻値 : なし
	// 引数 : DirectX::XMFLOAT2 size : 画像のサイズ(値を-にすると反転します)
	void SetSize(DirectX::XMFLOAT2 size);

	/// <summary>
	/// UVを設定
	/// </summary>
	/// <param name="uv">左上のUV座標</param>
	void SetUVPos(DirectX::XMFLOAT2 uv);

	/// <summary>
	/// UVの大きさを設定
	/// </summary>
	/// <param name="uv">UVの大きさ</param>
	void SetUVScale(DirectX::XMFLOAT2 uv);

	/// <summary>
	/// 回転を設定します。（度数法）
	/// </summary>
	/// <param name="rot">回転角度（度数法）</param>
	void SetRotation(float degRot);
	
	void SetColor(float r, float g, float b, float a = 1.0f);
	void SetColor255(int r, int g, int b, int a = 255);
	DirectX::XMFLOAT2 GetSize();

	int GetSortID();

	void SetSortID(SortOrder order);
private:
	ID3D11ShaderResourceView* m_pPicture;	// 画像
	DirectX::XMFLOAT2 m_pos;				// 画像の座標(HPバーのように常に画面に張り付くように描画するのでZ軸はなし)
	DirectX::XMFLOAT2 m_size;				// 画像のサイズ(Y軸の値を-にすると反転)
	float m_rot;				// 回転
	SortOrder m_sort;			// 描画順関連
	DirectX::XMFLOAT2 m_uvPos;	// 左上のUV座標
	DirectX::XMFLOAT2 m_uvScale;// 描画するUVの大きさ
	DirectX::XMFLOAT4 m_color;
};
#endif // ! __GAME_UI_H__

