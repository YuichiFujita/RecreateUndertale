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
	const char	*PASS	 = "data\\TEXT\\selectStatus.txt";				// �e�L�X�g�p�X
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
		const D3DXVECTOR3	ROT = VEC3_ZERO;		// ����
		const COLOR			COL = color::White();	// �F
	}

	namespace lvhp_title
	{
		const CString2D::EAlignX	ALIGN_X = CString2D::XALIGN_LEFT;	// ���z�u
		const CText2D::EAlignY		ALIGN_Y = CText2D::YALIGN_TOP;		// �c�z�u
		const D3DXVECTOR3	POS = D3DXVECTOR3(320.0f, 200.5f, 0.0f);	// �ʒu
		const D3DXVECTOR3	ROT = VEC3_ZERO;		// ����
		const COLOR			COL = color::White();	// �F
		const float	LINE_HEIGHT = 53.0f;			// �s�ԏc��
	}

	namespace lvhp_value
	{
		const CString2D::EAlignX	ALIGN_X = CString2D::XALIGN_LEFT;	// ���z�u
		const CText2D::EAlignY		ALIGN_Y = CText2D::YALIGN_TOP;		// �c�z�u
		const D3DXVECTOR3	POS = D3DXVECTOR3(402.0f, 200.5f, 0.0f);	// �ʒu
		const D3DXVECTOR3	ROT = VEC3_ZERO;		// ����
		const COLOR			COL = color::White();	// �F
		const float	LINE_HEIGHT = 53.0f;			// �s�ԏc��
	}

	namespace atkdef_title
	{
		const CString2D::EAlignX	ALIGN_X = CString2D::XALIGN_LEFT;	// ���z�u
		const CText2D::EAlignY		ALIGN_Y = CText2D::YALIGN_TOP;		// �c�z�u
		const D3DXVECTOR3	POS = D3DXVECTOR3(320.0f, 330.5f, 0.0f);	// �ʒu
		const D3DXVECTOR3	ROT = VEC3_ZERO;		// ����
		const COLOR			COL = color::White();	// �F
		const float	LINE_HEIGHT = 53.0f;			// �s�ԏc��
	}

	namespace atkdef_value
	{
		const CString2D::EAlignX	ALIGN_X = CString2D::XALIGN_LEFT;	// ���z�u
		const CText2D::EAlignY		ALIGN_Y = CText2D::YALIGN_TOP;		// �c�z�u
		const D3DXVECTOR3	POS = D3DXVECTOR3(402.0f, 330.5f, 0.0f);	// �ʒu
		const D3DXVECTOR3	ROT = VEC3_ZERO;		// ����
		const COLOR			COL = color::White();	// �F
		const float	LINE_HEIGHT = 53.0f;			// �s�ԏc��
	}

	namespace expnext_title
	{
		const CString2D::EAlignX	ALIGN_X = CString2D::XALIGN_LEFT;	// ���z�u
		const CText2D::EAlignY		ALIGN_Y = CText2D::YALIGN_TOP;		// �c�z�u
		const D3DXVECTOR3	POS = D3DXVECTOR3(570.0f, 330.5f, 0.0f);	// �ʒu
		const D3DXVECTOR3	ROT = VEC3_ZERO;		// ����
		const COLOR			COL = color::White();	// �F
		const float	LINE_HEIGHT = 53.0f;			// �s�ԏc��
	}

	namespace expnext_value
	{
		const CString2D::EAlignX	ALIGN_X = CString2D::XALIGN_LEFT;	// ���z�u
		const CText2D::EAlignY		ALIGN_Y = CText2D::YALIGN_TOP;		// �c�z�u
		const D3DXVECTOR3	POS = D3DXVECTOR3(672.0f, 330.5f, 0.0f);	// �ʒu
		const D3DXVECTOR3	ROT = VEC3_ZERO;		// ����
		const COLOR			COL = color::White();	// �F
		const float	LINE_HEIGHT = 53.0f;			// �s�ԏc��
	}

	namespace wpnamr_title
	{
		const CString2D::EAlignX	ALIGN_X = CString2D::XALIGN_LEFT;	// ���z�u
		const CText2D::EAlignY		ALIGN_Y = CText2D::YALIGN_TOP;		// �c�z�u
		const D3DXVECTOR3	POS = D3DXVECTOR3(320.0f, 460.5f, 0.0f);	// �ʒu
		const D3DXVECTOR3	ROT = VEC3_ZERO;		// ����
		const COLOR			COL = color::White();	// �F
		const float	LINE_HEIGHT = 53.0f;			// �s�ԏc��
	}

	namespace wpnamr_name
	{
		const CString2D::EAlignX	ALIGN_X = CString2D::XALIGN_LEFT;	// ���z�u
		const CText2D::EAlignY		ALIGN_Y = CText2D::YALIGN_TOP;		// �c�z�u
		const D3DXVECTOR3	POS = D3DXVECTOR3(402.0f, 460.5f, 0.0f);	// �ʒu
		const D3DXVECTOR3	ROT = VEC3_ZERO;		// ����
		const COLOR			COL = color::White();	// �F
		const float	LINE_HEIGHT = 53.0f;			// �s�ԏc��
	}

	namespace gold_title
	{
		const CString2D::EAlignX ALIGN_X = CString2D::XALIGN_LEFT;		// ���z�u
		const D3DXVECTOR3	POS = D3DXVECTOR3(320.0f, 615.5f, 0.0f);	// �ʒu
		const D3DXVECTOR3	ROT = VEC3_ZERO;		// ����
		const COLOR			COL = color::White();	// �F
	}

	namespace gold_value
	{
		const CString2D::EAlignX ALIGN_X = CString2D::XALIGN_LEFT;		// ���z�u
		const D3DXVECTOR3	POS = D3DXVECTOR3(423.0f, 615.5f, 0.0f);	// �ʒu
		const D3DXVECTOR3	ROT = VEC3_ZERO;		// ����
		const COLOR			COL = color::White();	// �F
	}

	namespace kills_title
	{
		const CString2D::EAlignX ALIGN_X = CString2D::XALIGN_LEFT;		// ���z�u
		const D3DXVECTOR3	POS = D3DXVECTOR3(500.0f, 615.5f, 0.0f);	// �ʒu
		const D3DXVECTOR3	ROT = VEC3_ZERO;		// ����
		const COLOR			COL = color::White();	// �F
	}

	namespace kills_value
	{
		const CString2D::EAlignX ALIGN_X = CString2D::XALIGN_LEFT;		// ���z�u
		const D3DXVECTOR3	POS = D3DXVECTOR3(627.0f, 615.5f, 0.0f);	// �ʒu
		const D3DXVECTOR3	ROT = VEC3_ZERO;		// ����
		const COLOR			COL = color::White();	// �F
	}
}

