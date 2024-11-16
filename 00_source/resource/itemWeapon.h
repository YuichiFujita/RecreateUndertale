//============================================================
//
//	����A�C�e���w�b�_�[ [itemWeapon.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _ITEM_WEAPON_H_
#define _ITEM_WEAPON_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "item.h"

//************************************************************
//	�N���X��`
//************************************************************
// ����A�C�e�����N���X
class CItemWeapon : public CItemData
{
public:
	// �R���X�g���N�^
	CItemWeapon();

	// �f�X�g���N�^
	~CItemWeapon() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Use(const int nBagIdx) const override;	// �A�C�e���g�p
	std::string Detail() const override;		// �A�C�e���ڍׂ̕�����擾

private:
	// �I�[�o�[���C�h�֐�
	HRESULT LoadSetup(std::ifstream* pFile, std::string& rString) override;	// ��ނ��Ƃ̃Z�b�g�A�b�v
};

#endif	// _ITEM_WEAPON_H_
