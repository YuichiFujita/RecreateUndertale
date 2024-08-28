//============================================================
//
//	�Z���N�g���j���[�w�b�_�[ [menuSelectUI.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _MENU_SELECT_UI_H_
#define _MENU_SELECT_UI_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object.h"
#include "object2D.h"
#include "frame2D.h"

//************************************************************
//	�O���錾
//************************************************************
class CString2D;	// ������2D�N���X
class CSelect;		// �Z���N�g�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �Z���N�g���j���[�N���X
class CMenuSelectUI : public CObject
{
public:
	// �I���
	enum ESelect
	{
		SELECT_ITEM = 0,	// �A�C�e��
		SELECT_STATUS,		// �X�e�[�^�X
		SELECT_PHONE,		// �d�b
		SELECT_MAX			// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CMenuSelectUI();

	// �f�X�g���N�^
	~CMenuSelectUI() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader *pShader = nullptr) override;	// �`��

	// �ÓI�����o�֐�
	static CMenuSelectUI *Create(void);	// ����

	// �����o�֐�
	bool IsChoiceSelect(void) const { return (m_pSelectMenu != nullptr); }	// �I�𒆏󋵎擾

private:
	// �I�[�o�[���C�h�֐�
	void Release(void) override { CObject::Release(); }	// �j��

	// �����o�֐�
	void UpdateSelect(void);		// �I���X�V
	void UpdateDecide(void);		// ����X�V
	void UninitSelectMenu(void);	// �I�����j���[�I��
	HRESULT ChangeSelectMenu(const CMenuSelectUI::ESelect select);	// �I�����j���[�ύX

	// �����o�ϐ�
	CString2D *m_apSelect[SELECT_MAX];	// �I�������
	CFrame2D *m_pFrame;		// �t���[�����
	CObject2D *m_pSoul;		// �\�E���J�[�\�����
	CSelect *m_pSelectMenu;	// �I�����j���[���
	int m_nCurSelect;		// ���݂̑I����
};

// �Z���N�g�N���X
class CSelect : public CObject
{
public:
	// �G�C���A�X��`
	using AFuncUninit = const std::function<void(void)>;	// �I�����j���[�I���֐��̃|�C���^�^

	// �R���X�g���N�^
	CSelect(AFuncUninit funcUninit, CObject2D *pSoul);

	// �f�X�g���N�^
	~CSelect() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader *pShader = nullptr) override;	// �`��

	// �ÓI�����o�֐�
	static CSelect *Create	// ����
	( // ����
		AFuncUninit funcUninit,	// �I�����j���[�I���֐�
		CObject2D *pSoul,		// �\�E���J�[�\�����
		const CMenuSelectUI::ESelect select	// �I����
	);

	// �����o�֐�
	void SetFramePosition(const D3DXVECTOR3& rPos)	{ m_pFrame->SetVec3Position(rPos); }	// �t���[���ʒu�ݒ�
	void SetFrameRotation(const D3DXVECTOR3& rRot)	{ m_pFrame->SetVec3Rotation(rRot); }	// �t���[�������ݒ�
	void SetFrameSizing(const D3DXVECTOR3& rSize)	{ m_pFrame->SetVec3Sizing(rSize); }		// �t���[���傫���ݒ�
	void SetSoulPosition(const D3DXVECTOR3& rPos)	{ m_pSoul->SetVec3Position(rPos); }		// �\�E���J�[�\���ʒu�ݒ�
	void SetSoulCursorDraw(const bool bDraw)		{ m_pSoul->SetEnableDraw(bDraw); }		// �\�E���J�[�\���`��󋵐ݒ�
	D3DXVECTOR3 GetFramePosition(void) const		{ return m_pFrame->GetVec3Position(); }	// �t���[���ʒu�擾
	D3DXVECTOR3 GetFrameRotation(void) const		{ return m_pFrame->GetVec3Rotation(); }	// �t���[�������擾
	D3DXVECTOR3 GetFrameSizing(void) const			{ return m_pFrame->GetVec3Sizing(); }	// �t���[���傫���擾
	D3DXVECTOR3 GetSoulPosition(void) const			{ return m_pSoul->GetVec3Position(); }	// �\�E���J�[�\���ʒu�擾
	bool IsSoulCursorDraw(void) const				{ return m_pSoul->IsDraw(); }			// �\�E���J�[�\���`��󋵎擾

private:
	// �I�[�o�[���C�h�֐�
	void Release(void) override { CObject::Release(); }	// �j��

	// �����o�ϐ�
	AFuncUninit m_funcUninitMenu;	// �I�����j���[�I���֐��|�C���^
	CObject2D *m_pSoul;	// �\�E���J�[�\�����
	CFrame2D *m_pFrame;	// �t���[�����
};

#endif	// _MENU_SELECT_UI_H_
