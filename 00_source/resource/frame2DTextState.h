//============================================================
//
//	�e�L�X�g�@�\��ԃw�b�_�[ [frame2DTextState.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _FRAME2D_TEXT_STATE_H_
#define _FRAME2D_TEXT_STATE_H_

//************************************************************
//	�O���錾
//************************************************************
class CFrame2DModuleText;		// �e�L�X�g�\���@�\�N���X
class CFrame2DTextStateText;	// �e�L�X�g��ԃN���X
class CFrame2DTextStateSelect;	// �I��t���e�L�X�g��ԃN���X

//************************************************************
//	�N���X��`
//************************************************************
// �e�L�X�g�@�\��ԃN���X
class CFrame2DTextState
{
public:
	// �R���X�g���N�^
	CFrame2DTextState();

	// �f�X�g���N�^
	virtual ~CFrame2DTextState();

	// �������z�֐�
	virtual HRESULT Init()	= 0;	// ������
	virtual void Uninit()	= 0;	// �I��
	virtual void Update(const float fDeltaTime) = 0;	// �X�V

	// ���z�֐�
	inline virtual CFrame2DTextStateText* GetStateText()	 { return nullptr; }	// �e�L�X�g��Ԏ擾
	inline virtual CFrame2DTextStateSelect* GetStateSelect() { return nullptr; }	// �I��t���e�L�X�g��Ԏ擾

	// �����o�֐�
	inline void SetContext(CFrame2DModuleText* pContext) { m_pContext = pContext; }	// �R���e�L�X�g�ݒ�

protected:
	// �����o�ϐ�
	CFrame2DModuleText* m_pContext;	// �R���e�L�X�g
};

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "frame2DTextStateText.h"

#endif	// _FRAME2D_TEXT_STATE_H_
