//============================================================
//
//	�������葬�x�ቺ��ԃw�b�_�[ [introStateTextSlow.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _INTRO_STATE_TEXT_SLOW_H_
#define _INTRO_STATE_TEXT_SLOW_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "introStateText.h"

//************************************************************
//	�N���X��`
//************************************************************
// �������葬�x�ቺ��ԃN���X
class CIntroStateTextSlow : public CIntroStateText
{
public:
	// �R���X�g���N�^
	CIntroStateTextSlow();

	// �f�X�g���N�^
	~CIntroStateTextSlow() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
};

#endif	// _INTRO_STATE_TEXT_SLOW_H_
