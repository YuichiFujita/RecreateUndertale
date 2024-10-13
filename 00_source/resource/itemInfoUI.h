//============================================================
//
//	��񃁃j���[�w�b�_�[ [itemInfoUI.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _ITEM_INFO_UI_H_
#define _ITEM_INFO_UI_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "selectItemUI.h"

//************************************************************
//	�N���X��`
//************************************************************
// ��񃁃j���[�N���X
class CItemInfoUI : public CItemUI
{
public:
	// �R���X�g���N�^
	explicit CItemInfoUI(const int nChoiceItemIdx);

	// �f�X�g���N�^
	~CItemInfoUI() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader *pShader = nullptr) override;	// �`��

private:
	// �I�[�o�[���C�h�֐�
	void NextText(void) override;	// �e�L�X�g�{�b�N�X�i�s
};

#endif	// _ITEM_INFO_UI_H_
