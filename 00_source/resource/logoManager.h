//============================================================
//
//	���S�}�l�[�W���[�w�b�_�[ [logoManager.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _LOGO_MANAGER_H_
#define _LOGO_MANAGER_H_

//************************************************************
//	�O���錾
//************************************************************
class CObject2D;	// �I�u�W�F�N�g2D�N���X
class CString2D;	// ������2D�N���X

//************************************************************
//	�N���X��`
//************************************************************
// ���S�}�l�[�W���[�N���X
class CLogoManager
{
public:
	// �R���X�g���N�^
	CLogoManager();

	// �f�X�g���N�^
	~CLogoManager();

	// �����o�֐�
	HRESULT Init();	// ������
	void Uninit();	// �I��
	void Update(const float fDeltaTime);	// �X�V

	// �ÓI�����o�֐�
	static CLogoManager* Create();	// ����
	static void Release(CLogoManager*& prLogoManager);	// �j��

private:
	// �����o�֐�
	void UpdateDispTrans(const float fDeltaTime);	// ����\���E�J�ڍX�V
	void UpdateCommand();	// �R�}���h���͍X�V

	// �����o�ϐ�
	std::string m_sFragInput;	// �L�[���̓t���O
	CObject2D* m_pLogo;	// �^�C�g�����S
	CString2D* m_pCont;	// �������
	float m_fCurTime;	// ���݂̑ҋ@����
	bool m_bSndBall;	// BALL�R�}���h�Đ��t���O
};

#endif	// _LOGO_MANAGER_H_
