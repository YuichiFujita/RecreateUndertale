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
