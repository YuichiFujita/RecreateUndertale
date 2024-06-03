//============================================================
//
//	�I����ԃw�b�_�[ [introStateEnd.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _INTRO_STATE_END_H_
#define _INTRO_STATE_END_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "introState.h"

//************************************************************
//	�N���X��`
//************************************************************
// �I����ԃN���X
class CIntroStateEnd : public CIntroState
{
public:
	// �R���X�g���N�^
	CIntroStateEnd();

	// �f�X�g���N�^
	~CIntroStateEnd() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V

private:
	// �����o�ϐ�
	float m_fCurTime;	// ���݂̑ҋ@����
};

#endif	// _INTRO_STATE_END_H_
