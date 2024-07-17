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
	void SetNextMode(const CScene::EMode next)	{ m_modeNext = next; }	// �J�ڐ惂�[�h�ݒ�
	CScene::EMode GetNextMode(void) const		{ return m_modeNext; }	// �J�ڐ惂�[�h�擾
	EFade GetState(void) const	{ return m_fade; }						// �t�F�[�h��Ԏ擾
	bool IsFade(void) const		{ return m_fade != FADE_NONE; }			// �t�F�[�h�󋵎擾

	void SetFade	// �t�F�[�h�J�n�ݒ�
	( // ����
		const float fAddOut		= DEF_LEVEL,	// �A�E�g�̃��l������
		const float fSubIn		= DEF_LEVEL,	// �C���̃��l������
		const int nPriority		= PRIORITY,		// �D�揇��
		const D3DXCOLOR colFade	= XCOL_ABLACK	// �t�F�[�h�F
	);
	void SetModeFade	// �J�ڐ惂�[�h�ݒ� (�t�F�[�h�̂�)
	( // ����
		const CScene::EMode mode,				// �J�ڐ惂�[�h
		const float fWaitTime	= 0.0f,			// �]�C����
		const float fAddOut		= DEF_LEVEL,	// �A�E�g�̃��l������
		const float fSubIn		= DEF_LEVEL,	// �C���̃��l������
		const D3DXCOLOR colFade	= XCOL_ABLACK	// �t�F�[�h�F
	);
	void SetLoadFade	// �J�ڐ惂�[�h�ݒ� (���[�h��ʕt��)
	( // ����
		const CScene::EMode mode,				// �J�ڐ惂�[�h
		const float fWaitTime	= 0.0f,			// �]�C����
		const float fAddOut		= DEF_LEVEL,	// �A�E�g�̃��l������
		const float fSubIn		= DEF_LEVEL,	// �C���̃��l������
		const D3DXCOLOR colFade	= XCOL_ABLACK	// �t�F�[�h�F
	);
	void SetRoomFade(void);	// �J�ڐ惋�[���ݒ�

private:
	// �����o�ϐ�
	std::function<HRESULT(void)> m_funcSetMode;	// ���[�h�ݒ�֐��|�C���^
	CScene::EMode m_modeNext;	// �J�ڐ惂�[�h
	EFade m_fade;		// �t�F�[�h���
	float m_fWaitTime;	// ���݂̗]�C����
	float m_fSubIn;		// �C���̃��l������
	float m_fAddOut;	// �A�E�g�̃��l������
};

#endif	// _FADE_H_
