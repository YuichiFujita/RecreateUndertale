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
#include "introState.h"

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
				L"�Ƃ��낪�@����Ƃ�",
				L"2�̂��ゼ���́@��������",
				L"���񂻂����@�����܂����B",
			},
			{
				L"�����ā@�Ȃ���",
				L"���������̂����@�j���Q����",
				L"���傤�肵�܂����B",
			},
			{
				L"�j���Q���́@�܂ق��̂������",
				L"�����X�^�[������",
				L"�����Ɂ@�Ƃ����߂܂����B",
			},
			{
				L"���ꂩ��@�����",
				L"�Ȃ����@�Ƃ����@�Ȃ���c�c�c",
				L"",
			},
			{
				L"�@�@�@�@�C�r�g�R",
				L"�@�@�@�@�@ 201X�N",
				L"",
			},
			{
				L"����́u�̂ڂ������̂�",
				L"�ɂǂƁ@���ǂ�Ȃ��v�Ƃ�����",
				L"�ł񂹂̎R�ł����B",
			},
			{ L"", L"", L"", },
			{ L"", L"", L"", },
			{ L"", L"", L"", },
			{ L"", L"", L"", },
		};
#endif

		const char *FONT = "data\\FONT\\JF�h�b�g���_�S�V�b�N14.ttf";	// �t�H���g�p�X
		const bool	ITALIC		= false;	// �C�^���b�N
		const float	WAIT_TIME	= 0.115f;	// �����\���̑ҋ@����
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
	m_pFade		(nullptr),		// �t�F�[�h
	m_pStory	(nullptr),		// �X�g�[���[
	m_pText		(nullptr),		// �e�L�X�g
	m_pState	(nullptr),		// ���
	m_fade		(FADE_NONE),	// �t�F�[�h��
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
	m_pFade		= nullptr;		// �t�F�[�h
	m_pStory	= nullptr;		// �X�g�[���[
	m_pText		= nullptr;		// �e�L�X�g
	m_pState	= nullptr;		// ���
	m_fade		= FADE_NONE;	// �t�F�[�h��
	m_nStory	= 0;			// ����C���f�b�N�X
	m_fCurTime	= 0.0f;			// ���݂̑ҋ@����

	// ���S�\����Ԃɂ���
	ChangeState(new CIntroStateLogo(this));

	// �X�g�[���[�̐���
#if 1
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
#endif

	// �t�F�[�h�̐���
#if 1
	m_pFade = CObject2D::Create(story::POS, story::SIZE, VEC3_ZERO, XCOL_ABLACK);
	if (m_pFade == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	m_pFade->SetPriority(PRIORITY);
#endif

	// �e�L�X�g�̐���
#if 1
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
#endif

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CIntroManager::Uninit(void)
{
	// ��Ԃ̔j��
	SAFE_DELETE(m_pState);

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
	// �t�F�[�h�̍X�V
	UpdateFade();

	// ��Ԃ��Ƃ̍X�V
	m_pState->Update(fDeltaTime);
}

//============================================================
//	��Ԃ̕ύX����
//============================================================
HRESULT CIntroManager::ChangeState(CIntroState *pState)
{
	// ��Ԃ̐����Ɏ��s���Ă���ꍇ������
	if (pState == nullptr) { assert(false); return E_FAIL; }

	// ���g�̃C���X�^���X���I��
	SAFE_UNINIT(m_pState);

	// ���g�̃C���X�^���X��ύX
	assert(m_pState == nullptr);
	m_pState = pState;

	// ���g�̃C���X�^���X��������
	if (FAILED(m_pState->Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
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
		ChangeState(new CIntroStateEnd(this));
	}
	else
	{ // �܂��\���ł���ꍇ

		// ����������ׂĔj��
		m_pText->DeleteStringAll();

		// ���̕�����ɒu��
		for (int i = 0; i < 3; i++)
		{
			// �������ݒ�
			m_pText->AddString(text::TEXT[m_nStory][i]);
		}

		// ����������J�n����
		m_pText->SetEnableScroll(true);

		// �t�F�[�h���J�n����
		m_fade = FADE_IN;

		// ���������Ԃɂ���
		ChangeState(new CIntroStateText(this));
	}
}

//============================================================
//	�t�F�[�h�X�V����
//============================================================
void CIntroManager::UpdateFade(void)
{
	switch (m_fade)
	{ // �t�F�[�h��Ԃ��Ƃ̏���
	case FADE_NONE:	// �t�F�[�h����
	{
		break;
	}
	case FADE_IN:	// �t�F�[�h�C��
	{
		D3DXCOLOR colFade = m_pFade->GetColor();	// �t�F�[�h�F
		colFade.a += 0.04f;
		m_pFade->SetColor(colFade);

		if (colFade.a >= 1.0f)
		{ // �t�F�[�h�d�؂����ꍇ

			// ����̉摜�������ւ�
			m_pStory->BindTexture(story::TEXTURE[m_nStory]);

			// �t�F�[�h�A�E�g��Ԃɂ���
			m_fade = FADE_OUT;
		}

		break;
	}
	case FADE_OUT:	// �t�F�[�h�A�E�g
	{
		D3DXCOLOR colFade = m_pFade->GetColor();	// �t�F�[�h�F
		colFade.a -= 0.04f;
		m_pFade->SetColor(colFade);

		if (colFade.a <= 0.0f)
		{ // �t�F�[�h�d�؂����ꍇ

			// �t�F�[�h������Ԃɂ���
			m_fade = FADE_NONE;
		}

		break;
	}
	default:
		assert(false);
		break;
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
