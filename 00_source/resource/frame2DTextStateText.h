//============================================================
//
//	�e�L�X�g��ԃw�b�_�[ [frame2DTextStateText.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _FRAME2D_TEXT_STATE_TEXT_H_
#define _FRAME2D_TEXT_STATE_TEXT_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "frame2DTextState.h"

//************************************************************
//	�N���X��`
//************************************************************
// �e�L�X�g��ԃN���X
class CFrame2DTextStateText : public CFrame2DTextState
{
public:
	// �R���X�g���N�^
	CFrame2DTextStateText();

	// �f�X�g���N�^
	~CFrame2DTextStateText() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	inline CFrame2DTextStateText* GetStateText() override { return this; }	// �e�L�X�g��Ԏ擾

private:
	// �����o�ϐ�

};

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "frame2DTextStateSelect.h"

#endif	// _FRAME2D_TEXT_STATE_TEXT_H_
