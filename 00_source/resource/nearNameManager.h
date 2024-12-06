//============================================================
//
//	���O�ڋ߃}�l�[�W���[�w�b�_�[ [nearNameManager.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _NEAR_NAME_MANAGER_H_
#define _NEAR_NAME_MANAGER_H_

//************************************************************
//	�O���錾
//************************************************************
class CString2D;	// ������2D�N���X
class CText2D;		// �e�L�X�g2D�N���X

//************************************************************
//	�N���X��`
//************************************************************
// ���O�ڋ߃}�l�[�W���[�N���X
class CNearNameManager
{
public:
	// �I���
	enum ESelect
	{
		SELECT_NONE = -1,	// �w��Ȃ�
		SELECT_NO,			// ������
		SELECT_YES,			// �͂�
		SELECT_MAX			// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CNearNameManager();

	// �f�X�g���N�^
	~CNearNameManager();

	// �����o�֐�
	HRESULT Init();	// ������
	void Uninit();	// �I��
	ESelect Update(const float fDeltaTime);	// �X�V
	void TransGame();						// �Q�[����ʑJ��

	// �ÓI�����o�֐�
	static CNearNameManager* Create	// ����
	( // ����
		const std::string& rName,					// �\����
		const std::vector<std::wstring>& rVecStr	// �^�C�g�������e�L�X�g
	);
	static void Release(CNearNameManager*& prNearNameManager);	// �j��

private:
	// �����o�֐�
	void UpdateSelect();	// �I���X�V
	ESelect UpdateDecide();	// ����X�V
	void ShakeName(const float fDeltaTime);	// ���O�U��
	void MoveName(const float fDeltaTime);	// ���O�ړ�
	void SetName(const std::string& rName);	// ���O�ݒ�

	// �����o�ϐ�
	CString2D* m_apSelect[SELECT_MAX];	// �I����
	CText2D* m_pTitle;		// �^�C�g��
	CString2D* m_pName;		// ���O
	int m_nCurSelect;		// ���݂̑I����
	int m_nOldSelect;		// �O��̑I����
	float m_fCurTimeShake;	// ���݂̐U���̌o�ߎ���
	float m_fCurTimeMove;	// ���݂̈ړ��̌o�ߎ���
	float m_fNameDestPosX;	// ���O�̖ڕW�ʒuX
	bool m_bMove;			// ���O�̈ړ���
};

#endif	// _NEAR_NAME_MANAGER_H_
