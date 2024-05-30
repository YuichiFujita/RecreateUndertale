//============================================================
//
//	�C���g���t�F�[�h�w�b�_�[ [introFade.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _INTRO_FADE_H_
#define _INTRO_FADE_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object2D.h"

//************************************************************
//	�N���X��`
//************************************************************
// �C���g���t�F�[�h�N���X
class CIntroFade : public CObject2D
{
public:
	// �t�F�[�h��
	enum EFade
	{
		FADE_IN = 0,	// �t�F�[�h�C��
		FADE_OUT,		// �t�F�[�h�A�E�g
		FADE_MAX		// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CIntroFade();

	// �f�X�g���N�^
	~CIntroFade();

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader *pShader = nullptr) override;	// �`��

	// �ÓI�����o�֐�
	static CIntroFade *Create(void);	// ����

private:
	// �����o�ϐ�
	EFade m_fade;	// �t�F�[�h��
};

#endif	// _INTRO_FADE_H_
