//============================================================
//
//	�^�C�g����ԃw�b�_�[ [titleState.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _TITLE_STATE_H_
#define _TITLE_STATE_H_

//************************************************************
//	�O���錾
//************************************************************
class CTitleManager;	// �^�C�g���}�l�[�W���[�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �^�C�g����ԃN���X
class CTitleState
{
public:
	// �R���X�g���N�^
	CTitleState();

	// �f�X�g���N�^
	virtual ~CTitleState();

	// �������z�֐�
	virtual HRESULT Init()	= 0;	// ������
	virtual void Uninit()	= 0;	// �I��
	virtual void Update(const float fDeltaTime) = 0;	// �X�V

	// �����o�֐�
	inline void SetContext(CTitleManager* pContext) { m_pContext = pContext; }	// �R���e�L�X�g�ݒ�

protected:
	// �����o�ϐ�
	CTitleManager* m_pContext;	// �R���e�L�X�g
};

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "titleStateLogo.h"
#include "titleStateSelect.h"
#include "titleStateOption.h"

#endif	// _TITLE_STATE_H_
