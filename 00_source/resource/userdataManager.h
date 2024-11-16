//============================================================
//
//	���[�U�[�f�[�^�}�l�[�W���[�w�b�_�[ [userdataManager.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _USERDATA_MANAGER_H_
#define _USERDATA_MANAGER_H_

//************************************************************
//	�N���X��`
//************************************************************
// ���[�U�[�f�[�^�}�l�[�W���[�N���X
class CUserDataManager
{
public:
	// �R���X�g���N�^
	CUserDataManager();

	// �f�X�g���N�^
	~CUserDataManager();

	// �����o�֐�
	HRESULT Init();	// ������
	void Uninit();	// �I��
	void Update(const float fDeltaTime);	// �X�V

	// �ÓI�����o�֐�
	static CUserDataManager* Create();		// ����
	static CUserDataManager* GetInstance();	// �擾
	static void Release();					// �j��

private:
	// �ÓI�����o�ϐ�
	static CUserDataManager* m_pInstance;	// ���g�̃C���X�^���X

	// �����o�ϐ�
	float m_fPlayTime;	// �v���C������
};

#endif	// _USERDATA_MANAGER_H_
