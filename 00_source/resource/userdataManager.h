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
//	�O���錾
//************************************************************
class CPlayerStatus;	// �v���C���[�X�e�[�^�X�N���X
class CPlayerItem;		// �v���C���[�����A�C�e���N���X

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
	void Update(const float fDeltaTime);				// �X�V
	HRESULT InitPlayerStatus(CPlayerStatus* pStatus);	// �v���C���[�X�e�[�^�X������
	HRESULT LoadPlayerStatus(CPlayerStatus* pStatus);	// �v���C���[�X�e�[�^�X�Ǎ�
	HRESULT InitPlayerItem(CPlayerItem* pItem);			// �v���C���[�����A�C�e��������
	HRESULT LoadPlayerItem(CPlayerItem* pItem);			// �v���C���[�����A�C�e���Ǎ�
	HRESULT LoadUserData();								// ���[�U�[�f�[�^�Ǎ�

	// �ÓI�����o�֐�
	static CUserDataManager* Create();		// ����
	static CUserDataManager* GetInstance();	// �擾
	static void Release();					// �j��

private:
	// �����o�֐�
	HRESULT LoadPlayerStatus(CPlayerStatus* pStatus, const char* pFilePath);	// �v���C���[�X�e�[�^�X�Ǎ� (�p�X�w��)
	HRESULT LoadPlayerItem(CPlayerItem* pItem, const char* pFilePath);			// �v���C���[�����A�C�e���Ǎ� (�p�X�w��)

	// �ÓI�����o�ϐ�
	static CUserDataManager* m_pInstance;	// ���g�̃C���X�^���X

	// �����o�ϐ�
	int m_nRoom;		// �����ԍ�
	int m_nFun;			// FUN�l
	float m_fPlayTime;	// ���v���C����
};

#endif	// _USERDATA_MANAGER_H_
