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
	// �萔
	static constexpr int	PRIORITY	= 7;		// �D�揇��
	static constexpr float	DEF_LEVEL	= 1.0f;		// ���l������ (�f�t�H���g)
	static constexpr float	SKIP_LEVEL	= 120.0f;	// ���l������ (�X�L�b�v)

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
	EFade GetState(void) const { return m_fade; }	// �t�F�[�h��Ԏ擾

	void SetFade	// �t�F�[�h�J�n�ݒ�
	( // ����
		const float fAddOut	= DEF_LEVEL,	// �A�E�g�̃��l������
		const float fSubIn	= DEF_LEVEL,	// �C���̃��l������
		const int nPriority	= PRIORITY		// �D�揇��
	);
	void SetModeFade	// ���V�[���ݒ� (�t�F�[�h�̂�)
	( // ����
		const CScene::EMode mode,				// ���V�[��
		const float fWaitTime	= 0.0f,			// �]�C����
		const float fAddOut		= DEF_LEVEL,	// �A�E�g�̃��l������
		const float fSubIn		= DEF_LEVEL		// �C���̃��l������
	);
	void SetLoadFade	// ���V�[���ݒ� (���[�h��ʕt��)
	( // ����
		const CScene::EMode mode,				// ���V�[��
		const float fWaitTime	= 0.0f,			// �]�C����
		const float fAddOut		= DEF_LEVEL,	// �A�E�g�̃��l������
		const float fSubIn		= DEF_LEVEL		// �C���̃��l������
	);

private:
	// �����o�ϐ�
	std::function<HRESULT(CScene::EMode)> m_pFuncSetMode;	// ���[�h�ݒ�֐��|�C���^
	CScene::EMode m_modeNext;	// ���V�[��
	EFade m_fade;		// �t�F�[�h���
	float m_fWaitTime;	// ���݂̗]�C����
	float m_fSubIn;		// �C���̃��l������
	float m_fAddOut;	// �A�E�g�̃��l������
};

#endif	// _FADE_H_
