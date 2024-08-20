//============================================================
//
//	�t���X�e�[�^�X���j���[���� [selectStatusUI.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "selectStatusUI.h"
#include "loadtext.h"
#include "string2D.h"
#include "text2D.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const char	*FONT	 = "data\\FONT\\JF�h�b�g���_�S�V�b�N14.ttf";	// �t�H���g�p�X
	const char	*PASS	 = "data\\TEXT\\start.txt";						// �e�L�X�g�p�X	// TODO�F�p�X�ǂ������邩
	const bool	ITALIC	 = false;	// �C�^���b�N
	const float	HEIGHT	 = 42.0f;	// �����c��
	const int	PRIORITY = 6;		// �t���X�e�[�^�X���j���[�̗D�揇��

	namespace frame
	{
		const D3DXVECTOR3 POS	= D3DXVECTOR3(555.0f, 386.5f, 0.0f);	// �t���[���ʒu
		const D3DXVECTOR3 ROT	= VEC3_ZERO;							// �t���[������
		const D3DXVECTOR3 SIZE	= D3DXVECTOR3(525.0f, 600.0f, 0.0f);	// �t���[���傫��
	}

	namespace name
	{
		const CString2D::EAlignX ALIGN_X = CString2D::XALIGN_LEFT;		// ���z�u
		const D3DXVECTOR3	POS = D3DXVECTOR3(320.0f, 140.0f, 0.0f);	// �ʒu
		const D3DXVECTOR3	ROT = VEC3_ZERO;	// ����
		const D3DXCOLOR		COL = XCOL_WHITE;	// �F
	}

	namespace lvhp_title
	{
		const CString2D::EAlignX	ALIGN_X = CString2D::XALIGN_LEFT;	// ���z�u
		const CText2D::EAlignY		ALIGN_Y = CText2D::YALIGN_TOP;		// �c�z�u
		const D3DXVECTOR3	POS = D3DXVECTOR3(320.0f, 205.5f, 0.0f);	// �ʒu
		const D3DXVECTOR3	ROT = VEC3_ZERO;	// ����
		const D3DXCOLOR		COL = XCOL_WHITE;	// �F
		const float	LINE_HEIGHT = 44.0f;		// �s�ԏc��
	}

	namespace lvhp_value
	{
		const CString2D::EAlignX	ALIGN_X = CString2D::XALIGN_LEFT;	// ���z�u
		const CText2D::EAlignY		ALIGN_Y = CText2D::YALIGN_TOP;		// �c�z�u
		const D3DXVECTOR3	POS = D3DXVECTOR3(415.0f, 205.5f, 0.0f);	// �ʒu
		const D3DXVECTOR3	ROT = VEC3_ZERO;	// ����
		const D3DXCOLOR		COL = XCOL_WHITE;	// �F
		const float	LINE_HEIGHT = 44.0f;		// �s�ԏc��
	}
}

//************************************************************
//	�q�N���X [CSelectStatusUI] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CSelectStatusUI::CSelectStatusUI(AFuncUninit funcUninit, CObject2D *pSoul) : CSelect(funcUninit, pSoul),
	m_pName		 (nullptr),	// ���O���
	m_pLvHpTitle (nullptr),	// ���x��/HP�^�C�g�����
	m_pLvHpValue (nullptr)	// ���x��/HP���l���
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CSelectStatusUI::~CSelectStatusUI()
{

}

