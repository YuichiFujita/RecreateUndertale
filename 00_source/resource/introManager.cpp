//============================================================
//
//	�C���g���}�l�[�W���[���� [introManager.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "introManager.h"
#include "manager.h"
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

	namespace story
	{
		const char *TEXTURE[] =	// ����̃e�N�X�`��
		{
			"data\\TEXTURE\\story000.png",	// �ނ����ނ���
			"data\\TEXTURE\\story001.png",	// �Ƃ��낪����Ƃ�
			"data\\TEXTURE\\story002.png",	// �j���Q�����傤��
			"data\\TEXTURE\\story003.png",	// �����ɂƂ����߂܂���
			"data\\TEXTURE\\story004.png",	// �Ȃ����Ƃ����Ȃ���
			"data\\TEXTURE\\story005.png",	// �C�r�g�R
			"data\\TEXTURE\\story006.png",	// �ł񂹂̎R
			"data\\TEXTURE\\story007.png",	// �����낵
			"data\\TEXTURE\\story008.png",	// �����|����
			"data\\TEXTURE\\story009.png",	// ����
			"data\\TEXTURE\\story010.png",	// ���n
		};

		const D3DXVECTOR3 POS	= D3DXVECTOR3(SCREEN_CENT.x, 225.0f, 0.0f);	// �X�g�[���[�ʒu
		const D3DXVECTOR3 SIZE	= D3DXVECTOR3(605.0f, 302.5f, 0.0f);		// �X�g�[���[�傫��
	}

	namespace text
	{
#if 1
		const wchar_t *TEXT[][3] =	// ����̃e�L�X�g
		{
			{
				L"�ނ����ނ����@�����イ�ɂ�",
				L"�j���Q���Ɓ@�����X�^�[�Ƃ���",
				L"2�̂��ゼ�����@���܂����B",
			},
			{
				L"�ނ����ނ����@�����イ�ɂ�",
				L"�j���Q���Ɓ@�����X�^�[�Ƃ���",
				L"2�̂��ゼ�����@���܂����B",
			},
			{
				L"�ނ����ނ����@�����イ�ɂ�",
				L"�j���Q���Ɓ@�����X�^�[�Ƃ���",
				L"2�̂��ゼ�����@���܂����B",
			},
			{
				L"�ނ����ނ����@�����イ�ɂ�",
				L"�j���Q���Ɓ@�����X�^�[�Ƃ���",
				L"2�̂��ゼ�����@���܂����B",
			},
			{
				L"�ނ����ނ����@�����イ�ɂ�",
				L"�j���Q���Ɓ@�����X�^�[�Ƃ���",
				L"2�̂��ゼ�����@���܂����B",
			},
			{
				L"�ނ����ނ����@�����イ�ɂ�",
				L"�j���Q���Ɓ@�����X�^�[�Ƃ���",
				L"2�̂��ゼ�����@���܂����B",
			},
			{
				L"�ނ����ނ����@�����イ�ɂ�",
				L"�j���Q���Ɓ@�����X�^�[�Ƃ���",
				L"2�̂��ゼ�����@���܂����B",
			},
			{
				L"�ނ����ނ����@�����イ�ɂ�",
				L"�j���Q���Ɓ@�����X�^�[�Ƃ���",
				L"2�̂��ゼ�����@���܂����B",
			},
			{
				L"�ނ����ނ����@�����イ�ɂ�",
				L"�j���Q���Ɓ@�����X�^�[�Ƃ���",
				L"2�̂��ゼ�����@���܂����B",
			},
			{
				L"�ނ����ނ����@�����イ�ɂ�",
				L"�j���Q���Ɓ@�����X�^�[�Ƃ���",
				L"2�̂��ゼ�����@���܂����B",
			},
			{
				L"�ނ����ނ����@�����イ�ɂ�",
				L"�j���Q���Ɓ@�����X�^�[�Ƃ���",
				L"2�̂��ゼ�����@���܂����B",
			},
		};
#endif

		const char *FONT = "data\\FONT\\JF�h�b�g���_�S�V�b�N14.ttf";	// �t�H���g�p�X
		const bool	ITALIC		= false;	// �C�^���b�N
		const float	WAIT_TIME	= 0.12f;	// �����\���̑ҋ@����
		const float	CHAR_HEIGHT	= 45.0f;	// �����c��
		const float	LINE_HEIGHT	= 62.0f;	// �s�ԏc��

		const D3DXVECTOR3 POS = D3DXVECTOR3(SCREEN_CENT.x - story::SIZE.x * 0.5f, 460.0f, 0.0f);	// �e�L�X�g�ʒu
		const CString2D::EAlignX ALIGN_X = CString2D::XALIGN_LEFT;	// ���z�u
		const CText2D::EAlignY ALIGN_Y = CText2D::YALIGN_TOP;		// �c�z�u
	}
}

