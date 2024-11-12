//============================================================
//
//	�A�C�e���w�b�_�[ [item.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _ITEM_H_
#define _ITEM_H_

//************************************************************
//	�N���X��`
//************************************************************
// �A�C�e�����N���X
class CItemData
{
public:
	// ��ޗ�
	enum EType
	{
		TYPE_NONE = 0,	// ������ʂȂ�
		TYPE_HEAL,		// HP�֗^
		TYPE_MAX		// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CItemData();

	// �f�X�g���N�^
	virtual ~CItemData();

	// �������z�֐�
	virtual void Use() const	= 0;	// �A�C�e���g�p
	virtual void Info() const	= 0;	// �A�C�e�����
	virtual void Drop() const	= 0;	// �A�C�e���j��
	virtual HRESULT LoadSetup(std::ifstream* pFile, std::string& rString) = 0;	// ��ނ��Ƃ̃Z�b�g�A�b�v

	// ���z�֐�
	virtual HRESULT Init();	// ������
	virtual void Uninit();	// �I��
	virtual std::string Detail() const;	// �A�C�e���ڍׂ̕�����擾
	virtual std::string UseEnd() const;	// �A�C�e���g�p��̕�����擾

	// �ÓI�����o�֐�
	static CItemData* Create(const EType type);	// ����

	// �����o�֐�
	void InitText();	// �e�L�X�g������
	inline void SetName(const char* pName)			{ m_sName = pName; }		// �A�C�e�����ݒ�
	inline const char* GetName() const				{ return m_sName.c_str(); }	// �A�C�e�����擾
	inline void SetAddAtk(const int nAddAtk)		{ m_nAddAtk = nAddAtk; }	// �U���͏㏸�ʐݒ�
	inline int GetAddAtk() const					{ return m_nAddAtk; }		// �U���͏㏸�ʎ擾
	inline void SetAddDef(const int nAddDef)		{ m_nAddDef = nAddDef; }	// �h��͏㏸�ʐݒ�
	inline int GetAddDef() const					{ return m_nAddDef; }		// �h��͏㏸�ʎ擾
	inline void SetUse(const ATextBox& rVecUse)		{ m_vecUse = rVecUse; }		// �g�p�e�L�X�g�ݒ�
	inline const ATextBox& GetUse() const			{ return m_vecUse; }		// �g�p�e�L�X�g�擾
	inline void SetInfo(const ATextBox& rVecInfo)	{ m_vecInfo = rVecInfo; }	// ���e�L�X�g�ݒ�
	inline const ATextBox& GetInfo() const			{ return m_vecInfo; }		// ���e�L�X�g�擾
	inline void SetDrop(const ATextBox& rVecDrop)	{ m_vecDrop = rVecDrop; }	// �j���e�L�X�g�ݒ�
	inline const ATextBox& GetDrop() const			{ return m_vecDrop; }		// �j���e�L�X�g�擾

private:
	// �����o�ϐ�
	std::string m_sName;	// �A�C�e����
	int m_nAddAtk;			// �U���͏㏸��
	int m_nAddDef;			// �h��͏㏸��
	ATextBox m_vecUse;		// �g�p�e�L�X�g
	ATextBox m_vecInfo;		// ���e�L�X�g
	ATextBox m_vecDrop;		// �j���e�L�X�g
};

// �A�C�e���N���X
class CItem
{
public:
	// �R���X�g���N�^
	CItem();

	// �f�X�g���N�^
	~CItem();

	// �����o�֐�
	HRESULT Init();		// �A�C�e��������
	void Uninit();		// �A�C�e���I��
	HRESULT LoadAll();	// �A�C�e���S�Ǎ�
	const CItemData& GetInfo(const int nIdx);	// �A�C�e�����擾

	// �ÓI�����o�֐�
	static CItem* Create();					// ����
	static void Release(CItem*& prItem);	// �j��

private:
	// �����o�֐�
	HRESULT LoadSetup();	// �Z�b�g�A�b�v
	ATextBox LoadText(std::ifstream& rFile, const char* pEndStr, const CItemData& rItem);	// �e�L�X�g�Z�b�g�A�b�v
	void ReplaceCommand(std::string* pStr, const CItemData& rItem);	// ��������̃R�}���h�̒u��

	// �����o�ϐ�
	std::vector<CItemData*> m_vecItemData;	// �A�C�e�����I�z��
};

#endif	// _ITEM_H_
