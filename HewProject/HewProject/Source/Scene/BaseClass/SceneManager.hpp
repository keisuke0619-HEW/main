#pragma once
#include <ISceneBase.hpp>
#include <DirectXTex/Texture.h>
#include <memory>
#include <vector>



struct TScenePassingData
{
	void* dataPtr;
	long size;
	const char* name;
};

enum ESwapState
{
	SWAP_NONE,	// シーン遷移なし
	SWAP_WAIT,	// シーン遷移まち（黒フェードイン中）
	SWAP_OK,	// シーン遷移準備OK（真っ黒状態）
	SWAP_END	// シーン遷移終了待ち（黒フェードアウト中）
};
class CSceneManager
{
public:
	static ESwapState getState();
	static void SetScene(ESceneID id);
	static void Init();
	static void Update();
	static void Draw();
	static void Uninit();
	static void SwapScene();
	static void SetData(void* dataPtr, long size = 0, const char* name = "NO_NAME");
private:
	static std::unique_ptr<IScene> m_scene;
	static ESwapState m_isSwap;
	static ESceneID m_next;
	static std::vector<TScenePassingData> m_passingData;
	static ID3D11ShaderResourceView* m_fade;
	static float m_alpha;
};