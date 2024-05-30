//============================================================
//
//	���S�\����ԏ��� [introStateLogo.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "introStateLogo.h"
#include "introManager.h"
#include "object2D.h"
#include "scroll2D.h"
#include "scrollText2D.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const char *TEXTURE		= "data\\TEXTURE\\logoIntro000.png";	// ���S�e�N�X�`��
	const int	PRIORITY	= 6;	// �D�揇��
	const float	DISP_TIME	= 4.0f;	// �^�C�g�����S�\������
}

//************************************************************
//	�q�N���X [CIntroStateLogo] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CIntroStateLogo::CIntroStateLogo() :
	m_pLogo		(nullptr),	// �^�C�g�����S
	m_fCurTime	(0.0f)		// ���݂̑ҋ@����
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CIntroStateLogo::~CIntroStateLogo()
{

}

//============================================================
//	����������
//============================================================
HRESULT CIntroStateLogo::Init(void)
{
	// �����o�ϐ���������
	m_pLogo		= nullptr;	// �^�C�g�����S
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
void CIntroStateLogo::Uninit(void)
{
	// �^�C�g�����S�̏I��
	SAFE_UNINIT(m_pLogo);

	// ���g�̔j��
	delete this;
}

//============================================================
//	�X�V����
//============================================================
void CIntroStateLogo::Update(const float fDeltaTime)
{
	// �ҋ@������i�߂�
	m_fCurTime += fDeltaTime;
	if (m_fCurTime >= DISP_TIME)
	{ // �ҋ@�I�������ꍇ

		// �ҋ@���Ԃ�������
		m_fCurTime = 0.0f;

		// �X�g�[���[�̎����`���ON�ɂ���
		m_pContext->m_pStory->SetEnableDraw(true);

		// ����������J�n����
		m_pContext->m_pText->SetEnableScroll(true);

		// ���������Ԃɂ���
		m_pContext->ChangeState(new CIntroStateText);
	}
}
