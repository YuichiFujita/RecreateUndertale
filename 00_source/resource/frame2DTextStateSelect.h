//============================================================
//
//	�I��t���e�L�X�g��ԃw�b�_�[ [frame2DTextStateSelect.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _FRAME2D_TEXT_STATE_SELECT_H_
#define _FRAME2D_TEXT_STATE_SELECT_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "frame2DTextStateText.h"

//************************************************************
//	�N���X��`
//************************************************************
// �I��t���e�L�X�g��ԃN���X
class CFrame2DTextStateSelect : public CFrame2DTextStateText
{
public:
	// �R���X�g���N�^
	CFrame2DTextStateSelect();

	// �f�X�g���N�^
	~CFrame2DTextStateSelect() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	inline CFrame2DTextStateSelect* GetStateSelect() override { return this; }	// �I��t���e�L�X�g��Ԏ擾

private:
	// �����o�ϐ�

};

#endif	// _FRAME2D_TEXT_STATE_SELECT_H_
