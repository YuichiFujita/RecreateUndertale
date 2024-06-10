//============================================================
//
//	������ԃw�b�_�[ [charState.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _CHAR_STATE_H_
#define _CHAR_STATE_H_

//************************************************************
//	�O���錾
//************************************************************
class CStartStateCreateName;	// ������ԃN���X

//************************************************************
//	�N���X��`
//************************************************************
// ������ԃN���X
class CCharState
{
public:
	// �R���X�g���N�^
	CCharState();

	// �f�X�g���N�^
	virtual ~CCharState();

	// �������z�֐�
	virtual HRESULT Init(void)	= 0;	// ������
	virtual void Uninit(void)	= 0;	// �I��
	virtual void Update(const float fDeltaTime) = 0;	// �X�V

	// ���z�֐�
	virtual void SetContext(CStartStateCreateName *pContext) { m_pContext = pContext; }	// �R���e�L�X�g�ݒ�

protected:
	// �����o�ϐ�
	CStartStateCreateName *m_pContext;	// �R���e�L�X�g
};

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "charStateHiragana.h"

#endif	// _CHAR_STATE_H_
