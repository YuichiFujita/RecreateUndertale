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
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Use(void) const override;	// �A�C�e���g�p
	void Info(void) const override;	// �A�C�e�����
	void Drop(void) const override;	// �A�C�e���j��
	std::string Detail(void) const override;	// �A�C�e�����O

private:
	// �����o�ϐ�

};

#endif	// _ITEM_NONE_H_