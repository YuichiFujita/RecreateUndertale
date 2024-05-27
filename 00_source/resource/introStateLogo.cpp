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
	const int PRIORITY = 6;	// �C���g���̗D�揇��

	namespace logo
	{
		const char *TEXTURE		= "data\\TEXTURE\\logoIntro000.png";	// �^�C�g�����S�e�N�X�`��
		const D3DXVECTOR3 POS	= SCREEN_CENT;	// �^�C�g�����S�ʒu
		const D3DXVECTOR3 SIZE	= SCREEN_SIZE;	// �^�C�g�����S�傫��
	}
}

//************************************************************
//	�q�N���X [CIntroStateLogo] �̃����o�֐�
//************************************************************
//============================================================
//	����������
//============================================================
HRESULT CIntroStateLogo::Init(void)
{
	// �����o�ϐ���������
	m_pLogo = nullptr;	// �^�C�g�����S

	// �^�C�g�����S�̐���
	m_pLogo = CObject2D::Create(logo::POS, logo::SIZE);
	if (m_pLogo == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �e�N�X�`����o�^�E����
	m_pLogo->BindTexture(logo::TEXTURE);

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
	if (m_pIntro->WaitTime(fDeltaTime, 4.0f))
	{ // �ҋ@�I�������ꍇ

		// �X�g�[���[�̎����`���ON�ɂ���
		m_pIntro->m_pStory->SetEnableDraw(true);

		// ����������J�n����
		m_pIntro->m_pText->SetEnableScroll(true);

		// ���������Ԃɂ���
		m_pIntro->ChangeState(new CIntroStateText(m_pIntro));
	}
}
