//============================================================
//
//	�������Ȃ���ԃw�b�_�[ [startStateNone.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _START_STATE_NONE_H_
#define _START_STATE_NONE_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "startState.h"

//************************************************************
//	�N���X��`
//************************************************************
// �������Ȃ���ԃN���X
class CStartStateNone : public CStartState
{
public:
	// �R���X�g���N�^
	CStartStateNone();

	// �f�X�g���N�^
	~CStartStateNone() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
};

#endif	// _START_STATE_NONE_H_
