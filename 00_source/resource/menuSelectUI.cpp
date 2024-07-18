//============================================================
//
//	�Z���N�g���j���[���� [menuSelectUI.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "menuSelectUI.h"
#include "menuUI.h"
#include "manager.h"
#include "string2D.h"
#include "loadtext.h"
#include "selectItemUI.h"
#include "selectStatusUI.h"
#include "selectPhoneUI.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const int PRIORITY = 6;	// �Z���N�g���j���[�̗D�揇��

	namespace frame
	{
		const D3DXVECTOR3 POS	= D3DXVECTOR3(155.0f, 362.5f, 0.0f);	// �t���[���ʒu
		const D3DXVECTOR3 ROT	= VEC3_ZERO;							// �t���[������
		const D3DXVECTOR3 SIZE	= D3DXVECTOR3(200.0f, 205.0f, 0.0f);	// �t���[���傫��
	}

	namespace select
	{
		const char	*FONT		= "data\\FONT\\JF�h�b�g���_�S�V�b�N14.ttf";	// �t�H���g�p�X
		const char	*PASS		= "data\\TEXT\\menu.txt";	// �e�L�X�g�p�X
		const bool	ITALIC		= false;	// �C�^���b�N
		const float	CHAR_HEIGHT	= 43.0f;	// �����c��
		const float	LINE_HEIGHT	= 53.0f;	// �s�ԏc��

		const CString2D::EAlignX ALIGN_X = CString2D::XALIGN_LEFT;	// ���z�u
		const D3DXVECTOR3 POS = D3DXVECTOR3(125.0f, 308.5f, 0.0f);	// �ʒu
		const D3DXVECTOR3 ROT = VEC3_ZERO;			// ����
		const D3DXCOLOR COL_DEFAULT	= XCOL_WHITE;	// �ʏ�F
		const D3DXCOLOR COL_CHOICE	= XCOL_YELLOW;	// �I��F
	}

	namespace soul
	{
		const D3DXVECTOR3 POS	= D3DXVECTOR3(97.5f, 308.5f, 0.0f);	// �\�E���J�[�\���ʒu
		const D3DXVECTOR3 SIZE	= D3DXVECTOR3(26.5f, 26.5f, 0.0f);	// �\�E���J�[�\���傫��
	}
}

//************************************************************
//	�q�N���X [CMenuSelectUI] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CMenuSelectUI::CMenuSelectUI() : CObject(CObject::LABEL_UI, CObject::DIM_3D, PRIORITY),
	m_pFrame		(nullptr),	// �t���[�����
	m_pSoul			(nullptr),	// �\�E���J�[�\�����
	m_pSelectMenu	(nullptr),	// �I�����j���[���
	m_nCurSelect	(0)			// ���݂̑I����
{
	// �����o�ϐ����N���A
	memset(&m_apSelect[0], 0, sizeof(m_apSelect));	// �I�������
}

//============================================================
//	�f�X�g���N�^
//============================================================
CMenuSelectUI::~CMenuSelectUI()
{

}