//************************************************************
//	�q�N���X [CSelectStatusUI] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CSelectStatusUI::CSelectStatusUI(AFuncUninit funcUninit, CObject2D *pSoul) : CSelectUI(funcUninit, pSoul),
	m_pName			(nullptr),	// ���O���
	m_pLvHpTitle	(nullptr),	// LV/HP�^�C�g�����
	m_pLvHpValue	(nullptr),	// LV/HP���l���
	m_pAtkDefTitle	(nullptr),	// ATK/DEF�^�C�g�����
	m_pAtkDefValue	(nullptr),	// ATK/DEF���l���
	m_pExpNextTitle	(nullptr),	// EXP/NEXT�^�C�g�����
	m_pExpNextValue	(nullptr),	// EXP/NEXT���l���
	m_pWpnAmrTitle	(nullptr),	// WPN/AMR�^�C�g�����
	m_pWpnAmrName	(nullptr),	// WPN/AMR���̏��
	m_pGoldTitle	(nullptr),	// GOLD�^�C�g�����
	m_pGoldValue	(nullptr),	// GOLD���l���
	m_pKillsTitle	(nullptr),	// KILLS�^�C�g�����
	m_pKillsValue	(nullptr)	// KILLS���l���
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
	m_pName			= nullptr;	// ���O���
	m_pLvHpTitle	= nullptr;	// LV/HP�^�C�g�����
	m_pLvHpValue	= nullptr;	// LV/HP���l���
	m_pAtkDefTitle	= nullptr;	// ATK/DEF�^�C�g�����
	m_pAtkDefValue	= nullptr;	// ATK/DEF���l���
	m_pExpNextTitle	= nullptr;	// EXP/NEXT�^�C�g�����
	m_pExpNextValue	= nullptr;	// EXP/NEXT���l���
	m_pWpnAmrTitle	= nullptr;	// WPN/AMR�^�C�g�����
	m_pWpnAmrName	= nullptr;	// WPN/AMR���̏��
	m_pGoldTitle	= nullptr;	// GOLD�^�C�g�����
	m_pGoldValue	= nullptr;	// GOLD���l���
	m_pKillsTitle	= nullptr;	// KILLS�^�C�g�����
	m_pKillsValue	= nullptr;	// KILLS���l���

	//--------------------------------------------------------
	//	�e�N���X�̏����� / �ݒ�
	//--------------------------------------------------------
	// �Z���N�gUI�̏�����
	if (FAILED(CSelectUI::Init()))
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
	SetFrameSize(frame::SIZE);

	// �\�E���J�[�\���̕`���OFF�ɂ���
	SetSoulCursorDraw(false);

	//--------------------------------------------------------
	//	���O�̏����� / �ݒ�
	//--------------------------------------------------------
	// �\�����閼�O��������쐬
	std::string sName = useful::SandString("\"", "���Ղ���", "\"");	// TODO�F���O�̊O���Ǎ�

	// ���O�̐���
	m_pName = CString2D::Create
	( // ����
		FONT,			// �t�H���g�p�X
		ITALIC,			// �C�^���b�N
		sName,			// �w�蕶����
		name::POS,		// ���_�ʒu
		HEIGHT,			// �����c��
		name::ALIGN_X,	// ���z�u
		name::ROT,		// ���_����
		name::COL		// �F
	);

	// �D�揇�ʂ�ݒ�
	m_pName->SetPriority(PRIORITY);

	//--------------------------------------------------------
	//	LV / HP�^�C�g���̏����� / �ݒ�
	//--------------------------------------------------------
	// LV/HP�^�C�g���̐���
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

	// �e�L�X�g������
	loadtext::BindText(m_pLvHpTitle, loadtext::LoadText(PASS, TEXT_LV_HP));

	//--------------------------------------------------------
	//	LV / HP���l�̏����� / �ݒ�
	//--------------------------------------------------------
	// LV/HP���l�̐���
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
	m_pLvHpValue->PushBackString("1");
	m_pLvHpValue->PushBackString(useful::SandString("20", "/", "20"));
