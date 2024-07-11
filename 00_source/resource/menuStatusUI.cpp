//============================================================
//
//	�X�e�[�^�X���j���[���� [menuStatusUI.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "menuStatusUI.h"
#include "frame2D.h"
#include "string2D.h"
#include "text2D.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const int PRIORITY = 6;	// �X�e�[�^�X���j���[�̗D�揇��

	namespace frame
	{
		const D3DXVECTOR3 POS	= D3DXVECTOR3(155.0f, 160.0f, 0.0f);	// �t���[���ʒu
		const D3DXVECTOR3 ROT	= VEC3_ZERO;							// �t���[������
		const D3DXVECTOR3 SIZE	= D3DXVECTOR3(200.0f, 140.0f, 0.0f);	// �t���[���傫��
	}

	namespace name
	{
		const char	*FONT	= "data\\FONT\\JF�h�b�g���_�S�V�b�N14.ttf";	// �t�H���g�p�X	// TODO�F�����t�H���g�Ⴄ�̎g���Ă�
		const bool	ITALIC	= false;	// �C�^���b�N
		const float	HEIGHT	= 26.0f;	// �����c��

		const CString2D::EAlignX ALIGN_X = CString2D::XALIGN_LEFT;	// ���z�u
		const D3DXVECTOR3	POS = D3DXVECTOR3(68.0f, 115.0f, 0.0f);	// �ʒu
		const D3DXVECTOR3	ROT = VEC3_ZERO;	// ����
		const D3DXCOLOR		COL = XCOL_WHITE;	// �F
	}

	namespace status
	{
		const char	*FONT = "data\\FONT\\Crypt of Tomorrow.ttf";	// �t�H���g�p�X
		const bool	ITALIC		= false;	// �C�^���b�N
		const float	CHAR_HEIGHT	= 22.0f;	// �����c��
		const float	LINE_HEIGHT	= 26.0f;	// �s�ԏc��

		const CString2D::EAlignX	ALIGN_X = CString2D::XALIGN_LEFT;	// ���z�u
		const CText2D::EAlignY		ALIGN_Y = CText2D::YALIGN_BOTTOM;	// �c�z�u
		const D3DXVECTOR3	POS = D3DXVECTOR3(68.0f, 223.0f, 0.0f);		// �ʒu
		const D3DXVECTOR3	ROT = VEC3_ZERO;	// ����
		const D3DXCOLOR		COL = XCOL_WHITE;	// �F
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
	m_pStatus	(nullptr)	// �X�e�[�^�X���
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
HRESULT CMenuStatusUI::Init(void)
{
	// �����o�ϐ���������
	m_pFrame	= nullptr;	// �t���[�����
	m_pName		= nullptr;	// ���O���
	m_pStatus	= nullptr;	// �X�e�[�^�X���

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

	// ���O�̐���
	m_pName = CString2D::Create
	( // ����
		name::FONT,		// �t�H���g�p�X
		name::ITALIC,	// �C�^���b�N
		L"���Ղ���",	// �w�蕶����	// TODO�F���O�̕ۑ��V�X�e�����쐬
		name::POS,		// ���_�ʒu
		name::HEIGHT,	// �����c��
		name::ALIGN_X,	// ���z�u
		name::ROT,		// ���_����
		name::COL		// �F
	);
	if (m_pName == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// ���x����UI�ɐݒ�
	m_pName->SetLabel(CObject::LABEL_UI);

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

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// TODO�F�X�e�[�^�X�̎擾
#if 1
	m_pStatus->AddString(L"LV 1");
	m_pStatus->AddString(L"HP 20/20");
	m_pStatus->AddString(L"G  0");
#endif

	// ���x����UI�ɐݒ�
	m_pStatus->SetLabel(CObject::LABEL_UI);

	// �D�揇�ʂ�ݒ�
	m_pStatus->SetPriority(PRIORITY);

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CMenuStatusUI::Uninit(void)
{
	// �t���[���̏I��
	SAFE_UNINIT(m_pFrame);

	// ���O�̏I��
	SAFE_UNINIT(m_pName);

	// �X�e�[�^�X�̏I��
	SAFE_UNINIT(m_pStatus);

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
void CMenuStatusUI::Draw(CShader * /*pShader*/)
{

}

//============================================================
//	��������
//============================================================
CMenuStatusUI *CMenuStatusUI::Create(void)
{
	// �X�e�[�^�X���j���[�̐���
	CMenuStatusUI *pMenuStatusUI = new CMenuStatusUI;
	if (pMenuStatusUI == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �X�e�[�^�X���j���[�̏�����
		if (FAILED(pMenuStatusUI->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �X�e�[�^�X���j���[�̔j��
			SAFE_DELETE(pMenuStatusUI);
			return nullptr;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return pMenuStatusUI;
	}
}
