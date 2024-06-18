//============================================================
//
//	�X�^�[�g��ԃw�b�_�[ [startState.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _START_STATE_H_
#define _START_STATE_H_

//************************************************************
//	�O���錾
//************************************************************
class CStartManager;	// �X�^�[�g�}�l�[�W���[�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �X�^�[�g��ԃN���X
class CStartState
{
public:
	// �R���X�g���N�^
	CStartState();

	// �f�X�g���N�^
	virtual ~CStartState();

	// �������z�֐�
	virtual HRESULT Init(void)	= 0;	// ������
	virtual void Uninit(void)	= 0;	// �I��
	virtual void Update(const float fDeltaTime) = 0;	// �X�V

	// �����o�֐�
	void SetContext(CStartManager *pContext) { m_pContext = pContext; }	// �R���e�L�X�g�ݒ�

protected:
	// �����o�ϐ�
	CStartManager *m_pContext;	// �R���e�L�X�g
};

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "startStateLogo.h"
#include "startStateTutorial.h"
#include "startStateOption.h"
#include "startStateCreateName.h"
#include "startStateDecideName.h"

#endif	// _START_STATE_H_
