//============================================================
//
//	���S��ԃw�b�_�[ [startStateLogo.h]
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
//	�N���X��`
//************************************************************
// ���S��ԃN���X
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
};

#endif	// _START_STATE_LOGO_H_
