//============================================================
//
//	���������ԃw�b�_�[ [introStateText.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _INTRO_STATE_TEXT_H_
#define _INTRO_STATE_TEXT_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "introState.h"

//************************************************************
//	�N���X��`
//************************************************************
// ���������ԃN���X
class CIntroStateText : public CIntroState
{
public:
	// �R���X�g���N�^
	CIntroStateText();

	// �f�X�g���N�^
	~CIntroStateText() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
};

#endif	// _INTRO_STATE_TEXT_H_