//============================================================
//	����������
//============================================================
HRESULT CSelectStatusUI::Init(void)
{
	// �����o�ϐ���������
	m_pName		 = nullptr;	// ���O���
	m_pLvHpTitle = nullptr;	// ���x��/HP�^�C�g�����
	m_pLvHpValue = nullptr;	// ���x��/HP���l���

	//--------------------------------------------------------
	//	�e�N���X�̏����� / �ݒ�
	//--------------------------------------------------------
	// �Z���N�g�̏�����
	if (FAILED(CSelect::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �t���[���̈ʒu��ݒ�
	SetFramePosition(frame::POS);

	// �t���[���̌�����ݒ�
	SetFrameRotation(frame::ROT);

	// �t���[���̑傫����ݒ�
	SetFrameSizing(frame::SIZE);

	// �\�E���J�[�\���̕`���OFF�ɂ���
	SetSoulCursorDraw(false);

	//--------------------------------------------------------
	//	���O�̏����� / �ݒ�
	//--------------------------------------------------------
	// �\�����閼�O��������쐬
	std::wstring wsName;
	wsName.append(L"\"");		// �h��擪�ɒǉ�
	wsName.append(L"���Ղ���");	// ���O��ǉ�	// TODO�F�O���Ǎ�
	wsName.append(L"\"");		// �h���Ō���ɒǉ�

	// ���O�̐���
	m_pName = CString2D::Create
	( // ����
		FONT,			// �t�H���g�p�X
		ITALIC,			// �C�^���b�N
		wsName,			// �w�蕶����
		name::POS,		// ���_�ʒu
		HEIGHT,			// �����c��
		name::ALIGN_X,	// ���z�u
		name::ROT,		// ���_����
		name::COL		// �F
	);

	// �D�揇�ʂ�ݒ�
	m_pName->SetPriority(PRIORITY);

	//--------------------------------------------------------
	//	���x�� / HP�^�C�g���̏����� / �ݒ�
	//--------------------------------------------------------
	// ���x��/HP�^�C�g���̐���
	m_pLvHpTitle = CText2D::Create
	( // ����
		FONT,						// �t�H���g�p�X
		ITALIC,						// �C�^���b�N
		lvhp_title::POS,			// ���_�ʒu
		HEIGHT,						// �����c��
		lvhp_title::LINE_HEIGHT,	// �s�ԏc��
		lvhp_title::ALIGN_X,		// ���z�u
		lvhp_title::ALIGN_Y,		// �c�z�u
		lvhp_title::ROT,			// ���_����
		lvhp_title::COL				// �F
	);
	if (m_pLvHpTitle == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	m_pLvHpTitle->SetPriority(PRIORITY);

	// TODO�F�O���t�@�C����
#if 1
	m_pLvHpTitle->AddString(L"LV");
	m_pLvHpTitle->AddString(L"HP");
#endif

	//--------------------------------------------------------
	//	���x�� / HP���l�̏����� / �ݒ�
	//--------------------------------------------------------
	// ���x��/HP���l�̐���
	m_pLvHpValue = CText2D::Create
	( // ����
		FONT,						// �t�H���g�p�X
		ITALIC,						// �C�^���b�N
		lvhp_value::POS,			// ���_�ʒu
		HEIGHT,						// �����c��
		lvhp_value::LINE_HEIGHT,	// �s�ԏc��
		lvhp_value::ALIGN_X,		// ���z�u
		lvhp_value::ALIGN_Y,		// �c�z�u
		lvhp_value::ROT,			// ���_����
		lvhp_value::COL				// �F
	);
	if (m_pLvHpValue == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	m_pLvHpValue->SetPriority(PRIORITY);

	// TODO�F�X�e�[�^�X���Ǎ�
#if 1
	m_pLvHpValue->AddString(L"1");
	m_pLvHpValue->AddString(L"20/20");
#endif

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CSelectStatusUI::Uninit(void)
{
	// �\�E���J�[�\���̕`���ON�ɂ���
	SetSoulCursorDraw(true);

	// ���O�̏I��
	SAFE_UNINIT(m_pName);

	// ���x��/HP�^�C�g���̏I��
	SAFE_UNINIT(m_pLvHpTitle);

	// ���x��/HP���l�̏I��
	SAFE_UNINIT(m_pLvHpValue);

	// �Z���N�g�̏I��
	CSelect::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CSelectStatusUI::Update(const float fDeltaTime)
{
	// �Z���N�g�̍X�V
	CSelect::Update(fDeltaTime);
}

//============================================================
//	�`�揈��
//============================================================
void CSelectStatusUI::Draw(CShader *pShader)
{
	// �Z���N�g�̕`��
	CSelect::Draw(pShader);
}
