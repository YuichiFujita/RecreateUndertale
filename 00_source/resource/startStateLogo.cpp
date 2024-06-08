//============================================================
//
//	���S�\����ԏ��� [startStateLogo.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "startStateLogo.h"
#include "startManager.h"
#include "manager.h"
#include "object2D.h"
#include "string2D.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const char *TEXTURE		= "data\\TEXTURE\\logo000.png";	// ���S�e�N�X�`��
	const int	PRIORITY	= 6;	// �D�揇��
	const float	DISP_TIME	= 3.0f;	// ���S�\������

	namespace str
	{
		const char		*FONT	= "data\\FONT\\Crypt of Tomorrow.ttf";	// �t�H���g�p�X
		const wchar_t	*STRING	= L"[PRESS Z OR ENTER]";	// �\��������
		const bool		ITALIC	= false;	// �C�^���b�N
		const float		HEIGHT	= 22.5f;	// �����c��

		const CString2D::EAlignX ALIGN_X = CString2D::XALIGN_CENTER;		// ���z�u
		const D3DXCOLOR   COL = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);			// �F
		const D3DXVECTOR3 POS = D3DXVECTOR3(SCREEN_CENT.x, 545.0f, 0.0f);	// �ʒu
		const D3DXVECTOR3 ROT = VEC3_ZERO;	// ����
	}
}

//************************************************************
//	�q�N���X [CStartStateLogo] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CStartStateLogo::CStartStateLogo() :
	m_pLogo		(nullptr),	// �^�C�g�����S
	m_pCont		(nullptr),	// �������
	m_fCurTime	(0.0f)		// ���݂̑ҋ@����
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CStartStateLogo::~CStartStateLogo()
{

}

//============================================================
//	����������
//============================================================
HRESULT CStartStateLogo::Init(void)
{
	// �����o�ϐ���������
	m_pLogo		= nullptr;	// �^�C�g�����S
	m_pCont		= nullptr;	// �������
	m_fCurTime	= 0.0f;		// ���݂̑ҋ@����

	// �^�C�g�����S�̐���
	m_pLogo = CObject2D::Create(SCREEN_CENT, SCREEN_SIZE);
	if (m_pLogo == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �e�N�X�`����o�^�E����
	m_pLogo->BindTexture(TEXTURE);

	// �D�揇�ʂ�ݒ�
	m_pLogo->SetPriority(PRIORITY);

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CStartStateLogo::Uninit(void)
{
	// �^�C�g�����S�̏I��
	SAFE_UNINIT(m_pLogo);

	// ��������̏I��
	SAFE_UNINIT(m_pCont);

	// ���g�̔j��
	delete this;
}

//============================================================
//	�X�V����
//============================================================
void CStartStateLogo::Update(const float fDeltaTime)
{
	if (m_pCont == nullptr)
	{ // �����������������Ă��Ȃ��ꍇ

		// �ҋ@������i�߂�
		m_fCurTime += fDeltaTime;
		if (m_fCurTime >= DISP_TIME)
		{ // �ҋ@�I�������ꍇ

			// �ҋ@���Ԃ�������
			m_fCurTime = 0.0f;

			// ��������̐���
			m_pCont = CString2D::Create
			( // ����
				str::FONT,		// �t�H���g�p�X
				str::ITALIC,	// �C�^���b�N
				str::STRING,	// �w�蕶����
				str::POS,		// ���_�ʒu
				str::HEIGHT,	// �����c��
				str::ALIGN_X,	// ���z�u
				str::ROT,		// ���_����
				str::COL		// �F
			);

			// �D�揇�ʂ�ݒ�
			m_pCont->SetPriority(PRIORITY);
		}
	}

	// �i�s����
	if (GET_INPUTKEY->IsTrigger(DIK_RETURN) || GET_INPUTKEY->IsTrigger(DIK_Z))
	{
		// �`���[�g���A����Ԃɂ���
		m_pContext->ChangeState(new CStartStateTutorial);
	}
}
