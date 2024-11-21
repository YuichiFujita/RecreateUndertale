//============================================================
//
//	�A�C�e�����j���[�w�b�_�[ [selectItemUI.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _SELECT_ITEM_UI_H_
#define _SELECT_ITEM_UI_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "menuSelectUI.h"
#include "frameText2D.h"

//************************************************************
//	�O���錾
//************************************************************
class CString2D;	// ������2D�N���X
class CItemUI;		// �A�C�e��UI�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �A�C�e�����j���[�N���X
class CSelectItemUI : public CSelectUI
{
public:
	// �I���
	enum ESelect
	{
		SELECT_USE = 0,	// �g�p
		SELECT_INFO,	// ���
		SELECT_DROP,	// �j��
		SELECT_MAX		// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CSelectItemUI(AFuncUninit funcUninit, CObject2D *pSoul);

	// �f�X�g���N�^
	~CSelectItemUI() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader* pShader = nullptr) override;	// �`��
	void SetEnableDraw(const bool bDraw) override;	// �`��󋵐ݒ�
	bool IsCreateOK() override;	// ���j���[�����\�t���O�擾

private:
	// ��ԗ�
	enum EState
	{
		STATE_ITEM = 0,	// �A�C�e���I�����
		STATE_ACT,		// �s���I�����
		STATE_TEXT,		// �e�L�X�g�\�����
		STATE_MAX		// ���̗񋓌^�̑���
	};

	// �\���e�L�X�g��
	enum EText
	{
		TEXT_USE = 0,	// USE
		TEXT_INFO,		// INFO
		TEXT_DROP,		// DROP
		TEXT_MAX		// ���̗񋓌^�̑���
	};

	// �A�C�e���\����
	struct SItem
	{
		// �f�t�H���g�R���X�g���N�^
		SItem() :
			pName	 (nullptr),	// �A�C�e�������
			nItemIdx (0)		// �A�C�e���C���f�b�N�X
		{}

		// �f�X�g���N�^
		~SItem() {}

		// �����o�ϐ�
		CString2D* pName;	// �A�C�e�������
		int nItemIdx;		// �A�C�e���C���f�b�N�X
	};

	// �����o�֐�
	void UpdateSelectItem();	// �A�C�e���I���X�V
	void UpdateDecideItem();	// �A�C�e������X�V
	void UpdateSelectAct();		// �s���I���X�V
	void UpdateDecideAct();		// �s������X�V

	// �����o�ϐ�
	std::vector<SItem> m_vecItemName;	// �A�C�e�����
	CString2D* m_apSelect[SELECT_MAX];	// �I�����
	CItemUI* m_pItemMenu;	// �A�C�e�����j���[���
	EState m_state;			// ���
	int m_nCurSelectItem;	// ���݂̑I���A�C�e��
	int m_nCurSelectAct;	// ���݂̑I���s��
};

// �A�C�e��UI�N���X
class CItemUI : public CObject
{
public:
	// �R���X�g���N�^
	explicit CItemUI(const int nChoiceItemIdx, const int nChoiceBagIdx);

	// �f�X�g���N�^
	~CItemUI() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader* pShader = nullptr) override;	// �`��

	// �ÓI�����o�֐�
	static CItemUI* Create	// ����
	( // ����
		const CSelectItemUI::ESelect choiceAct,	// �I�𒆍s��
		const int nChoiceItemIdx,				// �I�𒆃A�C�e���C���f�b�N�X
		const int nChoiceBagIdx					// �I�𒆃o�b�O�C���f�b�N�X
	);

	// �����o�֐�
	inline HRESULT PushFrontString(const std::string& rStr)		{ return m_pTextBox->PushFrontString(rStr); }	// ������̐擪�ǉ� (�}���`�o�C�g������)
	inline HRESULT PushFrontString(const std::wstring& rStr)	{ return m_pTextBox->PushFrontString(rStr); }	// ������̐擪�ǉ� (���C�h������)
	inline HRESULT PushBackString(const std::string& rStr)		{ return m_pTextBox->PushBackString(rStr); }	// ������̍Ō���ǉ� (�}���`�o�C�g������)
	inline HRESULT PushBackString(const std::wstring& rStr)		{ return m_pTextBox->PushBackString(rStr); }	// ������̍Ō���ǉ� (���C�h������)
	inline void DeleteString(const int nStrIdx)			{ m_pTextBox->DeleteString(nStrIdx); }		// ������폜
	inline void DeleteStringAll()						{ m_pTextBox->DeleteStringAll(); }			// ������S�폜
	inline void ChangeTextBox(const AText& rText)		{ m_pTextBox->ChangeText(rText); }			// �e�L�X�g�ύX
	inline void SetTextBoxEnableDraw(const bool bDraw)	{ m_pTextBox->SetTextEnableDraw(bDraw); };	// �`��󋵐ݒ�
	inline bool IsTextBoxScroll() const	{ return m_pTextBox->IsTextScroll(); }	// ��������󋵎擾
	inline int GetChoiceItemIdx() const	{ return m_nChoiceItemIdx; }			// �I�𒆃A�C�e���C���f�b�N�X�擾
	inline int GetChoiceBagIdx() const	{ return m_nChoiceBagIdx; }				// �I�𒆃o�b�O�C���f�b�N�X�擾
	inline int GetCurTextIdx() const	{ return m_nCurTextIdx; }				// ���݂̃e�L�X�g�C���f�b�N�X�擾

protected:
	// �������z�֐�
	virtual inline void NextText() = 0 { m_nCurTextIdx++; }	// �e�L�X�g�{�b�N�X�i�s

private:
	// �I�[�o�[���C�h�֐�
	inline void Release() override { CObject::Release(); }	// �j��

	// �����o�ϐ�
	const int m_nChoiceItemIdx;	// �I�𒆃A�C�e���C���f�b�N�X
	const int m_nChoiceBagIdx;	// �I�𒆃o�b�O�C���f�b�N�X
	CFrameText2D* m_pTextBox;	// �e�L�X�g�{�b�N�X���
	int m_nCurTextIdx;			// ���݂̃e�L�X�g�C���f�b�N�X
};

#endif	// _SELECT_ITEM_UI_H_
