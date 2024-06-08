//============================================================
//
//	������ԏ��� [startStateCreateName.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "startStateCreateName.h"
#include "startManager.h"
#include "manager.h"
#include "string2D.h"
#include "loadtext.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const char *PASS = "data\\TEXT\\start.txt";	// �e�L�X�g�p�X
	const int PRIORITY = 6;	// �D�揇��

	namespace title
	{	
		const char	*FONT	= "data\\FONT\\JF�h�b�g���_�S�V�b�N14.ttf";	// �t�H���g�p�X
		const bool	ITALIC	= false;	// �C�^���b�N
		const float	HEIGHT	= 90.0f;	// �����c��

		const CString2D::EAlignX ALIGN_X = CString2D::XALIGN_CENTER;		// ���z�u
		const D3DXVECTOR3	POS = D3DXVECTOR3(SCREEN_CENT.x, 70.0f, 0.0f);	// �ʒu
		const D3DXVECTOR3	ROT = VEC3_ZERO;	// ����
		const D3DXCOLOR		COL = XCOL_WHITE;	// �F
	}
}

//************************************************************
//	�q�N���X [CStartStateCreateName] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CStartStateCreateName::CStartStateCreateName() :
	m_pTitle		(nullptr),	// �^�C�g��
	m_nCurSelect	(0),		// ���݂̑I����
	m_nOldSelect	(0)			// �O��̑I����
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CStartStateCreateName::~CStartStateCreateName()
{

}

//============================================================
//	����������
//============================================================
HRESULT CStartStateCreateName::Init(void)
{
	// �����o�ϐ���������
	m_pTitle		= nullptr;	// �^�C�g��
	m_nCurSelect	= 0;		// ���݂̑I����
	m_nOldSelect	= 0;		// �O��̑I����

	// �^�C�g���̐���
	m_pTitle = CString2D::Create
	( // ����
		title::FONT,	// �t�H���g�p�X
		title::ITALIC,	// �C�^���b�N
		L"",			// �w�蕶����
		title::POS,		// ���_�ʒu
		title::HEIGHT,	// �����c��
		title::ALIGN_X,	// ���z�u
		title::ROT,		// ���_����
		title::COL		// �F
	);

	// �D�揇�ʂ�ݒ�
	m_pTitle->SetPriority(PRIORITY);

	// �����������
	loadtext::BindString(m_pTitle, loadtext::LoadText(PASS, CStartManager::TEXT_OPTION_TITLE));

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CStartStateCreateName::Uninit(void)
{
	// �^�C�g���̏I��
	SAFE_UNINIT(m_pTitle);

	// ���g�̔j��
	delete this;
}

//============================================================
//	�X�V����
//============================================================
void CStartStateCreateName::Update(const float fDeltaTime)
{
	// �I���̍X�V
	UpdateSelect();

	// ����̍X�V
	UpdateDecide();
}

//============================================================
//	�I���̍X�V����
//============================================================
void CStartStateCreateName::UpdateSelect(void)
{
#if 0
	CInputKeyboard *pKey = GET_INPUTKEY;	// �L�[�{�[�h���

	// �O��̑I������ۑ�
	m_nOldSelect = m_nCurSelect;

	// �I��������
	if (pKey->IsTrigger(DIK_DOWN))
	{
		// ��ɑI�������炷
		m_nCurSelect = (m_nCurSelect + (SELECT_MAX - 1)) % SELECT_MAX;
	}
	if (pKey->IsTrigger(DIK_UP))
	{
		// ���ɑI�������炷
		m_nCurSelect = (m_nCurSelect + 1) % SELECT_MAX;
	}

	// �O��̑I��v�f�̐F�𔒐F�ɐݒ�
	m_apSelect[m_nOldSelect]->SetColor(select::COL_DEFAULT);

	// ���݂̑I��v�f�̐F�����F�ɐݒ�
	m_apSelect[m_nCurSelect]->SetColor(select::COL_CHOICE);
#endif
}

//============================================================
//	����̍X�V����
//============================================================
void CStartStateCreateName::UpdateDecide(void)
{
#if 0
	CInputKeyboard *pKey = GET_INPUTKEY;	// �L�[�{�[�h���
	if (pKey->IsTrigger(DIK_Z) || pKey->IsTrigger(DIK_RETURN))
	{
		// �I�����ɉ����đJ�ڐ��ύX
		switch (m_nCurSelect)
		{ // ���݂̑I�������Ƃ̏���
		case SELECT_CLOSE:
			m_pContext->ChangeState(new CStartStateTutorial);	// �`���[�g���A�����
			break;

		default:
			assert(false);
			break;
		}
	}
#endif
}