#endif

	//--------------------------------------------------------
	//	ATK / DEF�^�C�g���̏����� / �ݒ�
	//--------------------------------------------------------
	// ATK/DEF�^�C�g���̐���
	m_pAtkDefTitle = CText2D::Create
	( // ����
		FONT,						// �t�H���g�p�X
		ITALIC,						// �C�^���b�N
		atkdef_title::POS,			// ���_�ʒu
		HEIGHT,						// �����c��
		atkdef_title::LINE_HEIGHT,	// �s�ԏc��
		atkdef_title::ALIGN_X,		// ���z�u
		atkdef_title::ALIGN_Y,		// �c�z�u
		atkdef_title::ROT,			// ���_����
		atkdef_title::COL			// �F
	);
	if (m_pAtkDefTitle == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	m_pAtkDefTitle->SetPriority(PRIORITY);

	// �e�L�X�g������
	loadtext::BindText(m_pAtkDefTitle, loadtext::LoadText(PASS, TEXT_ATK_DEF));

	//--------------------------------------------------------
	//	ATK / DEF���l�̏����� / �ݒ�
	//--------------------------------------------------------
	// ATK/DEF���l�̐���
	m_pAtkDefValue = CText2D::Create
	( // ����
		FONT,						// �t�H���g�p�X
		ITALIC,						// �C�^���b�N
		atkdef_value::POS,			// ���_�ʒu
		HEIGHT,						// �����c��
		atkdef_value::LINE_HEIGHT,	// �s�ԏc��
		atkdef_value::ALIGN_X,		// ���z�u
		atkdef_value::ALIGN_Y,		// �c�z�u
		atkdef_value::ROT,			// ���_����
		atkdef_value::COL			// �F
	);
	if (m_pAtkDefValue == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	m_pAtkDefValue->SetPriority(PRIORITY);

	// TODO�F�X�e�[�^�X��� / �������̓Ǎ�
#if 1
	// �U���͂̃X�e�[�^�X�������ǉ�
	std::string sAtk = std::to_string(0);							// ���O�̃X�e�[�^�X�𕶎���ɒǉ�
	sAtk.append(useful::SandString(" (", std::to_string(3), ")"));	// �����̃v���X�X�e�[�^�X�𕶎���ɒǉ�
	m_pAtkDefValue->PushBackString(sAtk);							// �쐬���������������

	// �h��͂̃X�e�[�^�X�������ǉ�
	std::string sDef = std::to_string(0);							// ���O�̃X�e�[�^�X�𕶎���ɒǉ�
	sDef.append(useful::SandString(" (", std::to_string(3), ")"));	// �����̃v���X�X�e�[�^�X�𕶎���ɒǉ�
	m_pAtkDefValue->PushBackString(sDef);							// �쐬���������������
#endif

	//--------------------------------------------------------
	//	EXP / NEXT�^�C�g���̏����� / �ݒ�
	//--------------------------------------------------------
	// EXP/NEXT�^�C�g���̐���
	m_pExpNextTitle = CText2D::Create
	( // ����
		FONT,						// �t�H���g�p�X
		ITALIC,						// �C�^���b�N
		expnext_title::POS,			// ���_�ʒu
		HEIGHT,						// �����c��
		expnext_title::LINE_HEIGHT,	// �s�ԏc��
		expnext_title::ALIGN_X,		// ���z�u
		expnext_title::ALIGN_Y,		// �c�z�u
		expnext_title::ROT,			// ���_����
		expnext_title::COL			// �F
	);
	if (m_pExpNextTitle == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	m_pExpNextTitle->SetPriority(PRIORITY);

	// �e�L�X�g������
	loadtext::BindText(m_pExpNextTitle, loadtext::LoadText(PASS, TEXT_EXP_NEXT));

	//--------------------------------------------------------
	//	EXP / NEXT���l�̏����� / �ݒ�
	//--------------------------------------------------------
	// EXP/NEXT���l�̐���
	m_pExpNextValue = CText2D::Create
	( // ����
		FONT,						// �t�H���g�p�X
		ITALIC,						// �C�^���b�N
		expnext_value::POS,			// ���_�ʒu
		HEIGHT,						// �����c��
		expnext_value::LINE_HEIGHT,	// �s�ԏc��
		expnext_value::ALIGN_X,		// ���z�u
		expnext_value::ALIGN_Y,		// �c�z�u
		expnext_value::ROT,			// ���_����
		expnext_value::COL			// �F
	);
	if (m_pExpNextValue == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	m_pExpNextValue->SetPriority(PRIORITY);

	// TODO�F�X�e�[�^�X���Ǎ�
#if 1
	m_pExpNextValue->PushBackString("0");
	m_pExpNextValue->PushBackString("10");
#endif

	//--------------------------------------------------------
	//	WPN / AMR�^�C�g���̏����� / �ݒ�
	//--------------------------------------------------------
	// WPN/AMR�^�C�g���̐���
	m_pWpnAmrTitle = CText2D::Create
	( // ����
		FONT,						// �t�H���g�p�X
		ITALIC,						// �C�^���b�N
		wpnamr_title::POS,			// ���_�ʒu
		HEIGHT,						// �����c��
		wpnamr_title::LINE_HEIGHT,	// �s�ԏc��
		wpnamr_title::ALIGN_X,		// ���z�u
		wpnamr_title::ALIGN_Y,		// �c�z�u
		wpnamr_title::ROT,			// ���_����
		wpnamr_title::COL			// �F
	);
	if (m_pWpnAmrTitle == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	m_pWpnAmrTitle->SetPriority(PRIORITY);

	// �e�L�X�g������
	loadtext::BindText(m_pWpnAmrTitle, loadtext::LoadText(PASS, TEXT_WPN_AMR));

	//--------------------------------------------------------
	//	WPN / AMR���̂̏����� / �ݒ�
	//--------------------------------------------------------
	// WPN/AMR���̂̐���
	m_pWpnAmrName = CText2D::Create
	( // ����
		FONT,						// �t�H���g�p�X
		ITALIC,						// �C�^���b�N
		wpnamr_name::POS,			// ���_�ʒu
		HEIGHT,						// �����c��
		wpnamr_name::LINE_HEIGHT,	// �s�ԏc��
		wpnamr_name::ALIGN_X,		// ���z�u
		wpnamr_name::ALIGN_Y,		// �c�z�u
		wpnamr_name::ROT,			// ���_����
		wpnamr_name::COL			// �F
	);
	if (m_pWpnAmrName == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	m_pWpnAmrName->SetPriority(PRIORITY);

	// TODO�F������񂩂疼�̎擾
#if 1
	m_pWpnAmrName->PushBackString("�ڂ�����");
	m_pWpnAmrName->PushBackString("�ق�����");
#endif

	//--------------------------------------------------------
	//	GOLD�^�C�g���̏����� / �ݒ�
	//--------------------------------------------------------
	// GOLD�^�C�g���̐���
	m_pGoldTitle = CString2D::Create
	( // ����
		FONT,					// �t�H���g�p�X
		ITALIC,					// �C�^���b�N
		L"",					// �w�蕶����
		gold_title::POS,		// ���_�ʒu
		HEIGHT,					// �����c��
		gold_title::ALIGN_X,	// ���z�u
		gold_title::ROT,		// ���_����
		gold_title::COL			// �F
	);

	// �D�揇�ʂ�ݒ�
	m_pGoldTitle->SetPriority(PRIORITY);

	// �����������
	loadtext::BindString(m_pGoldTitle, loadtext::LoadText(PASS, TEXT_GOLD));

	//--------------------------------------------------------
	//	GOLD���l�̏����� / �ݒ�
	//--------------------------------------------------------
	// GOLD���l�̐���
	m_pGoldValue = CString2D::Create
	( // ����
		FONT,					// �t�H���g�p�X
		ITALIC,					// �C�^���b�N
		L"",					// �w�蕶����
		gold_value::POS,		// ���_�ʒu
		HEIGHT,					// �����c��
		gold_value::ALIGN_X,	// ���z�u
		gold_value::ROT,		// ���_����
		gold_value::COL			// �F
	);

	// �D�揇�ʂ�ݒ�
	m_pGoldValue->SetPriority(PRIORITY);

	// TODO�F�������擾
#if 1
	m_pGoldValue->SetString("0");
#endif

	// TODO�F�L�����擾
#if 1
	int nNumKill = 0;	// �L����
#endif

	if (nNumKill > 0)
	{ // ��̂ł��E�������Ƃ�����ꍇ

		//----------------------------------------------------
		//	KILLS�^�C�g���̏����� / �ݒ�
		//----------------------------------------------------
		// KILLS�^�C�g���̐���
		m_pKillsTitle = CString2D::Create
		( // ����
			FONT,					// �t�H���g�p�X
			ITALIC,					// �C�^���b�N
			L"",					// �w�蕶����
			kills_title::POS,		// ���_�ʒu
			HEIGHT,					// �����c��
			kills_title::ALIGN_X,	// ���z�u
			kills_title::ROT,		// ���_����
			kills_title::COL		// �F
		);

		// �D�揇�ʂ�ݒ�
		m_pKillsTitle->SetPriority(PRIORITY);

		// �����������
		loadtext::BindString(m_pKillsTitle, loadtext::LoadText(PASS, TEXT_KILLS));

		//----------------------------------------------------
		//	KILLS���l�̏����� / �ݒ�
		//----------------------------------------------------
		// KILLS���l�̐���
		m_pKillsValue = CString2D::Create
		( // ����
			FONT,					// �t�H���g�p�X
			ITALIC,					// �C�^���b�N
			L"",					// �w�蕶����
			kills_value::POS,		// ���_�ʒu
			HEIGHT,					// �����c��
			kills_value::ALIGN_X,	// ���z�u
			kills_value::ROT,		// ���_����
			kills_value::COL		// �F
		);

		// �D�揇�ʂ�ݒ�
		m_pKillsValue->SetPriority(PRIORITY);

		// �\����������w��
		m_pKillsValue->SetString(std::to_string(nNumKill));
	}

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

	// LV/HP�^�C�g���̏I��
	SAFE_UNINIT(m_pLvHpTitle);

	// LV/HP���l�̏I��
	SAFE_UNINIT(m_pLvHpValue);

	// ATK/DEF�^�C�g���̏I��
	SAFE_UNINIT(m_pAtkDefTitle);

	// ATK/DEF���l�̏I��
	SAFE_UNINIT(m_pAtkDefValue);

	// EXP/NEXT�^�C�g���̏I��
	SAFE_UNINIT(m_pExpNextTitle);

	// EXP/NEXT���l�̏I��
	SAFE_UNINIT(m_pExpNextValue);

	// WPN/AMR�^�C�g���̏I��
	SAFE_UNINIT(m_pWpnAmrTitle);

	// WPN/AMR���̂̏I��
	SAFE_UNINIT(m_pWpnAmrName);

	// GOLD�^�C�g���̏I��
	SAFE_UNINIT(m_pGoldTitle);

	// GOLD���l�̏I��
	SAFE_UNINIT(m_pGoldValue);

	// KILLS�^�C�g���̏I��
	SAFE_UNINIT(m_pKillsTitle);

	// KILLS���l�̏I��
	SAFE_UNINIT(m_pKillsValue);

	// �Z���N�gUI�̏I��
	CSelectUI::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CSelectStatusUI::Update(const float fDeltaTime)
{
	// �Z���N�gUI�̍X�V
	CSelectUI::Update(fDeltaTime);
}

//============================================================
//	�`�揈��
//============================================================
void CSelectStatusUI::Draw(CShader *pShader)
{
	// �Z���N�gUI�̕`��
	CSelectUI::Draw(pShader);
}
