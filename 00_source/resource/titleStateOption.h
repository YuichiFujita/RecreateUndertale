//============================================================
//
//	�ݒ��ԃw�b�_�[ [titleStateOption.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _TITLE_STATE_OPTION_H_
#define _TITLE_STATE_OPTION_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "titleState.h"

//************************************************************
//	�O���錾
//************************************************************
class COptionManager;	// �ݒ�}�l�[�W���[�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �ݒ��ԃN���X
class CTitleStateOption : public CTitleState
{
public:
	// �R���X�g���N�^
	CTitleStateOption();

	// �f�X�g���N�^
	~CTitleStateOption() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V

private:
	// �����o�ϐ�
	COptionManager* m_pOptionManager;	// �ݒ�}�l�[�W���[
};

#endif	// _TITLE_STATE_OPTION_H_
