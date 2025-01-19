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
//	�C���N���[�h�t�@�C��
//************************************************************
#include "frame2DModuleText.h"

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
		TYPE_WEAPON,	// ����
		TYPE_ARMOR,		// �h��
		TYPE_MAX		// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CItemData();

	// �f�X�g���N�^
	virtual ~CItemData();

	// �������z�֐�
	virtual void Use(const int nBagIdx) const = 0;	// �A�C�e���g�p
	virtual HRESULT LoadSetup(std::ifstream* pFile, std::string& rString) = 0;	// ��ނ��Ƃ̃Z�b�g�A�b�v

	// ���z�֐�
	virtual HRESULT Init();	// ������
	virtual void Uninit();	// �I��
	virtual void Info(const int nBagIdx) const;	// �A�C�e�����
	virtual void Drop(const int nBagIdx) const;	// �A�C�e���j��
	virtual std::string Detail() const;			// �A�C�e���ڍׂ̕�����擾
	virtual std::string UseEnd() const;			// �A�C�e���g�p��̕�����擾
	virtual CFrame2DModuleText::ABuffTextArray CreateUseBuffTextArray() const;	// �����g�p�e�L�X�g�o�b�t�@�A�z�z�񐶐�
	virtual CFrame2DModuleText::ABuffTextArray CreateInfoBuffTextArray() const;	// �������e�L�X�g�o�b�t�@�A�z�z�񐶐�
	virtual CFrame2DModuleText::ABuffTextArray CreateDropBuffTextArray() const;	// �����j���e�L�X�g�o�b�t�@�A�z�z�񐶐�

	// �ÓI�����o�֐�
	static CItemData* Create(const EType type);	// ����

	// �����o�֐�
	inline void SetDataPath(const std::string& rDataPath)	{ m_sDataPath = rDataPath; }	// �A�C�e�����p�X�ݒ�
	inline std::string GetDataPath() const			{ return m_sDataPath; }		// �A�C�e�����p�X�擾
	inline void SetName(const std::string& rName)	{ m_sName = rName; }		// �A�C�e�����ݒ�
	inline std::string GetName() const				{ return m_sName; }			// �A�C�e�����擾
	inline void SetAddAtk(const int nAddAtk)		{ m_nAddAtk = nAddAtk; }	// �U���͏㏸�ʐݒ�
	inline int GetAddAtk() const					{ return m_nAddAtk; }		// �U���͏㏸�ʎ擾
	inline void SetAddDef(const int nAddDef)		{ m_nAddDef = nAddDef; }	// �h��͏㏸�ʐݒ�
	inline int GetAddDef() const					{ return m_nAddDef; }		// �h��͏㏸�ʎ擾

private:
	// �����o�ϐ�
	std::string m_sDataPath;	// �A�C�e�����p�X
	std::string m_sName;		// �A�C�e����
	int m_nAddAtk;				// �U���͏㏸��
	int m_nAddDef;				// �h��͏㏸��
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
	const CItemData& GetInfo(const int nIdx);			// �A�C�e�����擾 (�C���f�b�N�X)
	const CItemData& GetInfo(const std::string& rPath);	// �A�C�e�����擾 (�p�X)

	// �ÓI�����o�֐�
	static CItem* Create();					// ����
	static void Release(CItem*& prItem);	// �j��

private:
	// �����o�֐�
	HRESULT LoadSetup();	// �Z�b�g�A�b�v
	CItemData* LoadDataSetup(const char* pDataPath);	// �A�C�e�����Z�b�g�A�b�v

	// �����o�ϐ�
	std::vector<CItemData*> m_vecItemData;	// �A�C�e�����I�z��
};

#endif	// _ITEM_H_
