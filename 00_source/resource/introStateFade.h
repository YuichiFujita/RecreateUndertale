//============================================================
//
//	�t�F�[�h��ԃw�b�_�[ [introStateFade.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _INTRO_STATE_FADE_H_
#define _INTRO_STATE_FADE_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "introState.h"

//************************************************************
//	�N���X��`
//************************************************************
// �t�F�[�h��ԃN���X
class CIntroStateFade : public CIntroState
{
public:
	// �R���X�g���N�^
	CIntroStateFade();

	// �f�X�g���N�^
	~CIntroStateFade() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
};

#endif	// _INTRO_STATE_FADE_H_
