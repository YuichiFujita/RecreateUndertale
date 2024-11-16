//============================================================
//
//	�~�j�X�e�[�^�X���j���[���� [menuStatusUI.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "menuStatusUI.h"
#include "menuUI.h"
#include "frame2D.h"
#include "string2D.h"
#include "text2D.h"
#include "loadtext.h"
#include "sceneGame.h"
#include "player.h"
#include "playerStatus.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const int PRIORITY = 5;	// �~�j�X�e�[�^�X���j���[�̗D�揇��

	namespace frame
	{
		const VECTOR3 POS	= VECTOR3(155.0f, 160.0f, 0.0f);	// �t���[���ʒu
		const VECTOR3 ROT	= VEC3_ZERO;						// �t���[������
		const VECTOR3 SIZE	= VECTOR3(200.0f, 145.0f, 0.0f);	// �t���[���傫��
	}

	namespace name
	{
		const char*	FONT	= "data\\FONT\\JF�h�b�g���_�S�V�b�N14.ttf";	// �t�H���g�p�X	// TODO�F�����t�H���g�Ⴄ�̎g���Ă�
		const bool	ITALIC	= false;	// �C�^���b�N
		const float	HEIGHT	= 26.0f;	// �����c��

		const VECTOR3	POS = VECTOR3(68.0f, 115.0f, 0.0f);	// �ʒu
		const VECTOR3	ROT = VEC3_ZERO;		// ����
		const COLOR		COL = color::White();	// �F
		const EAlignX	ALIGN_X = XALIGN_LEFT;	// ���z�u
	}

	namespace status
	{
		const char*	FONT = "data\\FONT\\Crypt of Tomorrow.ttf";	// �t�H���g�p�X7
		const char*	PATH = "data\\TEXT\\menu.txt";	// �e�L�X�g�p�X
		const bool	ITALIC		= false;	// �C�^���b�N
		const float	CHAR_HEIGHT	= 22.0f;	// �����c��
		const float	LINE_HEIGHT	= 26.0f;	// �s�ԏc��

		const VECTOR3	POS = VECTOR3(68.0f, 225.5f, 0.0f);	// �ʒu
		const VECTOR3	ROT = VEC3_ZERO;			// ����
		const COLOR		COL = color::White();		// �F
		const EAlignX	ALIGN_X = XALIGN_LEFT;		// ���z�u
		const EAlignY	ALIGN_Y = YALIGN_BOTTOM;	// �c�z�u
	}

	namespace value
	{
		const char*	FONT		= status::FONT;			// �t�H���g�p�X
		const bool	ITALIC		= status::ITALIC;		// �C�^���b�N
		const float	CHAR_HEIGHT	= status::CHAR_HEIGHT;	// �����c��
		const float	LINE_HEIGHT = status::LINE_HEIGHT;	// �s�ԏc��

		const VECTOR3	POS = VECTOR3(115.0f, status::POS.y, 0.0f);	// �ʒu
		const VECTOR3	ROT = VEC3_ZERO;			// ����
		const COLOR		COL = color::White();		// �F
		const EAlignX	ALIGN_X = XALIGN_LEFT;		// ���z�u
		const EAlignY	ALIGN_Y = YALIGN_BOTTOM;	// �c�z�u
	}
}

//************************************************************
//	�q�N���X [CMenuStatusUI] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CMenuStatusUI::CMenuStatusUI() : CObject(CObject::LABEL_UI, CObject::DIM_3D, PRIORITY),
	m_pFrame	(nullptr),	// �t���[�����
	m_pName		(nullptr),	// ���O���
	m_pStatus	(nullptr),	// �X�e�[�^�X���
	m_pValue	(nullptr)	// �X�e�[�^�X���l���
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CMenuStatusUI::~CMenuStatusUI()
{

}

