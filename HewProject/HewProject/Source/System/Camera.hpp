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
	template<class T> static  void CreateCamera(T* cameraPtr, const char* cameraName);
	static void DeleteCamera(const char* cameraName);
	static void SetPrimaryCamera(const char* cameraName);
	static DirectX::XMFLOAT4X4 GetPrimaryViewMatrix();
	static DirectX::XMFLOAT4X4 GetPrimaryProjectionMatrix();
	static DirectX::XMFLOAT4X4 GetViewMatrixFromTag(const char* cameraName);
	static DirectX::XMFLOAT4X4 GetProjectionMatrixFromTag(const char* cameraName);
	static Data GetPrimaryData();
	static Data GetDataFromTag(const char* cameraName);
	static void UpdatePrimary();
	static const char* GetPrimaryName();
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
