//============================================================
//
//	�`���[�g���A����ԏ��� [startStateTutorial.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "startStateTutorial.h"
#include "startManager.h"
#include "manager.h"
#include "sound.h"
#include "string2D.h"
#include "text2D.h"
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

		const EAlignX		ALIGN_X = XALIGN_CENTER;	// ���z�u
		const D3DXVECTOR3	POS = D3DXVECTOR3(SCREEN_CENT.x, 65.0f, 0.0f);	// �ʒu
		const D3DXVECTOR3	ROT = VEC3_ZERO;								// ����
		const COLOR			COL = COLOR(0.75f, 0.75f, 0.75f, 1.0f);			// �F
	}

	namespace control
	{
		const char *FONT = "data\\FONT\\JF�h�b�g���_�S�V�b�N14.ttf";	// �t�H���g�p�X
		const bool	ITALIC		= false;	// �C�^���b�N
		const float	CHAR_HEIGHT	= 42.0f;	// �����c��
		const float	LINE_HEIGHT	= 54.0f;	// �s�ԏc��

		const D3DXVECTOR3	POS = D3DXVECTOR3(150.0f, 262.0f, 0.0f);	// �ʒu
		const D3DXVECTOR3	ROT = VEC3_ZERO;							// ����
		const COLOR			COL = COLOR(0.75f, 0.75f, 0.75f, 1.0f);		// �F
		const EAlignX		ALIGN_X = XALIGN_LEFT;		// ���z�u
		const EAlignY		ALIGN_Y = YALIGN_CENTER;	// �c�z�u
	}

	namespace rule
	{
		const char	*FONT	= "data\\FONT\\JF�h�b�g���_�S�V�b�N14.ttf";	// �t�H���g�p�X
		const bool	ITALIC	= false;	// �C�^���b�N
		const float	HEIGHT	= 42.0f;	// �����c��

		const EAlignX		ALIGN_X = XALIGN_LEFT;	// ���z�u
		const D3DXVECTOR3	POS = D3DXVECTOR3(150.0f, 450.0f, 0.0f);	// �ʒu
		const D3DXVECTOR3	ROT = VEC3_ZERO;							// ����
		const COLOR			COL = COLOR(0.75f, 0.75f, 0.75f, 1.0f);		// �F
	}

	namespace select
	{
		const char	*FONT		= "data\\FONT\\JF�h�b�g���_�S�V�b�N14.ttf";	// �t�H���g�p�X
		const bool	ITALIC		= false;	// �C�^���b�N
		const float	CHAR_HEIGHT	= 42.0f;	// �����c��
		const float	LINE_HEIGHT	= 54.0f;	// �s�ԏc��

		const EAlignX ALIGN_X = XALIGN_LEFT;	// ���z�u
		const D3DXVECTOR3 POS = D3DXVECTOR3(255.0f, 535.0f, 0.0f);	// �ʒu
		const D3DXVECTOR3 ROT = VEC3_ZERO;			// ����
		const COLOR COL_DEFAULT	= color::White();	// �ʏ�F
		const COLOR COL_CHOICE	= color::Yellow();	// �I��F
	}

	namespace virsion
	{
		const char	*FONT	= "data\\FONT\\Crypt of Tomorrow.ttf";	// �t�H���g�p�X
		const bool	ITALIC	= false;	// �C�^���b�N
		const float	HEIGHT	= 22.5f;	// �����c��

		const EAlignX		ALIGN_X = XALIGN_CENTER;	// ���z�u
		const D3DXVECTOR3	POS = D3DXVECTOR3(SCREEN_CENT.x, 706.0f, 0.0f);	// �ʒu
		const D3DXVECTOR3	ROT = VEC3_ZERO;								// ����
		const COLOR			COL = COLOR(0.5f, 0.5f, 0.5f, 1.0f);			// �F
	}
}

//************************************************************
//	�q�N���X [CStartStateTutorial] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CStartStateTutorial::CStartStateTutorial() :
	m_pCont			(nullptr),	// �������
	m_pTitle		(nullptr),	// �^�C�g��
	m_pRule			(nullptr),	// �Q�[���T�v
	m_pVersion		(nullptr),	// �o�[�W�����\�L
	m_nCurSelect	(0),		// ���݂̑I����
	m_nOldSelect	(0)			// �O��̑I����
{
	// �����o�ϐ����N���A
	memset(&m_apSelect[0], 0, sizeof(m_apSelect));	// �I����
}

//============================================================
//	�f�X�g���N�^
//============================================================
CStartStateTutorial::~CStartStateTutorial()
{

}