//************************************************************
//	�e�N���X [CIntroManager] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CIntroManager::CIntroManager() :
	m_pLogo		(nullptr),		// �^�C�g�����S
	m_pFade		(nullptr),		// �t�F�[�h
	m_pStory	(nullptr),		// �X�g�[���[
	m_pText		(nullptr),		// �e�L�X�g
	m_state		(STATE_LOGO),	// ���
	m_nStory	(0),			// ����C���f�b�N�X
	m_fCurTime	(0.0f)			// ���݂̑ҋ@����
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CIntroManager::~CIntroManager()
{

}

//============================================================
//	����������
//============================================================
HRESULT CIntroManager::Init(void)
{
	// �����o�ϐ���������
	m_pLogo		= nullptr;		// �^�C�g�����S
	m_pFade		= nullptr;		// �t�F�[�h
	m_pStory	= nullptr;		// �X�g�[���[
	m_pText		= nullptr;		// �e�L�X�g
	m_state		= STATE_LOGO;	// ���
	m_nStory	= 0;			// ����C���f�b�N�X
	m_fCurTime	= 0.0f;			// ���݂̑ҋ@����

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

	// �X�g�[���[�̐���
	m_pStory = CScroll2D::Create(0.0f, 0.0f, story::POS, story::SIZE);
	if (m_pStory == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �e�N�X�`����o�^�E����
	m_pStory->BindTexture(story::TEXTURE[0]);

	// �D�揇�ʂ�ݒ�
	m_pStory->SetPriority(PRIORITY);

	// �����`���OFF�ɂ���
	m_pStory->SetEnableDraw(false);

	// �t�F�[�h�̐���
	m_pFade = CObject2D::Create(story::POS, story::SIZE, VEC3_ZERO, XCOL_ABLACK);
	if (m_pFade == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	m_pFade->SetPriority(PRIORITY);

	// �e�L�X�g�̐���
	m_pText = CScrollText2D::Create
	( // ����
		text::FONT,			// �t�H���g�p�X
		text::ITALIC,		// �C�^���b�N
		text::POS,			// ���_�ʒu
		text::WAIT_TIME,	// �����\���̑ҋ@����
		text::CHAR_HEIGHT,	// �����c��
		text::LINE_HEIGHT,	// �s�ԏc��
		text::ALIGN_X,		// ���z�u
		text::ALIGN_Y		// �c�z�u
	);
	if (m_pText == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	for (int i = 0; i < 3; i++)
	{
		// �������ݒ�
		m_pText->AddString(text::TEXT[0][i]);
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CIntroManager::Uninit(void)
{
	// �^�C�g�����S�̏I��
	SAFE_UNINIT(m_pLogo);

	// �t�F�[�h�̏I��
	SAFE_UNINIT(m_pFade);

	// �X�g�[���[�̏I��
	SAFE_UNINIT(m_pStory);
}

//============================================================
//	�X�V����
//============================================================
void CIntroManager::Update(const float fDeltaTime)
{
	switch (m_state)
	{ // ��Ԃ��Ƃ̏���
	case STATE_LOGO:	// ���S�\��

		if (WaitTime(fDeltaTime, 0.0f))
		{ // �ҋ@�I�������ꍇ

			// �^�C�g�����S�̎����`���OFF�ɂ���
			m_pLogo->SetEnableDraw(false);

			// �X�g�[���[�̎����`���ON�ɂ���
			m_pStory->SetEnableDraw(true);

			// ����������J�n����
			m_pText->SetEnableScroll(true);

			// ���������Ԃɂ���
			m_state = STATE_TEXT;
		}

		break;

	case STATE_TEXT:	// ��������

		if (!m_pText->IsScroll())
		{ // �������肪�I�������ꍇ

			// �ҋ@��Ԃɂ���
			m_state = STATE_WAIT;
		}

		break;

	case STATE_WAIT:	// �ҋ@

		if (WaitTime(fDeltaTime, 2.0f))
		{ // �ҋ@�I�������ꍇ

			// �t�F�[�h�C����Ԃɂ���
			m_state = STATE_FADEIN;
		}

		break;

	case STATE_FADEIN:	// �t�F�[�h�C��
	{
		D3DXCOLOR colFade = m_pFade->GetColor();	// �t�F�[�h�F
		colFade.a += 0.05f;
		m_pFade->SetColor(colFade);

		if (colFade.a >= 1.0f)
		{ // �t�F�[�h�d�؂����ꍇ

			// ����Ə�Ԃ�J�ڂ�����
			NextStory();
		}

		break;
	}
	case STATE_FADEOUT:	// �t�F�[�h�A�E�g
	{
		D3DXCOLOR colFade = m_pFade->GetColor();	// �t�F�[�h�F
		colFade.a -= 0.05f;
		m_pFade->SetColor(colFade);

		if (colFade.a <= 0.0f)
		{ // �t�F�[�h�d�؂����ꍇ

			// ���������Ԃɂ���
			m_state = STATE_TEXT;
		}

		break;
	}
	case STATE_END:		// �I��

		// �^�C�g���Ƀ��[�h�����J��
		GET_MANAGER->SetScene(CScene::MODE_TITLE);

		break;

	default:
		assert(false);
		break;
	}
}

//============================================================
//	��������
//============================================================
CIntroManager *CIntroManager::Create(void)
{
	// �C���g���}�l�[�W���[�̐���
	CIntroManager *pIntroManager = new CIntroManager;
	if (pIntroManager == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �C���g���}�l�[�W���[�̏�����
		if (FAILED(pIntroManager->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �C���g���}�l�[�W���[�̔j��
			SAFE_DELETE(pIntroManager);
			return nullptr;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return pIntroManager;
	}
}

//============================================================
//	�j������
//============================================================
void CIntroManager::Release(CIntroManager *&prIntroManager)
{
	// �C���g���}�l�[�W���[�̏I��
	assert(prIntroManager != nullptr);
	prIntroManager->Uninit();

	// �������J��
	SAFE_DELETE(prIntroManager);
}

//============================================================
//	����̑J�ڏ���
//============================================================
void CIntroManager::NextStory(void)
{
	// ��������ɐi�߂�
	m_nStory++;
	if (useful::LimitMaxNum(m_nStory, (int)STORY_MAX - 1))
	{ // �Ō�܂ŕ\�������ꍇ

		// �I����Ԃɂ���
		m_state = STATE_END;
	}
	else
	{ // �܂��\���ł���ꍇ

		// ����̉摜�������ւ�
		m_pStory->BindTexture(story::TEXTURE[m_nStory]);

		// ����������J�n����
		m_pText->SetEnableDraw(false);	// TODO
		m_pText->SetEnableScroll(true);

		// �t�F�[�h�A�E�g��Ԃɂ���
		m_state = STATE_FADEOUT;
	}
}

//============================================================
//	�ҋ@���Ԃ̊Ǘ�����
//============================================================
bool CIntroManager::WaitTime(const float fDeltaTime, const float fDestTime)
{
	// �ҋ@������i�߂�
	m_fCurTime += fDeltaTime;
	if (m_fCurTime >= fDestTime)
	{ // �ҋ@�I�������ꍇ

		// �ҋ@���Ԃ�������
		m_fCurTime = 0.0f;

		return true;
	}

	return false;
}
