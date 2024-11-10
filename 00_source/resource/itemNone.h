//============================================================
//
//	������ʂȂ��A�C�e���w�b�_�[ [itemNone.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _ITEM_NONE_H_
#define _ITEM_NONE_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "item.h"

//************************************************************
//	�N���X��`
//************************************************************
// ������ʂȂ��A�C�e�����N���X
class CItemNone : public CItemData
{
public:
	// �R���X�g���N�^
	CItemNone();

	// �f�X�g���N�^
	~CItemNone() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Use() const override;	// �A�C�e���g�p
	void Info() const override;	// �A�C�e�����
	void Drop() const override;	// �A�C�e���j��
	std::string Detail() const override;	// �A�C�e���ڍׂ̕�����擾

private:
	// �I�[�o�[���C�h�֐�
	HRESULT LoadSetup(std::ifstream* pFile, std::string& rString) override;	// ��ނ��Ƃ̃Z�b�g�A�b�v

	// �����o�ϐ�

};

#endif	// _ITEM_NONE_H_
