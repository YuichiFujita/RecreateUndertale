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

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const int PRIORITY = 6;	// �D�揇��

	namespace virsion
	{
		const char		*FONT = "data\\FONT\\Crypt of Tomorrow.ttf";	// �t�H���g�p�X
		const wchar_t	*STRING = L"UNDERTALE_REPRISE V1.00 (C) OPUGST 2024-20XX";	// �\��������
		const bool		ITALIC = false;	// �C�^���b�N
		const float		HEIGHT = 22.5f;	// �����c��

		const CString2D::EAlignX ALIGN_X = CString2D::XALIGN_CENTER;		// ���z�u
		const D3DXCOLOR   COL = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);			// �F
		const D3DXVECTOR3 POS = D3DXVECTOR3(SCREEN_CENT.x, 706.0f, 0.0f);	// �ʒu
		const D3DXVECTOR3 ROT = VEC3_ZERO;	// ����
	}
}

//************************************************************
//	�q�N���X [CStartStateTutorial] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CStartStateTutorial::CStartStateTutorial() :
	m_pVersion	(nullptr)	// �o�[�W�����\�L
{

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
	m_pVersion = nullptr;	// �o�[�W�����\�L

	// �o�[�W�����\�L�̐���
	m_pVersion = CString2D::Create
	( // ����
		virsion::FONT,		// �t�H���g�p�X
		virsion::ITALIC,	// �C�^���b�N
		virsion::STRING,	// �w�蕶����
		virsion::POS,		// ���_�ʒu
		virsion::HEIGHT,	// �����c��
		virsion::ALIGN_X,	// ���z�u
		virsion::ROT,		// ���_����
		virsion::COL		// �F
	);

	// �D�揇�ʂ�ݒ�
	m_pVersion->SetPriority(PRIORITY);

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
