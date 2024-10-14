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
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader *pShader = nullptr) override;	// �`��
	void SetEnableDraw(const bool bDraw) override;	// �`��󋵐ݒ�

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
		CString2D *m_pName;	// �A�C�e�������
		int nItemID;		// �A�C�e���C���f�b�N�X
	};

	// �����o�֐�
	void UpdateSelectItem(void);	// �A�C�e���I���X�V
	void UpdateDecideItem(void);	// �A�C�e������X�V
	void UpdateSelectAct(void);		// �s���I���X�V
	void UpdateDecideAct(void);		// �s������X�V

	// �����o�ϐ�
	std::vector<SItem> m_vecItemName;	// �A�C�e�����
	CString2D *m_apSelect[SELECT_MAX];	// �I�����
	CItemUI *m_pItemMenu;	// �A�C�e�����j���[���
	EState m_state;			// ���
	int m_nCurSelectItem;	// ���݂̑I���A�C�e��
	int m_nCurSelectAct;	// ���݂̑I���s��
};

// �A�C�e��UI�N���X
class CItemUI : public CObject
{
public:
	// �R���X�g���N�^
	explicit CItemUI(const int nChoiceItemIdx);

	// �f�X�g���N�^
	~CItemUI() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader *pShader = nullptr) override;	// �`��

	// �ÓI�����o�֐�
	static CItemUI *Create	// ����
	( // ����
		const CSelectItemUI::ESelect choiceAct,	// �I�𒆍s��
		const int nChoiceItemIdx				// �I�𒆃A�C�e���C���f�b�N�X
	);

	// �����o�֐�
	HRESULT PushFrontString(const std::string& rStr)	{ return m_pTextBox->PushFrontString(rStr); }	// ������̐擪�ǉ� (�}���`�o�C�g������)
	HRESULT PushFrontString(const std::wstring& rStr)	{ return m_pTextBox->PushFrontString(rStr); }	// ������̐擪�ǉ� (���C�h������)
	HRESULT PushBackString(const std::string& rStr)		{ return m_pTextBox->PushBackString(rStr); }	// ������̍Ō���ǉ� (�}���`�o�C�g������)
	HRESULT PushBackString(const std::wstring& rStr)	{ return m_pTextBox->PushBackString(rStr); }	// ������̍Ō���ǉ� (���C�h������)
	void DeleteString(const int nStrID)			{ m_pTextBox->DeleteString(nStrID); }		// ������폜
	void DeleteStringAll(void)					{ m_pTextBox->DeleteStringAll(); }			// ������S�폜
	void ChangeTextBox(const AText& rText)		{ m_pTextBox->ChangeText(rText); }			// �e�L�X�g�ύX
	void SetTextBoxEnableDraw(const bool bDraw)	{ m_pTextBox->SetTextEnableDraw(bDraw); };	// �`��󋵐ݒ�
	bool IsTextBoxScroll(void) const	{ return m_pTextBox->IsTextScroll(); }	// ��������󋵎擾
	int GetChoiceItemIdx(void) const	{ return m_nChoiceItemIdx; }			// �I�𒆃A�C�e���C���f�b�N�X�擾
	int GetCurTextIdx(void) const		{ return m_nCurTextIdx; }				// ���݂̃e�L�X�g�C���f�b�N�X�擾

protected:
	// �������z�֐�
	virtual void NextText(void) = 0 { m_nCurTextIdx++; }	// �e�L�X�g�{�b�N�X�i�s

private:
	// �I�[�o�[���C�h�֐�
	void Release(void) override { CObject::Release(); }	// �j��

	// �����o�ϐ�
	const int m_nChoiceItemIdx;	// �I�𒆃A�C�e���C���f�b�N�X
	CFrameText2D *m_pTextBox;	// �e�L�X�g�{�b�N�X���
	int m_nCurTextIdx;			// ���݂̃e�L�X�g�C���f�b�N�X
};

#endif	// _SELECT_ITEM_UI_H_
