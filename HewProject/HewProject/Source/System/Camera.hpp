#pragma once
#include <DirectXMath.h>
#include <memory>
#include <map>
#include <Windows.h>

class CCameraBase
{
	//
	// 今後実装メモ
	// スタティック領域にカメラのリストを作成
	// インスタンス化時に自身を登録
	// デストラクタで解放
	// スタティック関数で名前を指定（タグ？）で
	// 使用するカメラ情報を取得。
	//
public:
	struct Data
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 look;
	};
	//--- static ---//
public:
	// カメラを作成
	template<class T> static  void CreateCamera(T* cameraPtr, const char* cameraName);
	// カメラを削除
	static void DeleteCamera(const char* cameraName);
	// 全カメラを削除
	static void DeleteCameraAll();
	// メインカメラをセット
	static void SetPrimaryCamera(const char* cameraName);
	// メインカメラのビュー行列取得
	static DirectX::XMFLOAT4X4 GetPrimaryViewMatrix();
	// メインカメラのプロジェクション行列取得
	static DirectX::XMFLOAT4X4 GetPrimaryProjectionMatrix();
	// 指定したカメラのビュー行列取得
	static DirectX::XMFLOAT4X4 GetViewMatrixFromTag(const char* cameraName);
	// 指定したカメラのプロジェクション行列取得
	static DirectX::XMFLOAT4X4 GetProjectionMatrixFromTag(const char* cameraName);
	// メインカメラの情報を取得
	static Data GetPrimaryData();
	// 指定したカメラの情報を取得
	static Data GetDataFromTag(const char* cameraName);
	// メインカメラを更新
	static void UpdatePrimary();
	// 指定したカメラを更新
	static void UpdateFromTag(const char* cameraName);
	// メインカメラの名前を取得
	static const char* GetPrimaryName();
	// メインカメラの前向き単位ベクトル
	static DirectX::XMVECTOR GetPrimaryFront();
	// メインカメラの右向き単位ベクトル
	static DirectX::XMVECTOR GetPrimaryRight();
	// メインカメラの上向き単位ベクトル
	static DirectX::XMVECTOR GetPrimaryUp();
	// メインカメラの前向き単位ベクトル（水平）
	static DirectX::XMVECTOR GetPrimaryFrontHorizontal();
	static DirectX::XMVECTOR GetFrontHorizontal(const char* cameraName);
	// メインカメラの右向き単位ベクトル（水平）
	static DirectX::XMVECTOR GetPrimaryRightHorizontal();
	// メインカメラの上向き単位ベクトル（水平）
	static DirectX::XMVECTOR GetPrimaryUpHorizontal();
	// メインカメラのRadXZを取得
	static float GetPrimaryRadXZ();


private:
	using Ptr = std::unique_ptr<CCameraBase>;
	static std::map<const char*,Ptr> m_cameraMap;
	static const char* m_primaryCameraName;
	//--- dynamic ---//
protected:
	CCameraBase();
public:
	virtual ~CCameraBase();
	
	virtual void Update() = 0;
	DirectX::XMFLOAT4X4 GetViewMatrix();
	DirectX::XMFLOAT4X4 GetProjectionMatrix();
	DirectX::XMFLOAT3 GetPos();
	DirectX::XMFLOAT3 GetLook();

protected:
	Data m_data;
	float m_distance;
	float m_radXZ;
	float m_radY;
	DirectX::XMFLOAT3 m_up;
	float m_fovY;
	float m_aspect;
	float m_near;
	float m_far;
	const char* m_tagName;
};

template<class T>
inline void CCameraBase::CreateCamera(T *cameraPtr, const char* cameraName)
{
	// 重複定義されないように
	if (m_cameraMap.count(cameraName) != 0)
	{
		MessageBox(NULL, cameraName, "[CreateCamera]重複カメラタグ", MB_ICONEXCLAMATION);
		return;
	}
	m_cameraMap[cameraName].reset(cameraPtr);
	m_cameraMap[cameraName]->m_tagName = cameraName;

}
