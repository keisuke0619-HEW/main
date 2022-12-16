#ifndef  __GAME_UI_H__
#define  __GAME_UI_H__

#include "DirectX.h"
#include "Sprite.h"
#include "DirectXTex/Texture.h"
#include <memory>

enum SortOrder
{
	SORT_ORDER_TOP,
	SORT_ORDER_DEFAULT,
	SORT_ORDER_BOTTOM,
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
	/// 回転を設定します。（度数法）
	/// </summary>
	/// <param name="rot">回転角度（度数法）</param>
	void SetRotation(float degRot);
	int GetSortID();

	void SetSortID(SortOrder order);
private:
	ID3D11ShaderResourceView* m_pPicture;	// 画像
	DirectX::XMFLOAT2 m_pos;				// 画像の座標(HPバーのように常に画面に張り付くように描画するのでZ軸はなし)
	DirectX::XMFLOAT2 m_size;				// 画像のサイズ(Y軸の値を-にすると反転)
	float m_rot;
	SortOrder m_sort;
};
#endif // ! __GAME_UI_H__

