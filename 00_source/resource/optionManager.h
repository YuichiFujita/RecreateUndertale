//============================================================
//
//	�ݒ�}�l�[�W���[�w�b�_�[ [optionManager.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _OPTION_MANAGER_H_
#define _OPTION_MANAGER_H_

//************************************************************
//	�O���錾
//************************************************************
class CString2D;	// ������2D�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �ݒ�}�l�[�W���[�N���X
class COptionManager
{
public:
	// �\���e�L�X�g��
	enum EText
	{
		TEXT_TITLE = 0,	// �����Ă�
		TEXT_CLOSE,		// �Ƃ���
		TEXT_MAX		// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	COptionManager();

	// �f�X�g���N�^
	~COptionManager();

	// �����o�֐�
	HRESULT Init();	// ������
	void Uninit();	// �I��
	bool Update(const float fDeltaTime);	// �X�V

	// �ÓI�����o�֐�
	static COptionManager* Create();	// ����
	static void Release(COptionManager*& prOptionManager);	// �j��

private:
	// �I���
	enum ESelect
	{
		SELECT_CLOSE = 0,	// ����
		SELECT_MAX			// ���̗񋓌^�̑���
	};

	// �����o�֐�
	void UpdateSelect();	// �I���X�V
	bool UpdateDecide();	// ����X�V

	// �����o�ϐ�
	CString2D* m_apSelect[SELECT_MAX];	// �I����
	CString2D* m_pTitle;	// �^�C�g��
	int m_nCurSelect;		// ���݂̑I����
	int m_nOldSelect;		// �O��̑I����
};

#endif	// _OPTION_MANAGER_H_
