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

	// �e�L�X�g�\����
	struct SText
	{
		// �����o�ϐ�
		std::vector<std::vector<std::string>> vec;	// �e�L�X�g���I�z��
	};

	// �������z�֐�
	virtual void Use(void)	= 0;	// �A�C�e���g�p
	virtual void Info(void)	= 0;	// �A�C�e�����
	virtual void Drop(void)	= 0;	// �A�C�e���j��

	// ���z�֐�
	virtual HRESULT Init(void);	// ������
	virtual void Uninit(void);	// �I��

	// �ÓI�����o�֐�
	static CItemData *Create(const EType type);	// ����

	// �����o�֐�
	void SetName(const char* pName)		{ m_sName = pName; }		// �A�C�e�����ݒ�
	const char* GetName(void) const		{ return m_sName.c_str(); }	// �A�C�e�����擾
	void SetUse(const SText& rVecUse)	{ m_vecUse = rVecUse; }		// �g�p�e�L�X�g�ݒ�
	const SText& GetUse(void) const		{ return m_vecUse; }		// �g�p�e�L�X�g�擾
	void SetInfo(const SText& rVecInfo)	{ m_vecInfo = rVecInfo; }	// ���e�L�X�g�ݒ�
	const SText& GetInfo(void) const	{ return m_vecInfo; }		// ���e�L�X�g�擾

private:
	// �����o�ϐ�
	std::string m_sName;	// �A�C�e����
	SText m_vecUse;			// �g�p�e�L�X�g
	SText m_vecInfo;		// ���e�L�X�g
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
	HRESULT Init(void);		// �A�C�e��������
	void Uninit(void);		// �A�C�e���I��
	HRESULT LoadAll(void);	// �A�C�e���S�Ǎ�
	const CItemData& GetInfo(const int nID);	// �A�C�e�����擾

	// �ÓI�����o�֐�
	static CItem *Create(void);			// ����
	static void Release(CItem *&pItem);	// �j��

private:
	// �����o�֐�
	HRESULT LoadSetup(void);	// �Z�b�g�A�b�v
	CItemData::SText LoadText(std::ifstream& rFile, const char *pEndStr);	// �e�L�X�g�Z�b�g�A�b�v

	// �����o�ϐ�
	std::vector<CItemData*> m_vecItemData;	// �A�C�e�����I�z��
};

#endif	// _ITEM_H_
