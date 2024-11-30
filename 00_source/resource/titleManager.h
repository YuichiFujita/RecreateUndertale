//============================================================
//
//	�^�C�g���}�l�[�W���[�w�b�_�[ [titleManager.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _TITLEMANAGER_H_
#define _TITLEMANAGER_H_

//************************************************************
//	�O���錾
//************************************************************
class CString2D;	// ������2D�N���X
class CVersion;		// �o�[�W�����\�L�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �^�C�g���}�l�[�W���[�N���X
class CTitleManager
{
public:
	// �\���e�L�X�g��
	enum EText
	{
		TEXT_CONTINUE = 0,	// �R���e�B�j���[
		TEXT_RESET,			// ���Z�b�g
		TEXT_SETTING,		// �ݒ�
		TEXT_MAX			// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CTitleManager();

	// �f�X�g���N�^
	~CTitleManager();

	// �����o�֐�
	HRESULT Init();	// ������
	void Uninit();	// �I��
	void Update(const float fDeltaTime);	// �X�V

	// �ÓI�����o�֐�
	static CTitleManager* Create();	// ����
	static void Release(CTitleManager*& prTitleManager);	// �j��

private:
	// �����o�֐�
	void UpdateSelect();	// �I���X�V
	void UpdateDecide();	// ����X�V

	// �����o�ϐ�
	std::vector<std::vector<CString2D*>> m_vecSelect;	// �I�������
	CString2D* m_pName;		// ���O���
	CString2D* m_pLove;		// ���x�����
	CString2D* m_pTime;		// ���v���C���ԏ��
	CVersion* m_pVersion;	// �o�[�W�����\�L���
	POSGRID2 m_curSelect;	// ���݂̑I����
	POSGRID2 m_oldSelect;	// �O��̑I����
};

#endif	// _TITLEMANAGER_H_
