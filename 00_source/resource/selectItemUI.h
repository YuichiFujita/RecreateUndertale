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

//************************************************************
//	�N���X��`
//************************************************************
// �A�C�e�����j���[�N���X
class CSelectItemUI : public CSelect
{
public:
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
	// �I���
	enum ESelect
	{
		SELECT_USE = 0,	// �g�p
		SELECT_INFO,	// ���
		SELECT_DROP,	// �j��
		SELECT_MAX		// ���̗񋓌^�̑���
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
	void UpdateSelect(void);		// �I���X�V
	void UpdateDecide(void);		// ����X�V

	// �����o�ϐ�
	std::vector<SItem> m_vecItemName;	// �A�C�e�����
	CString2D *m_apSelect[SELECT_MAX];	// �I�����
	CFrameText2D *m_pTextBox;			// �e�L�X�g�{�b�N�X���
	SItem *m_pSelectItem;	// �I�𒆃A�C�e�����		// TODO�F�A�C�e���I�𒆂��̓C���f�b�N�X�ł̊Ǘ��ɂ��悤
	int m_nCurTextIdx;		// ���݂̃e�L�X�g�C���f�b�N�X
	int m_nCurSelectItem;	// ���݂̑I���A�C�e��
	int m_nCurSelect;		// ���݂̑I����
};

#endif	// _SELECT_ITEM_UI_H_
