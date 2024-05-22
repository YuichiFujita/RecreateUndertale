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
class CObject2D;		// �I�u�W�F�N�g2D�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �C���g����ԃN���X
class CIntroState
{
public:
	// �R���X�g���N�^
	CIntroState(CIntroManager *pIntro) :
		m_pIntro	(pIntro)	// �C���g���}�l�[�W���[
	{}

	// �f�X�g���N�^
	virtual ~CIntroState() {}

	// �������z�֐�
	virtual HRESULT Init(void)	= 0;	// ������
	virtual void Uninit(void)	= 0;	// �I��
	virtual void Update(const float fDeltaTime) = 0;	// �X�V

protected:
	// �����o�ϐ�
	CIntroManager *m_pIntro;	// �C���g���}�l�[�W���[
};

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

// ���������ԃN���X
class CIntroStateText : public CIntroState
{
public:
	// �R���X�g���N�^
	CIntroStateText(CIntroManager *pIntro) :
		CIntroState(pIntro)	// �C�j�V�����C�U
	{}

	// �f�X�g���N�^
	~CIntroStateText() override {}

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
};

// �ҋ@��ԃN���X
class CIntroStateWait : public CIntroState
{
public:
	// �R���X�g���N�^
	CIntroStateWait(CIntroManager *pIntro) :
		CIntroState(pIntro)	// �C�j�V�����C�U
	{}

	// �f�X�g���N�^
	~CIntroStateWait() override {}

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
};

// �I����ԃN���X
class CIntroStateEnd : public CIntroState
{
public:
	// �R���X�g���N�^
	CIntroStateEnd(CIntroManager *pIntro) :
		CIntroState(pIntro)	// �C�j�V�����C�U
	{}

	// �f�X�g���N�^
	~CIntroStateEnd() override {}

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
};

#endif	// _INTRO_STATE_H_
