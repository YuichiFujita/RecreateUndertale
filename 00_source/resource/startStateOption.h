//============================================================
//
//	�����ݒ��ԃw�b�_�[ [startStateOption.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _START_STATE_OPTION_H_
#define _START_STATE_OPTION_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "startState.h"

//************************************************************
//	�N���X��`
//************************************************************
// �����ݒ��ԃN���X
class CStartStateOption : public CStartState
{
public:
	// �R���X�g���N�^
	CStartStateOption();

	// �f�X�g���N�^
	~CStartStateOption() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
};

#endif	// _START_STATE_OPTION_H_
