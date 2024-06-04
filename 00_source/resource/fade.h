//============================================================
//
//	�t�F�[�h�w�b�_�[ [fade.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _FADE_H_
#define _FADE_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "scene.h"

//************************************************************
//	�O���錾
//************************************************************
class CObject2D;	// �I�u�W�F�N�g2D�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �t�F�[�h�N���X
class CFade
{
public:
	// �t�F�[�h��ԗ�
	enum EFade
	{
		FADE_NONE = 0,	// �������Ă��Ȃ����
		FADE_WAIT,		// �t�F�[�h�]�C���
		FADE_IN,		// �t�F�[�h�C�����
		FADE_OUT,		// �t�F�[�h�A�E�g���
		FADE_MAX		// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CFade();

	// �f�X�g���N�^
	~CFade();

	// �����o�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(const float fDeltaTime);	// �X�V
	void Draw(void);						// �`��
	EFade GetState(void) const;				// �t�F�[�h��Ԏ擾
	void SetFade(const float fWaitTime);	// �t�F�[�h�J�n�ݒ�
	void SetFade(const CScene::EMode mode, const float fWaitTime);		// ���V�[���ݒ� (�t�F�[�h�̂�)
	void SetLoadFade(const CScene::EMode mode, const float fWaitTime);	// ���V�[���ݒ� (���[�h��ʕt��)

	// �ÓI�����o�֐�
	static CFade *Create(void);			// ����
	static void Release(CFade *&pFade);	// �j��

private:
	// �����o�ϐ�
	CObject2D *m_pFade;			// �t�F�[�h���
	CScene::EMode m_modeNext;	// ���V�[��
	EFade m_fade;				// �t�F�[�h���
	float m_fWaitTime;			// �]�C�Ǘ��J�E���^�[
};

#endif	// _FADE_H_