//============================================================
//	����������
//============================================================
HRESULT CStartStateTutorial::Init(void)
{
	// �����o�ϐ���������
	memset(&m_apSelect[0], 0, sizeof(m_apSelect));	// �I����
	m_pCont			= nullptr;	// �������
	m_pTitle		= nullptr;	// �^�C�g��
	m_pRule			= nullptr;	// �Q�[���T�v
	m_pVersion		= nullptr;	// �o�[�W�����\�L
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
	loadtext::BindString(m_pTitle, loadtext::LoadText(PASS, CStartManager::TEXT_BUTTON_TITLE));

	// ��������̐���
	m_pCont = CText2D::Create
	( // ����
		control::FONT,			// �t�H���g�p�X
		control::ITALIC,		// �C�^���b�N
		control::POS,			// ���_�ʒu
		control::CHAR_HEIGHT,	// �����c��
		control::LINE_HEIGHT,	// �s�ԏc��
		control::ALIGN_X,		// ���z�u
		control::ALIGN_Y,		// �c�z�u
		control::ROT,			// ���_����
		control::COL			// �F
	);
	if (m_pCont == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	m_pCont->SetPriority(PRIORITY);

	// �e�L�X�g������
	loadtext::BindText(m_pCont, loadtext::LoadText(PASS, CStartManager::TEXT_BUTTON_KINDS));

	// �Q�[���T�v�̐���
	m_pRule = CString2D::Create
	( // ����
		rule::FONT,		// �t�H���g�p�X
		rule::ITALIC,	// �C�^���b�N
		L"",			// �w�蕶����
		rule::POS,		// ���_�ʒu
		rule::HEIGHT,	// �����c��
		rule::ALIGN_X,	// ���z�u
		rule::ROT,		// ���_����
		rule::COL		// �F
	);

	// �D�揇�ʂ�ݒ�
	m_pRule->SetPriority(PRIORITY);

	// �����������
	loadtext::BindString(m_pRule, loadtext::LoadText(PASS, CStartManager::TEXT_RULE));

	for (int i = 0; i < SELECT_MAX; i++)
	{ // �I�����̑������J��Ԃ�

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

		// �D�揇�ʂ�ݒ�
		m_apSelect[i]->SetPriority(PRIORITY);

		// �����������
		loadtext::BindString(m_apSelect[i], loadtext::LoadText(PASS, CStartManager::TEXT_START + i));
	}

	// �o�[�W�����\�L�̐���
	m_pVersion = CString2D::Create
	( // ����
		virsion::FONT,		// �t�H���g�p�X
		virsion::ITALIC,	// �C�^���b�N
		L"",				// �w�蕶����
		virsion::POS,		// ���_�ʒu
		virsion::HEIGHT,	// �����c��
		virsion::ALIGN_X,	// ���z�u
		virsion::ROT,		// ���_����
		virsion::COL		// �F
	);

	// �D�揇�ʂ�ݒ�
	m_pVersion->SetPriority(PRIORITY);

	// �����������
	loadtext::BindString(m_pVersion, loadtext::LoadText(PASS, CStartManager::TEXT_VIRSION));

	// �C���g���m�C�Y���~
	GET_MANAGER->GetSound()->Stop(CSound::LABEL_SE_INTRONOISE);

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CStartStateTutorial::Uninit(void)
{
	// �^�C�g���̏I��
	SAFE_UNINIT(m_pTitle);

	// ��������̏I��
	SAFE_UNINIT(m_pCont);

	// �Q�[���T�v�̏I��
	SAFE_UNINIT(m_pRule);

	for (int i = 0; i < SELECT_MAX; i++)
	{ // �I�����̑������J��Ԃ�

		// �I�����̏I��
		SAFE_UNINIT(m_apSelect[i]);
	}

	// �o�[�W�����\�L�̏I��
	SAFE_UNINIT(m_pVersion);

	// ���g�̔j��
	delete this;
}

//============================================================
//	�X�V����
//============================================================
void CStartStateTutorial::Update(const float fDeltaTime)
{
	// �I���̍X�V
	UpdateSelect();

	// ����̍X�V
	UpdateDecide();
}

//============================================================
//	�I���̍X�V����
//============================================================
void CStartStateTutorial::UpdateSelect(void)
{
	CInputKeyboard *pKey = GET_INPUTKEY;	// �L�[�{�[�h���

	// �O��̑I������ۑ�
	m_nOldSelect = m_nCurSelect;

	// �I��������
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

	// �O��̑I��v�f�̐F�𔒐F�ɐݒ�
	m_apSelect[m_nOldSelect]->SetColor(select::COL_DEFAULT);

	// ���݂̑I��v�f�̐F�����F�ɐݒ�
	m_apSelect[m_nCurSelect]->SetColor(select::COL_CHOICE);
}

//============================================================
//	����̍X�V����
//============================================================
void CStartStateTutorial::UpdateDecide(void)
{
	if (input::Decide())
	{
		// �I�����ɉ����đJ�ڐ��ύX
		switch (m_nCurSelect)
		{ // ���݂̑I�������Ƃ̏���
		case SELECT_START:
			m_pContext->ChangeState(new CStartStateCreateName);	// �������
			break;

		case SELECT_OPTION:
			m_pContext->ChangeState(new CStartStateOption);	// �����ݒ���
			break;

		default:
			assert(false);
			break;
		}
	}
}
