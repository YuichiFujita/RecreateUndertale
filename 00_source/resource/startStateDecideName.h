//============================================================
//
//	���O�����ԃw�b�_�[ [startStateDecideName.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _START_STATE_DECIDE_NAME_H_
#define _START_STATE_DECIDE_NAME_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "startState.h"

//************************************************************
//	�N���X��`
//************************************************************
// ���O�����ԃN���X
class CStartStateDecideName : public CStartState
{
public:
	// �R���X�g���N�^
	CStartStateDecideName();

	// �f�X�g���N�^
	~CStartStateDecideName() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
};

#endif	// _START_STATE_DECIDE_NAME_H_
