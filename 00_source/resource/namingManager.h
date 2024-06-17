//============================================================
//
//	�����}�l�[�W���[�w�b�_�[ [namingManager.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _NAMING_MANAGER_H_
#define _NAMING_MANAGER_H_

//************************************************************
//	�O���錾
//************************************************************
class CStartStateCreateName;	// ������ԃN���X
class CString2D;				// ������2D�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �����}�l�[�W���[�N���X
class CNamingManager
{
public:
	// ������ޗ�
	enum ETypeChar
	{
		TYPECHAR_HIRAGANA = 0,	// �Ђ炪��
		TYPECHAR_KATAKANA,		// �J�^�J�i
		TYPECHAR_ALPHABET,		// �A���t�@�x�b�g
		TYPECHAR_MAX			// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CNamingManager(CStartStateCreateName *pParent);

	// �f�X�g���N�^
	~CNamingManager();

	// �����o�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(const float fDeltaTime);			// �X�V
	HRESULT ChangeChar(const ETypeChar typeChar);	// �����ύX

	// �ÓI�����o�֐�
	static CNamingManager *Create(CStartStateCreateName *pParent);	// ����
	static void Release(CNamingManager *&prNamingManager);	// �j��

private:
	// �����o�֐�
	int GetSelectWidth(void)	{ return (int)m_vecSelect[0].size(); }	// ���̕������擾
	int GetSelectHeight(void)	{ return (int)m_vecSelect.size(); }		// �c�̕������擾
	void UpdateSelect(void);	// �I���X�V
	void UpdateDecide(void);	// ����X�V
	void ClearVector(void);		// �I�𕶎��̓��I�z��N���A
	HRESULT LoadArray(const ETypeChar typeChar);	// �z�u�Ǎ�

	// �����o�ϐ�
	std::vector<std::vector<CString2D*>> m_vecSelect;	// �I�𕶎�
	CStartStateCreateName *m_pParent;	// ���g���Ǘ�����e
	POSGRID2 m_curSelect;	// ���݂̑I�𕶎�
	POSGRID2 m_oldSelect;	// �O��̑I�𕶎�
};

#endif	// _NAMING_MANAGER_H_
