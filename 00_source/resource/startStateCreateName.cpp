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
#include "namingManager.h"
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
		const float	HEIGHT	= 42.0f;	// �����c��

		const CString2D::EAlignX ALIGN_X = CString2D::XALIGN_CENTER;		// ���z�u
		const D3DXVECTOR3	POS = D3DXVECTOR3(SCREEN_CENT.x, 80.0f, 0.0f);	// �ʒu
		const D3DXVECTOR3	ROT = VEC3_ZERO;	// ����
		const D3DXCOLOR		COL = XCOL_WHITE;	// �F
	}
	
	namespace select
	{	
		const D3DXVECTOR3 POS[CStartStateCreateName::YSELECT_POLY_MAX][CStartStateCreateName::XSELECT_MAX] =	// �ʒu�z��
		{
			{ D3DXVECTOR3(180.0f, 530.0f, 0.0f), D3DXVECTOR3(440.0f, 530.0f, 0.0f), D3DXVECTOR3(750.0f, 530.0f, 0.0f) },
			{ D3DXVECTOR3(220.0f, 630.0f, 0.0f), D3DXVECTOR3(460.0f, 630.0f, 0.0f), D3DXVECTOR3(700.0f, 630.0f, 0.0f) },
		};

		const char	*FONT	= "data\\FONT\\JF�h�b�g���_�S�V�b�N14.ttf";	// �t�H���g�p�X
		const bool	ITALIC	= false;	// �C�^���b�N
		const float	HEIGHT	= 42.0f;	// �����c��

		const CString2D::EAlignX ALIGN_X = CString2D::XALIGN_CENTER;	// ���z�u
		const D3DXVECTOR3	ROT			= VEC3_ZERO;	// ����
		const D3DXCOLOR		COL_DEFAULT	= XCOL_WHITE;	// �ʏ�F
		const D3DXCOLOR		COL_CHOICE	= XCOL_YELLOW;	// �I��F
	}
}

