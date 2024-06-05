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
#include "object2D.h"

//************************************************************
//	�N���X��`
//************************************************************
// �t�F�[�h�N���X
class CFade : public CObject2D
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

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader *pShader = nullptr) override;	// �`��

	// �ÓI�����o�֐�
	static CFade *Create(void);	// ����

	// �����o�֐�
	EFade GetState(void) const { return m_fade; }			// �t�F�[�h��Ԏ擾
	void SetFade(const float fLevel, const int nPriority);	// �t�F�[�h�J�n�ݒ�
	void SetModeFade(const CScene::EMode mode, const float fWaitTime);	// ���V�[���ݒ� (�t�F�[�h�̂�)
	void SetLoadFade(const CScene::EMode mode, const float fWaitTime);	// ���V�[���ݒ� (���[�h��ʕt��)

private:
	// �����o�ϐ�
	std::function<HRESULT(CScene::EMode)> m_pFuncSetMode;	// ���[�h�ݒ�֐��|�C���^
	CScene::EMode m_modeNext;	// ���V�[��
	EFade m_fade;		// �t�F�[�h���
	float m_fWaitTime;	// ���݂̗]�C����
	float m_fLevel;		// ���l������
};

#endif	// _FADE_H_
