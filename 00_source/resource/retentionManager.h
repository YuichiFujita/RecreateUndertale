//============================================================
//
//	�f�[�^�ۑ��}�l�[�W���[�w�b�_�[ [retentionManager.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _RETENTION_MANAGER_H_
#define _RETENTION_MANAGER_H_

//************************************************************
//	�N���X��`
//************************************************************
// �f�[�^�ۑ��}�l�[�W���[�N���X
class CRetentionManager
{
public:
	// ������
	enum EWin
	{
		WIN_NONE,	// ����
		WIN_FAILED,	// �������s
		WIN_CLEAR,	// ��������
		WIN_MAX		// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CRetentionManager();

	// �f�X�g���N�^
	~CRetentionManager();

	// ���U���g���\����
	struct SResult
	{
		EWin win;		// ������
		float fTime;	// �o�߃^�C��
	};

	// �����o�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��

	// �ÓI�����o�֐�
	static CRetentionManager *Create(void);	// ����
	static void Release(CRetentionManager *&prRetentionManager);	// �j��

	// �����o�֐�
	void SetResult(const EWin win, const float fTime);		// ���U���g���ݒ�
	EWin GetWin(void) const		{ return m_result.win; }	// �����󋵎擾
	float GetTime(void) const	{ return m_result.fTime; }	// �o�߃^�C���擾

private:
	// �����o�ϐ�
	SResult m_result;	// ���U���g���
};

#endif	// _RETENTION_MANAGER_H_
