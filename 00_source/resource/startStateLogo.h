//============================================================
//
//	���S�\����ԃw�b�_�[ [startStateLogo.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _START_STATE_LOGO_H_
#define _START_STATE_LOGO_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "startState.h"

//************************************************************
//	�O���錾
//************************************************************
class CObject2D;	// �I�u�W�F�N�g2D�N���X
class CString2D;	// ������2D�N���X

//************************************************************
//	�N���X��`
//************************************************************
// ���S�\����ԃN���X
class CStartStateLogo : public CStartState
{
public:
	// �R���X�g���N�^
	CStartStateLogo();

	// �f�X�g���N�^
	~CStartStateLogo() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V

private:
	// �����o�ϐ�
	CObject2D *m_pLogo;	// �^�C�g�����S
	CString2D *m_pCont;	// �������
	float m_fCurTime;	// ���݂̑ҋ@����
};

#endif	// _START_STATE_LOGO_H_