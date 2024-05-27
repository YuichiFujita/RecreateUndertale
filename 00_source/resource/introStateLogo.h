//============================================================
//
//	���S�\����ԃw�b�_�[ [introStateLogo.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _INTRO_STATE_LOGO_H_
#define _INTRO_STATE_LOGO_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "introState.h"

//************************************************************
//	�O���錾
//************************************************************
class CIntroManager;	// �C���g���}�l�[�W���[�N���X
class CObject2D;		// �I�u�W�F�N�g2D�N���X

//************************************************************
//	�N���X��`
//************************************************************
// ���S�\����ԃN���X
class CIntroStateLogo : public CIntroState
{
public:
	// �R���X�g���N�^
	CIntroStateLogo(CIntroManager *pIntro) :
		CIntroState(pIntro),	// �C�j�V�����C�U
		m_pLogo	(nullptr)		// �^�C�g�����S
	{}

	// �f�X�g���N�^
	~CIntroStateLogo() override {}

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V

private:
	// �����o�ϐ�
	CObject2D *m_pLogo;	// �^�C�g�����S
};

#endif	// _INTRO_STATE_LOGO_H_
