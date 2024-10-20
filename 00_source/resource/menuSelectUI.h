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
class CSelectUI;	// �Z���N�gUI�N���X

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
	void Draw(CShader* pShader = nullptr) override;	// �`��

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
	CFrame2D *m_pFrame;			// �t���[�����
	CObject2D *m_pSoul;			// �\�E���J�[�\�����
	CSelectUI *m_pSelectMenu;	// �I�����j���[���
	int m_nCurSelect;			// ���݂̑I����
};

// �Z���N�gUI�N���X
class CSelectUI : public CObject
{
public:
	// �G�C���A�X��`
	using AFuncUninit = const std::function<void(void)>;	// �I�����j���[�I���֐��̃|�C���^�^

	// �R���X�g���N�^
	CSelectUI(AFuncUninit funcUninit, CObject2D *pSoul);

	// �f�X�g���N�^
	~CSelectUI() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader* pShader = nullptr) override;	// �`��
	void SetEnableDraw(const bool bDraw) override;	// �`��󋵐ݒ�

	// �ÓI�����o�֐�
	static CSelectUI *Create	// ����
	( // ����
		AFuncUninit funcUninit,	// �I�����j���[�I���֐�
		CObject2D *pSoul,		// �\�E���J�[�\�����
		const CMenuSelectUI::ESelect select	// �I����
	);

	// �����o�֐�
	void SetFramePosition(const VECTOR3& rPos)	{ m_pFrame->SetVec3Position(rPos); }	// �t���[���ʒu�ݒ�
	void SetFrameRotation(const VECTOR3& rRot)	{ m_pFrame->SetVec3Rotation(rRot); }	// �t���[�������ݒ�
	void SetFrameSize(const VECTOR3& rSize)		{ m_pFrame->SetVec3Size(rSize); }		// �t���[���傫���ݒ�
	void SetSoulPosition(const VECTOR3& rPos)	{ m_pSoul->SetVec3Position(rPos); }		// �\�E���J�[�\���ʒu�ݒ�
	void SetSoulCursorDraw(const bool bDraw)	{ m_pSoul->SetEnableDraw(bDraw); }		// �\�E���J�[�\���`��󋵐ݒ�
	VECTOR3 GetFramePosition(void) const		{ return m_pFrame->GetVec3Position(); }	// �t���[���ʒu�擾
	VECTOR3 GetFrameRotation(void) const		{ return m_pFrame->GetVec3Rotation(); }	// �t���[�������擾
	VECTOR3 GetFrameSize(void) const			{ return m_pFrame->GetVec3Size(); }		// �t���[���傫���擾
	VECTOR3 GetSoulPosition(void) const			{ return m_pSoul->GetVec3Position(); }	// �\�E���J�[�\���ʒu�擾
	bool IsSoulCursorDraw(void) const			{ return m_pSoul->IsDraw(); }			// �\�E���J�[�\���`��󋵎擾

private:
	// �I�[�o�[���C�h�֐�
	void Release(void) override { CObject::Release(); }	// �j��

	// �����o�ϐ�
	AFuncUninit m_funcUninitMenu;	// �I�����j���[�I���֐��|�C���^
	CObject2D *m_pSoul;	// �\�E���J�[�\�����
	CFrame2D *m_pFrame;	// �t���[�����
};

#endif	// _MENU_SELECT_UI_H_
