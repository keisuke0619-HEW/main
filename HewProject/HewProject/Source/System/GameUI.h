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

private:
	ID3D11ShaderResourceView* m_pPicture;	// 画像
	DirectX::XMFLOAT2 m_pos;				// 画像の座標(HPバーのように常に画面に張り付くように描画するのでZ軸はなし)
	DirectX::XMFLOAT2 m_size;				// 画像のサイズ(Y軸の値を-にすると反転)
};
#endif // ! __GAME_UI_H__

