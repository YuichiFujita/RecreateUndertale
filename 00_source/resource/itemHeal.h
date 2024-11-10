//============================================================
//
//	�񕜃A�C�e���w�b�_�[ [itemHeal.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _ITEM_HEAL_H_
#define _ITEM_HEAL_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "item.h"

//************************************************************
//	�N���X��`
//************************************************************
// �񕜃A�C�e�����N���X
class CItemHeal : public CItemData
{
public:
	// �R���X�g���N�^
	CItemHeal();

	// �f�X�g���N�^
	~CItemHeal() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Use() const override;	// �A�C�e���g�p
	void Info() const override;	// �A�C�e�����
	void Drop() const override;	// �A�C�e���j��
	std::string Detail() const override;	// �A�C�e���ڍׂ̕�����擾
	std::string UseEnd() const override;	// �A�C�e���g�p��̕�����擾

private:
	// �I�[�o�[���C�h�֐�
	HRESULT LoadSetup(std::ifstream* pFile, std::string& rString) override;	// ��ނ��Ƃ̃Z�b�g�A�b�v

	// �����o�ϐ�
	int m_nHeal;	// �񕜗�
	bool m_bUseEnd;	// �g�p��̕����\���t���O
};

#endif	// _ITEM_HEAL_H_
