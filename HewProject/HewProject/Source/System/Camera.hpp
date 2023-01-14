#pragma once
#include <DirectXMath.h>
#include <memory>
#include <map>
#include <Windows.h>

class CCameraBase
{
	//
	// �����������
	// �X�^�e�B�b�N�̈�ɃJ�����̃��X�g���쐬
	// �C���X�^���X�����Ɏ��g��o�^
	// �f�X�g���N�^�ŉ��
	// �X�^�e�B�b�N�֐��Ŗ��O���w��i�^�O�H�j��
	// �g�p����J���������擾�B
	//
public:
	struct Data
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 look;
	};
	//--- static ---//
public:
	// �J�������쐬
	template<class T> static  void CreateCamera(T* cameraPtr, const char* cameraName);
	// �J�������폜
	static void DeleteCamera(const char* cameraName);
	// �S�J�������폜
	static void DeleteCameraAll();
	// ���C���J�������Z�b�g
	static void SetPrimaryCamera(const char* cameraName);
	// ���C���J�����̃r���[�s��擾
	static DirectX::XMFLOAT4X4 GetPrimaryViewMatrix();
	// ���C���J�����̃v���W�F�N�V�����s��擾
	static DirectX::XMFLOAT4X4 GetPrimaryProjectionMatrix();
	// �w�肵���J�����̃r���[�s��擾
	static DirectX::XMFLOAT4X4 GetViewMatrixFromTag(const char* cameraName);
	// �w�肵���J�����̃v���W�F�N�V�����s��擾
	static DirectX::XMFLOAT4X4 GetProjectionMatrixFromTag(const char* cameraName);
	// ���C���J�����̏����擾
	static Data GetPrimaryData();
	// �w�肵���J�����̏����擾
	static Data GetDataFromTag(const char* cameraName);
	// ���C���J�������X�V
	static void UpdatePrimary();
	// �w�肵���J�������X�V
	static void UpdateFromTag(const char* cameraName);
	// ���C���J�����̖��O���擾
	static const char* GetPrimaryName();
	// ���C���J�����̑O�����P�ʃx�N�g��
	static DirectX::XMVECTOR GetPrimaryFront();
	// ���C���J�����̉E�����P�ʃx�N�g��
	static DirectX::XMVECTOR GetPrimaryRight();
	// ���C���J�����̏�����P�ʃx�N�g��
	static DirectX::XMVECTOR GetPrimaryUp();
	// ���C���J�����̑O�����P�ʃx�N�g���i�����j
	static DirectX::XMVECTOR GetPrimaryFrontHorizontal();
	static DirectX::XMVECTOR GetFrontHorizontal(const char* cameraName);
	// ���C���J�����̉E�����P�ʃx�N�g���i�����j
	static DirectX::XMVECTOR GetPrimaryRightHorizontal();
	// ���C���J�����̏�����P�ʃx�N�g���i�����j
	static DirectX::XMVECTOR GetPrimaryUpHorizontal();
	// ���C���J������RadXZ���擾
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
	// �d����`����Ȃ��悤��
	if (m_cameraMap.count(cameraName) != 0)
	{
		MessageBox(NULL, cameraName, "[CreateCamera]�d���J�����^�O", MB_ICONEXCLAMATION);
		return;
	}
	m_cameraMap[cameraName].reset(cameraPtr);
	m_cameraMap[cameraName]->m_tagName = cameraName;

}
