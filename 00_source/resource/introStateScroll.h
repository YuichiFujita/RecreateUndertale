//============================================================
//
//	����X�N���[����ԃw�b�_�[ [introStateScroll.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _INTRO_STATE_SCROLL_H_
#define _INTRO_STATE_SCROLL_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "introState.h"

//************************************************************
//	�N���X��`
//************************************************************
// ����X�N���[����ԃN���X
class CIntroStateScroll : public CIntroState
{
public:
	// �R���X�g���N�^
	CIntroStateScroll();

	// �f�X�g���N�^
	~CIntroStateScroll() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
};

#endif	// _INTRO_STATE_SCROLL_H_
