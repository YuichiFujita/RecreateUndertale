//============================================================
//
//	�`���[�g���A����ԃw�b�_�[ [startStateTutorial.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _START_STATE_TUTORIAL_H_
#define _START_STATE_TUTORIAL_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "startState.h"

//************************************************************
//	�O���錾
//************************************************************
class CString2D;	// ������2D�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �`���[�g���A����ԃN���X
class CStartStateTutorial : public CStartState
{
public:
	// �R���X�g���N�^
	CStartStateTutorial();

	// �f�X�g���N�^
	~CStartStateTutorial() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V

private:
	// �����o�ϐ�
	CString2D *m_pVersion;	// �o�[�W�����\�L
};

#endif	// _START_STATE_TUTORIAL_H_
