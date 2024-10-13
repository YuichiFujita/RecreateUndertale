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
	explicit CItemUseUI(const int nChoiceItemIdx);

	// �f�X�g���N�^
	~CItemUseUI() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader *pShader = nullptr) override;	// �`��

private:
	// �I�[�o�[���C�h�֐�
	void NextText(void) override;	// �e�L�X�g�{�b�N�X�i�s
};

#endif	// _ITEM_USE_UI_H_
