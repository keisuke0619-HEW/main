#pragma once

#include <memory>
/// <summary>
/// ���f���f�[�^��摜�f�[�^��ۑ����Ă����N���X�B�V���O���g���B
/// </summary>
class CDataPool
{
	// �V���O���g���@�\
public:
	static std::weak_ptr<CDataPool> GetIns();
private:

};