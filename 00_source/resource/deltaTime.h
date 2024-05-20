//============================================================
//
//	�f���^�^�C���w�b�_�[ [deltaTime.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _DELTATIME_H_
#define _DELTATIME_H_

//************************************************************
//	�N���X��`
//************************************************************
// �f���^�^�C���N���X
class CDeltaTime
{
public:
	// �R���X�g���N�^
	CDeltaTime();

	// �f�X�g���N�^
	~CDeltaTime();

	// �����o�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	float GetTime(void) { return m_fTime; }	// �o�ߎ��Ԏ擾

	// �ÓI�����o�֐�
	static CDeltaTime *Create(void);				// ����
	static void Release(CDeltaTime *&prDeltaTime);	// �j��

private:
	// �����o�ϐ�
	DWORD m_dwOldTime;	// �O��̏����J�n����
	DWORD m_dwCurTime;	// ����̏����J�n����
	float m_fTime;		// �����̌o�ߎ���
};

#endif	// _DELTATIME_H_
