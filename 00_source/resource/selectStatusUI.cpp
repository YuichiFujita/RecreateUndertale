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
	const char *PASS = "data\\TEXT\\start.txt";	// �e�L�X�g�p�X	// TODO�F�p�X�ǂ������邩
	const int PRIORITY = 6;	// �t���X�e�[�^�X���j���[�̗D�揇��

	namespace frame
	{
		const D3DXVECTOR3 POS	= D3DXVECTOR3(555.0f, 386.5f, 0.0f);	// �t���[���ʒu
		const D3DXVECTOR3 ROT	= VEC3_ZERO;							// �t���[������
		const D3DXVECTOR3 SIZE	= D3DXVECTOR3(525.0f, 600.0f, 0.0f);	// �t���[���傫��
	}

	namespace name
	{
		const char	*FONT = "data\\FONT\\JF�h�b�g���_�S�V�b�N14.ttf";	// �t�H���g�p�X
		const bool	ITALIC = false;	// �C�^���b�N
		const float	HEIGHT = 42.0f;	// �����c��

		const CString2D::EAlignX ALIGN_X = CString2D::XALIGN_LEFT;		// ���z�u
		const D3DXVECTOR3	POS = D3DXVECTOR3(320.0f, 140.0f, 0.0f);	// �ʒu
		const D3DXVECTOR3	ROT = VEC3_ZERO;	// ����
		const D3DXCOLOR		COL = XCOL_WHITE;	// �F
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

	// ���O�̐���
	m_pName = CString2D::Create
	( // ����
		name::FONT,		// �t�H���g�p�X
		name::ITALIC,	// �C�^���b�N
		L"",			// �w�蕶����
		name::POS,		// ���_�ʒu
		name::HEIGHT,	// �����c��
		name::ALIGN_X,	// ���z�u
		name::ROT,		// ���_����
		name::COL		// �F
	);

	// �D�揇�ʂ�ݒ�
	m_pName->SetPriority(PRIORITY);

	// TODO�F�������Ȃ��H
	std::wstring str;
	str.append(L"\"");
	str.append(L"���Ղ���");
	str.append(L"\"");
	m_pName->SetString(str);

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
