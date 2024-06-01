//============================================================
//
//	�ҋ@��ԃw�b�_�[ [introStateWait.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _INTRO_STATE_WAIT_H_
#define _INTRO_STATE_WAIT_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "introState.h"

//************************************************************
//	�N���X��`
//************************************************************
// �ҋ@��ԃN���X
class CIntroStateWait : public CIntroState
{
public:
	// �R���X�g���N�^
	CIntroStateWait(const float fEndTime);

	// �f�X�g���N�^
	~CIntroStateWait() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V

private:
	// �����o�ϐ�
	const float m_fEndTime;	// �ҋ@�̏I������
	float m_fCurTime;		// ���݂̑ҋ@����
};

#endif	// _INTRO_STATE_WAIT_H_
