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
//	�O���錾
//************************************************************
class CItemData;	// �A�C�e�����N���X

//************************************************************
//	�N���X��`
//************************************************************
// �A�C�e���N���X
class CItem
{
public:
	// ��ޗ�
	enum EType
	{
		TYPE_CANDY_MONSTER = 0,	// �����X�^�[����
		TYPE_MAX				// ���̗񋓌^�̑���
	};

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

	// �����o�ϐ�
	CItemData *m_apItemData[TYPE_MAX];	// �A�C�e���z��
};

// �A�C�e�����N���X
class CItemData
{
public:
	// �R���X�g���N�^
	CItemData();

	// �f�X�g���N�^
	virtual ~CItemData();

	// �������z�֐�
	virtual HRESULT Init(void)	= 0;	// ������
	virtual void Uninit(void)	= 0;	// �I��
	virtual void Use(void)		= 0;	// �A�C�e���g�p
	virtual void Info(void)		= 0;	// �A�C�e�����
	virtual void Drop(void)		= 0;	// �A�C�e���j��

	// �ÓI�����o�֐�
	static CItemData *Create(void);				// ����
	static void Release(CItemData *&pItemData);	// �j��

	// �����o�֐�
	void SetName(const char* pName) { m_sName = pName; }	// �A�C�e�����ݒ�

private:
	// �����o�ϐ�
	std::string m_sName;	// �A�C�e����
	std::vector<std::vector<std::string>> m_vecUse;		// �g�p�e�L�X�g
	std::vector<std::vector<std::string>> m_vecInfo;	// ���e�L�X�g
};

#endif	// _ITEM_H_
