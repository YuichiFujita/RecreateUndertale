//============================================================
//
//	�X�^�[�g�}�l�[�W���[�w�b�_�[ [startManager.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _STATEMANAGER_H_
#define _STATEMANAGER_H_

//************************************************************
//	�O���錾
//************************************************************
class CStartState;	// �X�^�[�g��ԃN���X

//************************************************************
//	�N���X��`
//************************************************************
// �X�^�[�g�}�l�[�W���[�N���X
class CStartManager
{
public:
	// �\���e�L�X�g��
	enum EText
	{
		TEXT_PRESS_Z = 0,	// [PRESS Z OR ENTER]
		TEXT_BUTTON_TITLE,	// �� �{�^�������� ��
		TEXT_BUTTON_KINDS,	// �e�푀��{�^��
		TEXT_RULE,			// HP��0�ɂȂ�ƃQ�[���I�[�o�[
		TEXT_START,			// �Q�[�����͂��߂�
		TEXT_OPTION,		// �����Ă�
		TEXT_VIRSION,		// �o�[�W�������
	};

	// �R���X�g���N�^
	CStartManager();

	// �f�X�g���N�^
	~CStartManager();

	// �����o�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(const float fDeltaTime);		// �X�V
	HRESULT ChangeState(CStartState *pState);	// ��ԕύX

	// �ÓI�����o�֐�
	static CStartManager *Create(void);	// ����
	static void Release(CStartManager *&prStartManager);	// �j��

private:
	// �����o�ϐ�
	CStartState *m_pState;	// ���
};

#endif	// _STATEMANAGER_H_
