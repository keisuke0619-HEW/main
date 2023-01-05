#ifndef __BILLBOARD_H__
#define __BILLBOARD_H__

#include "DirectX.h"
#include "Sprite.h"
#include "DirectXTex/Texture.h"
#include <list>
#include <map>
#include <memory>
class CBillboard
{
public:
	using Ptr =  std::unique_ptr<CBillboard>;
	static void DrawAll();
	static void ClearBillboard();
private:
	static std::list<CBillboard*> m_billList;
	static std::map<const char*, ID3D11ShaderResourceView*> m_billImg;







public:
	CBillboard(const char*);
	~CBillboard();

	// �T�v : 2D�`��
	// �ߒl : �Ȃ�
	// ���� : bool BillOnOff				: �r���{�[�h�̃I���I�t
	//		  false�ɂ��Ċp�x��ݒ肵�����ꍇ��SetRotation���Ă�
	//		  bool enable					: �[�x�o�b�t�@�̂Ȃ�Ƃ�(flase�ɂ���ƕ\�����ꂽ�摜����O�ɕ`�悳���)
	//		  false�ɂ���Ƃ���SetPlayerrPos���Ă�
	void Draw(bool BillOnOff = true, bool enable = true);

	// �T�v : �J�����̃r���[�ƃv���W�F�N�V�����s���ݒ�
	//		: Draw�̒��O�ŌĂ�ł�������
	// �ߒl : �Ȃ�
	// ���� : DirectX::XMFLOAT4X4 view		: �J�����̃r���[�s��
	//		  DirectX::XMFLOAT4X4 proj		: �J�����̃v���W�F�N�V�����s��
	void SetPosViewProj(DirectX::XMFLOAT4X4 view, DirectX::XMFLOAT4X4 proj);

	// �T�v : �\������摜�̍��W��ݒ�
	// �ߒl : �Ȃ�
	// ���� :�@DirectX::XMFLOAT3 pos		: �\������摜�̍��W
	void SetPos(DirectX::XMFLOAT3 pos);

	// �T�v : �v���C���[�̍��W�Ǝ�O�ɕ`�悳��鋗����ݒ�
	//		: Draw��enable��false�̂���Ƃ��͂��̑O�ɌĂ�ł�������
	// �ߒl : �Ȃ�
	// ���� : DirectX::XMFLOAT3 Playerpos	: �v���C���[��pos(�摜�Ƃ̋����Ɏg��)
	//		  float distance				: �摜����O�ɕ`�悳���悤�ɂȂ鋗�� 
	void SetPlayerrPos(DirectX::XMFLOAT3 playerPos, float distance = 4.f);

	// �T�v : �摜�̃T�C�Y�̐ݒ�
	// �ߒl : �Ȃ�
	// ���� : DirectX::XMFLOAT2 size		: �\������摜�̃T�C�Y
	void SetSize(DirectX::XMFLOAT2 size);

	// �T�v : �摜�̊p�x�̐ݒ�
	//		: �ݒ肷��p�x�͓x���@�ł�
	//		: Draw��BillOnOff��false�ɂ��Ċp�x��ݒ肵�����Ƃ��ɂ��̑O�ɌĂ�ł�������
	// �ߒl : �Ȃ�
	// ���� : float rot						: �\������摜�̊p�x
	void SetRotation(float rot);


private:
	ID3D11ShaderResourceView* m_pPicture;	// �摜
	DirectX::XMFLOAT4X4 m_view;				// �r���[�s��
	DirectX::XMFLOAT4X4 m_proj;				// �v���W�F�N�V�����s��
	DirectX::XMFLOAT3 m_pos;				// �摜�̍��W
	DirectX::XMFLOAT3 m_playerPos;			// �v���C���[�̍��W(�����𑪂�Ƃ��Ɏg��)
	DirectX::XMFLOAT2 m_size;				// �摜�̃T�C�Y
	float m_distance;						// �摜����O�ɕ`�悳��鋗��
	float m_rot;							// �摜�̊p�x
	bool m_isUseUniqueViewProj;				// "����O"�̃r���[�v���W�F�N�V�����}�g���b�N�X���g����
};


#endif // !__BILLBOARD_H__
