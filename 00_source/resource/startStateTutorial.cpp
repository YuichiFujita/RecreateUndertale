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
		const float	HEIGHT	= 45.0f;	// �����c��

		const CString2D::EAlignX ALIGN_X = CString2D::XALIGN_CENTER;		// ���z�u
		const D3DXVECTOR3	POS = D3DXVECTOR3(SCREEN_CENT.x, 70.0f, 0.0f);	// �ʒu
		const D3DXVECTOR3	ROT = VEC3_ZERO;								// ����
		const D3DXCOLOR		COL = D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f);		// �F
	}

	namespace control
	{
		const char *FONT = "data\\FONT\\JF�h�b�g���_�S�V�b�N14.ttf";	// �t�H���g�p�X
		const bool	ITALIC		= false;	// �C�^���b�N
		const float	CHAR_HEIGHT	= 45.0f;	// �����c��
		const float	LINE_HEIGHT	= 62.0f;	// �s�ԏc��

		const D3DXVECTOR3	POS = D3DXVECTOR3(120.0f, 285.0f, 0.0f);	// �ʒu
		const D3DXVECTOR3	ROT = VEC3_ZERO;							// ����
		const D3DXCOLOR		COL = D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f);	// �F
		const CString2D::EAlignX	ALIGN_X = CString2D::XALIGN_LEFT;	// ���z�u
		const CText2D::EAlignY		ALIGN_Y = CText2D::YALIGN_CENTER;	// �c�z�u
	}

	namespace rule
	{
		const char	*FONT = "data\\FONT\\JF�h�b�g���_�S�V�b�N14.ttf";	// �t�H���g�p�X
		const bool	ITALIC = false;	// �C�^���b�N
		const float	HEIGHT = 45.0f;	// �����c��

		const CString2D::EAlignX ALIGN_X = CString2D::XALIGN_LEFT;		// ���z�u
		const D3DXVECTOR3	POS = D3DXVECTOR3(120.0f, 500.0f, 0.0f);	// �ʒu
		const D3DXVECTOR3	ROT = VEC3_ZERO;							// ����
		const D3DXCOLOR		COL = D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f);	// �F
	}

	namespace virsion
	{
		const char	*FONT	= "data\\FONT\\Crypt of Tomorrow.ttf";	// �t�H���g�p�X
		const bool	ITALIC	= false;	// �C�^���b�N
		const float	HEIGHT	= 22.5f;	// �����c��

		const CString2D::EAlignX ALIGN_X = CString2D::XALIGN_CENTER;		// ���z�u
		const D3DXVECTOR3	POS = D3DXVECTOR3(SCREEN_CENT.x, 706.0f, 0.0f);	// �ʒu
		const D3DXVECTOR3	ROT = VEC3_ZERO;								// ����
		const D3DXCOLOR		COL = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);		// �F
	}
}

//************************************************************
//	�q�N���X [CStartStateTutorial] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CStartStateTutorial::CStartStateTutorial() :
	m_pCont		(nullptr),	// �������
	m_pTitle	(nullptr),	// �^�C�g��
	m_pRule		(nullptr),	// �Q�[���T�v
	m_pVersion	(nullptr)	// �o�[�W�����\�L
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
	m_pCont		= nullptr;	// �������
	m_pTitle	= nullptr;	// �^�C�g��
	m_pRule		= nullptr;	// �Q�[���T�v
	m_pVersion	= nullptr;	// �o�[�W�����\�L

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

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CStartStateTutorial::Uninit(void)
{
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

}
