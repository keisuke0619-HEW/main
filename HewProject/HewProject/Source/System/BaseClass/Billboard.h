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
	// 引数 : bool BillOnOff				: ビルボードのオンオフ
	//		  bool enable					: 深度バッファのなんとか(flaseにすると表示された画像が手前に描画される)
	void Draw(bool BillOnOff, bool enable);

	// 概要 : カメラのビューとプロジェクション行列を設定
	//		: Drawの直前で呼んでください
	// 戻値 : なし
	// 引数 : DirectX::XMFLOAT4X4 view		: カメラのビュー行列
	//		  DirectX::XMFLOAT4X4 proj		: カメラのプロジェクション行列
	void SetPosViewProj(DirectX::XMFLOAT4X4 view, DirectX::XMFLOAT4X4 proj);

	// 概要 : 表示する画像の座標を設定
	// 戻値 : なし
	// 引数 :　DirectX::XMFLOAT3 pos		: 表示する画像の座標
	void SetPos(DirectX::XMFLOAT3 pos);

	// 概要 : プレイヤーの座標と手前に描画される距離を設定
	//		: Drawのenableをfalseのするときはその前に呼んでください
	// 戻値 : なし
	// 引数 : DirectX::XMFLOAT3 Playerpos	: プレイヤーのpos(画像との距離に使う)
	//		  float distance				: 画像が手前に描画されるようになる距離 
	void SetPlayerrPos(DirectX::XMFLOAT3 playerPos, float distance);

	// 概要 : 画像のサイズの設定
	// 戻値 : なし
	// 引数 : DirectX::XMFLOAT2 size		: 表示する画像のサイズ
	void SetSize(DirectX::XMFLOAT2 size);

	// 概要 : 画像の角度の設定
	//		: 設定する角度は度数法です
	//		: DrawのBillOnOffをfalseにして角度を設定したいときにその前に呼んでください
	// 戻値 : なし
	// 引数 : float rot						: 表示する画像の角度
	void SetRotation(float rot);


private:
	ID3D11ShaderResourceView* m_pPicture;	// 画像
	DirectX::XMFLOAT4X4 m_view;				// ビュー行列
	DirectX::XMFLOAT4X4 m_proj;				// プロジェクション行列
	DirectX::XMFLOAT3 m_pos;				// 画像の座標
	DirectX::XMFLOAT3 m_playerPos;			// プレイヤーの座標(距離を測るときに使う)
	DirectX::XMFLOAT2 m_size;				// 画像のサイズ
	float m_distance;						// 画像が手前に描画される距離
	float m_rot;							// 画像の角度
};


#endif // !__BILLBOARD_H__