//============================================================
//	����������
//============================================================
HRESULT CMenuSelectUI::Init(void)
{
	// �����o�ϐ���������
	memset(&m_apSelect[0], 0, sizeof(m_apSelect));	// �I�������
	m_pFrame		= nullptr;	// �t���[�����
	m_pSoul			= nullptr;	// �\�E���J�[�\�����
	m_pSelectMenu	= nullptr;	// �I�����j���[���
	m_nCurSelect	= 0;		// ���݂̑I����

	// �t���[���̐���
	m_pFrame = CFrame2D::Create
	( // ����
		frame::POS,	// �ʒu
		frame::ROT,	// ����
		frame::SIZE	// �傫��
	);
	if (m_pFrame == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	m_pFrame->SetPriority(PRIORITY);

	for (int i = 0; i < SELECT_MAX; i++)
	{ // �I�����̍��ڐ����J��Ԃ�

		// �����ʒu�I�t�Z�b�g
		D3DXVECTOR3 offset = D3DXVECTOR3(0.0f, select::LINE_HEIGHT * i, 0.0f);

		// �I�����̐���
		m_apSelect[i] = CString2D::Create
		( // ����
			select::FONT,			// �t�H���g�p�X
			select::ITALIC,			// �C�^���b�N
			L"",					// �w�蕶����
			select::POS + offset,	// ���_�ʒu
			select::CHAR_HEIGHT,	// �����c��
			select::ALIGN_X,		// ���z�u
			select::ROT,			// ���_����
			select::COL_DEFAULT		// �F
		);
		if (m_apSelect[i] == nullptr)
		{ // �����Ɏ��s�����ꍇ

			// ���s��Ԃ�
			assert(false);
			return E_FAIL;
		}

		// �D�揇�ʂ�ݒ�
		m_apSelect[i]->SetPriority(PRIORITY);

		// �����������
		loadtext::BindString(m_apSelect[i], loadtext::LoadText(select::PASS, CMenuUI::TEXT_ITEM + i));
	}

	// �\�E���J�[�\���̐���
	m_pSoul = CObject2D::Create
	( // ����
		soul::POS,	// �ʒu
		soul::SIZE	// �傫��
	);
	if (m_pSoul == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �\�E���e�N�X�`��������
	m_pSoul->BindTexture("data\\TEXTURE\\spr_heartsmall.png");	// TODO�F�p�X

	// ���x����ݒ�
	m_pSoul->SetLabel(CObject::LABEL_UI);

	// �D�揇�ʂ�ݒ�
	m_pSoul->SetPriority(PRIORITY);

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CMenuSelectUI::Uninit(void)
{
	// �t���[���̏I��
	SAFE_UNINIT(m_pFrame);

	for (int i = 0; i < SELECT_MAX; i++)
	{ // �I�����̍��ڐ����J��Ԃ�

		// �I�����̏I��
		SAFE_UNINIT(m_apSelect[i]);
	}

	// �\�E���J�[�\���̏I��
	SAFE_UNINIT(m_pSoul);

	// �I�u�W�F�N�g��j��
	Release();
}

//============================================================
//	�X�V����
//============================================================
void CMenuSelectUI::Update(const float fDeltaTime)
{
	if (m_pSelectMenu == nullptr)
	{ // ���j���[��I�����Ă��Ȃ��ꍇ

		// �I���̍X�V
		UpdateSelect();

		// ����̍X�V
		UpdateDecide();
	}
}

//============================================================
//	�`�揈��
//============================================================
void CMenuSelectUI::Draw(CShader * /*pShader*/)
{

}

//============================================================
//	��������
//============================================================
CMenuSelectUI *CMenuSelectUI::Create(void)
{
	// �Z���N�g���j���[�̐���
	CMenuSelectUI *pMenuSelectUI = new CMenuSelectUI;
	if (pMenuSelectUI == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �Z���N�g���j���[�̏�����
		if (FAILED(pMenuSelectUI->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �Z���N�g���j���[�̔j��
			SAFE_DELETE(pMenuSelectUI);
			return nullptr;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return pMenuSelectUI;
	}
}

//============================================================
//	�I���̍X�V����
//============================================================
void CMenuSelectUI::UpdateSelect(void)
{
	// �I��������
	CInputKeyboard *pKey = GET_INPUTKEY;	// �L�[�{�[�h���
	if (pKey->IsTrigger(DIK_DOWN))
	{
		// ��ɑI�������炷
		m_nCurSelect = (m_nCurSelect + 1) % SELECT_MAX;
	}
	if (pKey->IsTrigger(DIK_UP))
	{
		// ���ɑI�������炷
		m_nCurSelect = (m_nCurSelect + (SELECT_MAX - 1)) % SELECT_MAX;
	}

	// �����ʒu�I�t�Z�b�g���v�Z
	D3DXVECTOR3 offset = D3DXVECTOR3(0.0f, select::LINE_HEIGHT * m_nCurSelect, 0.0f);

	// �\�E���J�[�\���̈ʒu���ړ�
	m_pSoul->SetVec3Position(soul::POS + offset);
}

//============================================================
//	����̍X�V����
//============================================================
void CMenuSelectUI::UpdateDecide(void)
{
	CInputKeyboard *pKey = GET_INPUTKEY;	// �L�[�{�[�h���
	if (pKey->IsTrigger(DIK_Z) || pKey->IsTrigger(DIK_RETURN))
	{
		// ���ݑI�𒆂̃��j���[�ɕύX
		ChangeSelectMenu((ESelect)m_nCurSelect);
	}
}

//============================================================
//	�I�����j���[�̏I������
//============================================================
void CMenuSelectUI::UninitSelectMenu(void)
{
	// �I�����j���[�̏I��
	SAFE_UNINIT(m_pSelectMenu);
}

//============================================================
//	�I�����j���[�̕ύX����
//============================================================
HRESULT CMenuSelectUI::ChangeSelectMenu(const CMenuSelectUI::ESelect select)
{
	// �I�����j���[�̏I��
	SAFE_UNINIT(m_pSelectMenu);

	// �I�����ɉ����ă��j���[�𐶐�
	assert(m_pSelectMenu == nullptr);
	m_pSelectMenu = CSelect::Create
	( // ����
		std::bind(&CMenuSelectUI::UninitSelectMenu, this),	// �I�����j���[�I���֐�
		m_pSoul,	// �\�E���J�[�\�����
		select		// �I����
	);
	if (m_pSelectMenu == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//************************************************************
//	�q�N���X [CSelect] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CSelect::CSelect(AFuncUninit funcUninit, CObject2D *pSoul) : CObject(CObject::LABEL_UI, CObject::DIM_3D, PRIORITY),
	m_funcUninitMenu (funcUninit),	// �I�����j���[�I���֐��|�C���^
	m_pSoul			 (pSoul),		// �\�E���J�[�\�����
	m_pFrame		 (nullptr)		// �t���[�����
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CSelect::~CSelect()
{

}

//============================================================
//	����������
//============================================================
HRESULT CSelect::Init(void)
{
	// �����o�ϐ���������
	m_pFrame = nullptr;	// �t���[�����

	// �t���[���̐���
	m_pFrame = CFrame2D::Create
	( // ����
		VEC3_ZERO,	// �ʒu
		VEC3_ZERO,	// ����
		VEC3_ZERO	// �傫��
	);
	if (m_pFrame == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	m_pFrame->SetPriority(PRIORITY);

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CSelect::Uninit(void)
{
	// �t���[���̏I��
	SAFE_UNINIT(m_pFrame);

	// �I�u�W�F�N�g��j��
	Release();
}

//============================================================
//	�X�V����
//============================================================
void CSelect::Update(const float fDeltaTime)
{
	CInputKeyboard *pKey = GET_INPUTKEY;	// �L�[�{�[�h���
	if (pKey->IsTrigger(DIK_X) || pKey->IsTrigger(DIK_LSHIFT) || pKey->IsTrigger(DIK_RSHIFT))
	{
		// �I�����j���[�̏I��
		m_funcUninitMenu();
	}
}

//============================================================
//	�`�揈��
//============================================================
void CSelect::Draw(CShader * /*pShader*/)
{

}

//============================================================
//	��������
//============================================================
CSelect *CSelect::Create
(
	AFuncUninit funcUninit,	// �I�����j���[�I���֐�
	CObject2D *pSoul,		// �\�E���J�[�\�����
	const CMenuSelectUI::ESelect select	// �I����
)
{
	// �Z���N�g�̐���
	CSelect *pSelect = nullptr;	// �Z���N�g���
	switch (select)
	{ // �I�������Ƃ̏���
	case CMenuSelectUI::SELECT_ITEM:
		pSelect = new CSelectItemUI(funcUninit, pSoul);
		break;

	case CMenuSelectUI::SELECT_STATUS:
		pSelect = new CSelectStatusUI(funcUninit, pSoul);
		break;

	case CMenuSelectUI::SELECT_PHONE:
		pSelect = new CSelectPhoneUI(funcUninit, pSoul);
		break;

	default:	// ��O����
		assert(false);
		break;
	}

	if (pSelect == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �Z���N�g�̏�����
		if (FAILED(pSelect->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �Z���N�g�̔j��
			SAFE_DELETE(pSelect);
			return nullptr;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return pSelect;
	}
}
