//============================================================
//
//	�C���g����ԃw�b�_�[ [introState.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _INTRO_STATE_H_
#define _INTRO_STATE_H_

//************************************************************
//	�O���錾
//************************************************************
class CIntroManager;	// �C���g���}�l�[�W���[�N���X
class CIntroState;		// �C���g����ԃN���X

//************************************************************
//	�N���X��`
//************************************************************
// �C���g���R���e�L�X�g�N���X
class CIntroContext
{
public:
	// �R���X�g���N�^
	CIntroContext(CIntroManager *pIntro) :
		m_pIntro(pIntro),	// �C���g���}�l�[�W���[
		m_pState(nullptr)	// ��ԃC���X�^���X
	{}

	// �f�X�g���N�^
	~CIntroContext() { SAFE_DELETE(m_pState); }

	// �����o�֐�
	void Update(const float fDeltaTime);	// �X�V
	void Change(CIntroState *pState);		// ��ԕύX

//private:	// TODO�F�{����΃_���I
	// �����o�ϐ�
	CIntroManager *m_pIntro;	// �C���g���}�l�[�W���[
	CIntroState *m_pState;		// ��ԃC���X�^���X
};

// �C���g����ԃN���X
class CIntroState
{
public:
	// �R���X�g���N�^
	CIntroState(CIntroContext *pContext) :
		m_pContext(pContext)	// �C���g���R���e�L�X�g
	{}

	// �f�X�g���N�^
	virtual ~CIntroState() {}

	// �������z�֐�
	virtual void Update(const float fDeltaTime) = 0;	// �X�V

protected:
	// �����o�ϐ�
	CIntroContext *m_pContext;	// �C���g���R���e�L�X�g
};

// ���S�\����ԃN���X
class CIntroStateLogo : public CIntroState
{
public:
	// �R���X�g���N�^
	CIntroStateLogo(CIntroContext *pContext) :
		CIntroState(pContext)
	{}

	// �f�X�g���N�^
	~CIntroStateLogo() override {}

	// �I�[�o�[���C�h�֐�
	void Update(const float fDeltaTime) override;	// �X�V
};

// ���������ԃN���X
class CIntroStateText : public CIntroState
{
public:
	// �R���X�g���N�^
	CIntroStateText(CIntroContext *pContext) :
		CIntroState(pContext)
	{}

	// �f�X�g���N�^
	~CIntroStateText() override {}

	// �I�[�o�[���C�h�֐�
	void Update(const float fDeltaTime) override;	// �X�V
};

// �ҋ@��ԃN���X
class CIntroStateWait : public CIntroState
{
public:
	// �R���X�g���N�^
	CIntroStateWait(CIntroContext *pContext) :
		CIntroState(pContext)
	{}

	// �f�X�g���N�^
	~CIntroStateWait() override {}

	// �I�[�o�[���C�h�֐�
	void Update(const float fDeltaTime) override;	// �X�V
};

// �I����ԃN���X
class CIntroStateEnd : public CIntroState
{
public:
	// �R���X�g���N�^
	CIntroStateEnd(CIntroContext *pContext) :
		CIntroState(pContext)
	{}

	// �f�X�g���N�^
	~CIntroStateEnd() override {}

	// �I�[�o�[���C�h�֐�
	void Update(const float fDeltaTime) override;	// �X�V
};

#endif	// _INTRO_STATE_H_
