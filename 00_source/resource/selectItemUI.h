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

#endif	// _SELECT_ITEM_UI_H_
