//============================================================
//
//	�Ђ炪�ȏ�ԃw�b�_�[ [charStateHiragana.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _CHAR_STATE_HIRAGANA_H_
#define _CHAR_STATE_HIRAGANA_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "charState.h"

//************************************************************
//	�N���X��`
//************************************************************
// �Ђ炪�ȏ�ԃN���X
class CCharStateHiragana : public CCharState
{
public:
	// �R���X�g���N�^
	CCharStateHiragana();

	// �f�X�g���N�^
	~CCharStateHiragana() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
};

#endif	// _CHAR_STATE_HIRAGANA_H_
