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

	// 概要 : 2D描画
	// 戻値 : なし
	// 引数 : DirectX::XMFLOAT4X4 view	: カメラのビュー行列
	//		  DirectX::XMFLOAT4X4 proj	: カメラのプロジェクション行列
	//		  DirectX::XMFLOAT3 pos		: 表示する画像の座標
	//		  DirectX::XMFLOAT2 size	: 表示する画像のサイズ
	//		  bool BillOnOff			: ビルボードのオンオフ
	//		  bool enable				: 深度バッファのなんとか(flaseにすると表示された画像が手前に描画される)
	//		  float rot					: 表示する画像の角度(度数法)(ビルボードがオンの時は必要ない)
	void Draw(DirectX::XMFLOAT4X4 view, DirectX::XMFLOAT4X4 proj, DirectX::XMFLOAT3 pos, DirectX::XMFLOAT2 size, bool BillOnOff, bool enable, float rot = 0.f);

private:
	ID3D11ShaderResourceView* m_pPicture;
};


#endif // !__BILLBOARD_H__
