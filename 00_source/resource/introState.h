//============================================================
//
//	�C���g����ԃw�b�_�[ [introState.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _INTRO_STATE_H_
#define _INTRO_STATE_H_

//************************************************************
//	�O���錾
//************************************************************
class CIntroManager;	// �C���g���}�l�[�W���[�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �C���g����ԃN���X
class CIntroState
{
public:
	// �R���X�g���N�^
	CIntroState();

	// �f�X�g���N�^
	virtual ~CIntroState();

	// �������z�֐�
	virtual HRESULT Init(void)	= 0;	// ������
	virtual void Uninit(void)	= 0;	// �I��
	virtual void Update(const float fDeltaTime) = 0;	// �X�V

	// �����o�֐�
	void SetContext(CIntroManager *pContext) { m_pContext = pContext; }	// �R���e�L�X�g�ݒ�

protected:
	// �����o�ϐ�
	CIntroManager *m_pContext;	// �R���e�L�X�g
};

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "introStateLogo.h"
#include "introStateText.h"
#include "introStateWait.h"
#include "introStateScroll.h"
#include "introStateEnd.h"

#endif	// _INTRO_STATE_H_
