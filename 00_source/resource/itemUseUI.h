//============================================================
//
//	�g�p���j���[�w�b�_�[ [itemUseUI.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _ITEM_USE_UI_H_
#define _ITEM_USE_UI_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "selectItemUI.h"

//************************************************************
//	�N���X��`
//************************************************************
// �g�p���j���[�N���X
class CItemUseUI : public CItemUI
{
public:
	// �R���X�g���N�^
	CItemUseUI(const int nChoiceItemIdx, const int nChoiceBagIdx);

	// �f�X�g���N�^
	~CItemUseUI() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader* pShader = nullptr) override;	// �`��
};

#endif	// _ITEM_USE_UI_H_