//************************************************************
//	�q�N���X [CStartStateCreateName] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CStartStateCreateName::CStartStateCreateName() :
	m_pTitle	(nullptr),		// �^�C�g��
	m_pNaming	(nullptr),		// �����}�l�[�W���[
	m_curSelect	(GRID2_ZERO),	// ���݂̑I����
	m_oldSelect	(GRID2_ZERO)	// �O��̑I����
{
	// �����o�ϐ����N���A
	memset(&m_apSelect[0][0], 0, sizeof(m_apSelect));	// �I����
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
	memset(&m_apSelect[0][0], 0, sizeof(m_apSelect));	// �I����
	m_pTitle	= nullptr;		// �^�C�g��
	m_pNaming	= nullptr;		// �����}�l�[�W���[
	m_curSelect	= GRID2_ZERO;	// ���݂̑I����
	m_oldSelect	= GRID2_ZERO;	// �O��̑I����

	// �����}�l�[�W���[�̐���
	m_pNaming = CNamingManager::Create(this);
	if (m_pNaming == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

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
	if (m_pTitle == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	m_pTitle->SetPriority(PRIORITY);

	// �����������
	loadtext::BindString(m_pTitle, loadtext::LoadText(PASS, CStartManager::TEXT_NAMING));


	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CStartStateCreateName::Uninit(void)
{
	// �����}�l�[�W���[�̔j��
	SAFE_REF_RELEASE(m_pNaming);

	// �^�C�g���̏I��
	SAFE_UNINIT(m_pTitle);

	for (int i = 0; i < YSELECT_POLY_MAX; i++)
	{
		for (int j = 0; j < XSELECT_MAX; j++)
		{
			// �I�����̏I��
			SAFE_UNINIT(m_apSelect[i][j]);
		}
	}

	// ���g�̔j��
	delete this;
}

//============================================================
//	�X�V����
//============================================================
void CStartStateCreateName::Update(const float fDeltaTime)
{
	// �I���̍X�V
	UpdateSelect(fDeltaTime);

	// ����̍X�V
	UpdateDecide();

	// TODO�F���ؗp
	if (GET_INPUTKEY->IsTrigger(DIK_0))
	{
		m_pNaming->ChangeChar(CNamingManager::TYPECHAR_HIRAGANA);
	}
	if (GET_INPUTKEY->IsTrigger(DIK_9))
	{
		m_pNaming->ChangeChar(CNamingManager::TYPECHAR_KATAKANA);
	}
	if (GET_INPUTKEY->IsTrigger(DIK_8))
	{
		m_pNaming->ChangeChar(CNamingManager::TYPECHAR_ALPHABET);
	}
}

//============================================================
//	�I���̍X�V����
//============================================================
void CStartStateCreateName::UpdateSelect(const float fDeltaTime)
{
#if 0
	CInputKeyboard *pKey = GET_INPUTKEY;	// �L�[�{�[�h���

	// �O��̑I������ۑ�
	m_oldSelect = m_curSelect;

	// TODO�F���܂̂܂܂��ƑI�����͓������Ȃ���
	if (m_curSelect.y == YSELECT_TOP)
	{ // �I���������ɓ����Ă���ꍇ

		// �����}�l�[�W���[�̍X�V
		assert(m_pNaming != nullptr);
		m_pNaming->Update(fDeltaTime);
	}
	else
	{ // �I�����I�����ɓ����Ă���ꍇ

		// �I��������
		if (pKey->IsTrigger(DIK_LEFT))
		{
			// ���ɑI�������炷
			m_curSelect.x = (m_curSelect.x + (XSELECT_MAX - 1)) % XSELECT_MAX;
		}
		if (pKey->IsTrigger(DIK_RIGHT))
		{
			// �E�ɑI�������炷
			m_curSelect.x = (m_curSelect.x + 1) % XSELECT_MAX;
		}
		if (pKey->IsTrigger(DIK_UP))
		{
			// ��ɑI�������炷
			m_curSelect.y = (m_curSelect.y + (YSELECT_MAX - 1)) % YSELECT_MAX;
		}
		if (pKey->IsTrigger(DIK_DOWN))
		{
			// ���ɑI�������炷
			m_curSelect.y = (m_curSelect.y + 1) % YSELECT_MAX;
		}

		if (m_curSelect.y == YSELECT_TOP)
		{
			// �O��̑I��v�f�̐F�𔒐F�ɐݒ�
			m_apSelect[m_oldSelect.y - 1][m_oldSelect.x]->SetColor(select::COL_DEFAULT);
		}
		else
		{
			// �O��̑I��v�f�̐F�𔒐F�ɐݒ�
			m_apSelect[m_oldSelect.y - 1][m_oldSelect.x]->SetColor(select::COL_DEFAULT);

			// ���݂̑I��v�f�̐F�����F�ɐݒ�
			m_apSelect[m_curSelect.y - 1][m_curSelect.x]->SetColor(select::COL_CHOICE);
		}
	}
#else
	// �����}�l�[�W���[�̍X�V
	assert(m_pNaming != nullptr);
	m_pNaming->Update(fDeltaTime);
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
		// �I�����ɉ����đ����ύX
		switch (m_curSelect.y)
		{ // ���݂̍s�I�������Ƃ̏���
		case YSELECT_CENTER:	// �����ύX�s

			// �I�𒆂̕����ɕύX
			m_pNaming->ChangeChar((CNamingManager::ETypeChar)m_curSelect.x);
			break;

		case YSELECT_BOTTOM:	// �ݒ�ςݕ�������s

			switch (m_curSelect.x)
			{ // ���݂̗�I�������Ƃ̏���
			case XSELECT_LEFT:		// �~�߂�

				// �`���[�g���A����Ԃɂ���
				m_pContext->ChangeState(new CStartStateTutorial);
				break;

			case XSELECT_CENTER:	// �폜

				// �Ō�����ꕶ���폜
				//m_pNaming->DeleteBackName();	// TODO
				break;

			case XSELECT_RIGHT:		// �m��

				// ���O�����Ԃɂ���
				//m_pContext->ChangeState(new CStartStateDecideName(m_pNaming->GetName()));	// TODO
				break;

			default:
				assert(false);
				break;
			}
			break;

		default:
			assert(false);
			break;
		}
	}
#endif
}
