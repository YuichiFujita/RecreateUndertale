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
		CIntroState(pIntro)
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
	CIntroStateText(CIntroManager *pIntro) :
		CIntroState(pIntro)
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
	CIntroStateWait(CIntroManager *pIntro) :
		CIntroState(pIntro)
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
	CIntroStateEnd(CIntroManager *pIntro) :
		CIntroState(pIntro)
	{}

	// �f�X�g���N�^
	~CIntroStateEnd() override {}

	// �I�[�o�[���C�h�֐�
	void Update(const float fDeltaTime) override;	// �X�V
};

#endif	// _INTRO_STATE_H_
