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

//************************************************************
//	�O���錾
//************************************************************
class CFrameText2D;	// �t���[���e�L�X�g2D�N���X
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
	CItemUI
	( // ����
		CSelectUI::AFuncUninit funcUninit,		// �I�����j���[�I���֐�
		const ATextBox& rText,					// �\���e�L�X�g
		const CSelectItemUI::ESelect choiceAct,	// �I�𒆍s��
		const int nChoiceItemIdx				// �I�𒆃A�C�e���C���f�b�N�X
	);

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
		CSelectUI::AFuncUninit funcUninit,		// �I�����j���[�I���֐�
		const ATextBox& rText,					// �\���e�L�X�g
		const CSelectItemUI::ESelect choiceAct,	// �I�𒆍s��
		const int nChoiceItemIdx				// �I�𒆃A�C�e���C���f�b�N�X
	);

private:
	// �I�[�o�[���C�h�֐�
	void Release(void) override { CObject::Release(); }	// �j��

	// �����o�ϐ�
	CSelectUI::AFuncUninit m_funcUninitMenu;	// �I�����j���[�I���֐��|�C���^
	const ATextBox& m_text;						// �\���e�L�X�g
	const CSelectItemUI::ESelect m_choiceAct;	// �I�𒆍s��
	const int m_nChoiceItemIdx;					// �I�𒆃A�C�e���C���f�b�N�X
	CFrameText2D *m_pTextBox;	// �e�L�X�g�{�b�N�X���
	int m_nCurTextIdx;			// ���݂̃e�L�X�g�C���f�b�N�X
};

#endif	// _SELECT_ITEM_UI_H_
