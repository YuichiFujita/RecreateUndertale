//============================================================
//
//	�j�����j���[�w�b�_�[ [itemDropUI.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _ITEM_DROP_UI_H_
#define _ITEM_DROP_UI_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "selectItemUI.h"

//************************************************************
//	�N���X��`
//************************************************************
// �j�����j���[�N���X
class CItemDropUI : public CItemUI
{
public:
	// �R���X�g���N�^
	explicit CItemDropUI(const int nChoiceItemIdx, const int nChoiceBagIdx);

	// �f�X�g���N�^
	~CItemDropUI() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader* pShader = nullptr) override;	// �`��

private:
	// �I�[�o�[���C�h�֐�
	void NextText() override;	// �e�L�X�g�{�b�N�X�i�s
};

#endif	// _ITEM_DROP_UI_H_