//============================================================
//	����������
//============================================================
HRESULT CMenuStatusUI::Init()
{
	CPlayerStatus status = *CSceneGame::GetPlayer()->GetStatus();	// �X�e�[�^�X���

	// �����o�ϐ���������
	m_pFrame	= nullptr;	// �t���[�����
	m_pName		= nullptr;	// ���O���
	m_pStatus	= nullptr;	// �X�e�[�^�X���
	m_pValue	= nullptr;	// �X�e�[�^�X���l���

	// �t���[���̐���
	m_pFrame = CFrame2D::Create
	( // ����
		frame::POS,	// �ʒu
		frame::ROT,	// ����
		frame::SIZE	// �傫��
	);
	if (m_pFrame == nullptr)
	{ // �����Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	m_pFrame->SetPriority(PRIORITY);

	// ���O�̐���
	m_pName = CString2D::Create
	( // ����
		name::FONT,			// �t�H���g�p�X
		name::ITALIC,		// �C�^���b�N
		status.GetName(),	// �w�蕶����
		name::POS,			// ���_�ʒu
		name::HEIGHT,		// �����c��
		name::ALIGN_X,		// ���z�u
		name::ROT,			// ���_����
		name::COL			// �F
	);
	if (m_pName == nullptr)
	{ // �����Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	m_pName->SetPriority(PRIORITY);

	// �X�e�[�^�X�̐���
	m_pStatus = CText2D::Create
	( // ����
		status::FONT,			// �t�H���g�p�X
		status::ITALIC,			// �C�^���b�N
		status::POS,			// ���_�ʒu
		status::CHAR_HEIGHT,	// �����c��
		status::LINE_HEIGHT,	// �s�ԏc��
		status::ALIGN_X,		// ���z�u
		status::ALIGN_Y,		// �c�z�u
		status::ROT,			// ���_����
		status::COL				// �F
	);
	if (m_pStatus == nullptr)
	{ // �����Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	m_pStatus->SetPriority(PRIORITY);

	// �����������
	loadtext::BindText(m_pStatus, loadtext::LoadText(status::PATH, CMenuUI::TEXT_MINI_STATUS));

	// �X�e�[�^�X���l�̐���
	m_pValue = CText2D::Create
	( // ����
		value::FONT,		// �t�H���g�p�X
		value::ITALIC,		// �C�^���b�N
		value::POS,			// ���_�ʒu
		value::CHAR_HEIGHT,	// �����c��
		value::LINE_HEIGHT,	// �s�ԏc��
		value::ALIGN_X,		// ���z�u
		value::ALIGN_Y,		// �c�z�u
		value::ROT,			// ���_����
		value::COL			// �F
	);
	if (m_pValue == nullptr)
	{ // �����Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// �̗͏��̎擾
	const std::string& rHP = std::to_string(status.GetHP());		// ���݂̗͕̑�����
	const std::string& rMaxHP = std::to_string(status.GetMaxHP());	// �ő�̗͕̑�����

	// �X�e�[�^�X���̒ǉ�
	m_pValue->PushBackString(std::to_string(status.GetLove()));
	m_pValue->PushBackString(useful::SandString(rHP, "/", rMaxHP));
	m_pValue->PushBackString(std::to_string(status.GetNumGold()));

	// �D�揇�ʂ�ݒ�
	m_pValue->SetPriority(PRIORITY);

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CMenuStatusUI::Uninit()
{
	// �t���[���̏I��
	SAFE_UNINIT(m_pFrame);

	// ���O�̏I��
	SAFE_UNINIT(m_pName);

	// �X�e�[�^�X�̏I��
	SAFE_UNINIT(m_pStatus);

	// �X�e�[�^�X���l�̏I��
	SAFE_UNINIT(m_pValue);

	// �I�u�W�F�N�g��j��
	Release();
}

//============================================================
//	�X�V����
//============================================================
void CMenuStatusUI::Update(const float fDeltaTime)
{

}

//============================================================
//	�`�揈��
//============================================================
void CMenuStatusUI::Draw(CShader* /*pShader*/)
{

}

//============================================================
//	��������
//============================================================
CMenuStatusUI* CMenuStatusUI::Create()
{
	// �~�j�X�e�[�^�X���j���[�̐���
	CMenuStatusUI* pMenuStatusUI = new CMenuStatusUI;
	if (pMenuStatusUI == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �~�j�X�e�[�^�X���j���[�̏�����
		if (FAILED(pMenuStatusUI->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �~�j�X�e�[�^�X���j���[�̔j��
			SAFE_DELETE(pMenuStatusUI);
			return nullptr;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return pMenuStatusUI;
	}
}
