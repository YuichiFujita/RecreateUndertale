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
#include "introState.h"
#include "introFade.h"
#include "loadtext.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
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

		const int	PRIORITY		= 4;		// ����\���|���S���̗D�揇��
		const float	SCROLL_MOVE		= -0.002f;	// �X�N���[���̈ړ���
		const float	SCROLL_OFFSET	= 0.324f;	// �X�N���[���|���S���̃e�N�X�`���I�t�Z�b�g

		const float	WAIT_TIME_DISP		= 5.5f;	// ����J�ڂ̑ҋ@���� (�\���̂�)
		const float	WAIT_TIME_SCROLL	= 5.5f;	// ����J�ڂ̑ҋ@���� (�X�N���[��)

		const D3DXVECTOR3 POS	= D3DXVECTOR3(SCREEN_CENT.x, 225.0f, 0.0f);	// �X�g�[���[�ʒu
		const D3DXVECTOR3 SIZE	= D3DXVECTOR3(605.0f, 302.5f, 0.0f);		// �X�g�[���[�傫��
	}

	namespace text
	{
		const char *FONT = "data\\FONT\\JF�h�b�g���_�S�V�b�N14.ttf";	// �t�H���g�p�X
		const char *PASS = "data\\TEXT\\intro.txt";	// �e�L�X�g�p�X

		const int	PRIORITY	= 6;		// �e�L�X�g�̗D�揇��
		const bool	ITALIC		= false;	// �C�^���b�N
		const float	CHAR_HEIGHT	= 45.0f;	// �����c��
		const float	LINE_HEIGHT	= 62.0f;	// �s�ԏc��

		const float	WAIT_TIME_NOR	= 0.115f;	// �����\���̑ҋ@���� (�ʏ푬�x)
		const float	WAIT_TIME_SLOW	= 0.7f;		// �����\���̑ҋ@���� (���x�ቺ)

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
	m_pStory	(nullptr),	// �X�g�[���[
	m_pText		(nullptr),	// �e�L�X�g
	m_pState	(nullptr),	// ���
	m_nStoryID	(0)			// ����C���f�b�N�X
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
	m_pStory	= nullptr;	// �X�g�[���[
	m_pText		= nullptr;	// �e�L�X�g
	m_pState	= nullptr;	// ���
	m_nStoryID	= 0;		// ����C���f�b�N�X

	// ���S�\����Ԃɂ���
	ChangeState(new CIntroStateLogo);

	//--------------------------------------------------------
	//	�X�g�[���[�̐����E�ݒ�
	//--------------------------------------------------------
	// �X�g�[���[�̐���
	m_pStory = CScroll2D::Create(0.0f, 0.0f, story::POS, story::SIZE);
	if (m_pStory == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// ���x����UI�ɐݒ�
	m_pStory->SetLabel(CObject::LABEL_UI);

	// �D�揇�ʂ�ݒ�
	m_pStory->SetPriority(story::PRIORITY);

	//--------------------------------------------------------
	//	�e�L�X�g�̐����E�ݒ�
	//--------------------------------------------------------
	// �e�L�X�g�̐���
	m_pText = CScrollText2D::Create
	( // ����
		text::FONT,				// �t�H���g�p�X
		text::ITALIC,			// �C�^���b�N
		text::POS,				// ���_�ʒu
		text::WAIT_TIME_NOR,	// �����\���̑ҋ@����
		text::CHAR_HEIGHT,		// �����c��
		text::LINE_HEIGHT,		// �s�ԏc��
		text::ALIGN_X,			// ���z�u
		text::ALIGN_Y			// �c�z�u
	);
	if (m_pText == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ��t�F�[�h����ɂ���
	m_pText->SetPriority(text::PRIORITY);

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CIntroManager::Uninit(void)
{
	// ��Ԃ̏I��
	SAFE_UNINIT(m_pState);
}

//============================================================
//	�X�V����
//============================================================
void CIntroManager::Update(const float fDeltaTime)
{
	// ��Ԃ��Ƃ̍X�V
	assert(m_pState != nullptr);
	m_pState->Update(fDeltaTime);
}

//============================================================
//	��Ԃ̕ύX����
//============================================================
HRESULT CIntroManager::ChangeState(CIntroState *pState)
{
	// ��Ԃ̐����Ɏ��s���Ă���ꍇ������
	if (pState == nullptr) { assert(false); return E_FAIL; }

	// ��ԃC���X�^���X���I��
	SAFE_UNINIT(m_pState);

	// ��ԃC���X�^���X��ύX
	assert(m_pState == nullptr);
	m_pState = pState;

	// ��ԃC���X�^���X��������
	if (FAILED(m_pState->Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// ��ԂɃR���e�L�X�g��ݒ�
	m_pState->SetContext(this);

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	����̑J�ڏ���
//============================================================
void CIntroManager::NextStory(void)
{
	// ��������ɐi�߂�
	m_nStoryID++;

	// �t�F�[�h�𐶐�����
	CIntroFade::Create(this);

	switch (m_nStoryID)
	{ // ���ꂲ�Ƃ̏���
	case STORY_00:	// �ނ����ނ���
	case STORY_01:	// �Ƃ��낪����Ƃ�
	case STORY_02:	// �j���Q�����傤��
	case STORY_03:	// �����ɂƂ����߂܂���
	case STORY_05:	// �C�r�g�R
	case STORY_06:	// �ł񂹂̎R

		// �\���e�L�X�g��ύX����
		ChangeText(m_nStoryID);

		// ���������Ԃɂ���
		ChangeState(new CIntroStateText);

		break;

	case STORY_04:	// �Ȃ����Ƃ����Ȃ���

		// �\���e�L�X�g��ύX����
		ChangeText(m_nStoryID);

		// �������葬�x�ቺ��Ԃɂ���
		ChangeState(new CIntroStateTextSlow);

		break;

	case STORY_07:	// �����낵
	case STORY_08:	// �����|����
	case STORY_09:	// ����

		// �������S�č폜
		m_pText->DeleteStringAll();

		// �ҋ@��Ԃɂ���
		ChangeState(new CIntroStateWait(story::WAIT_TIME_DISP));

		break;

	case STORY_10:	// ���n

		// �������S�č폜
		m_pText->DeleteStringAll();

		// �ҋ@��Ԃɂ���
		ChangeState(new CIntroStateWait(story::WAIT_TIME_SCROLL));

		break;
	}
}

//============================================================
//	�X�g�[���[�ύX����
//============================================================
void CIntroManager::ChangeStory(const int nStoryID)
{
	// ����̉摜�������ւ�
	m_pStory->BindTexture(story::TEXTURE[nStoryID]);

	if (nStoryID == STORY_MAX - 1)
	{ // �Ō�̕���̏ꍇ

		// �e�N�X�`���̊J�n�n�_�ɂ���
		m_pStory->SetOffsetV(story::SCROLL_OFFSET);		// �I�t�Z�b�g��ݒ�
		m_pStory->SetTexV(1.0f - story::SCROLL_OFFSET);	// �e�N�X�`�����W��ݒ�
	}
}

//============================================================
//	�e�L�X�g�ύX����
//============================================================
void CIntroManager::ChangeText(const int nStoryID)
{
	// �������S�č폜
	m_pText->DeleteStringAll();

	// ���̃e�L�X�g������
	loadtext::BindText(m_pText, loadtext::LoadText(text::PASS, nStoryID));

	// ����������J�n����
	m_pText->SetEnableScroll(true);
}

//============================================================
//	�X�g�[���[�X�N���[���̊J�n
//============================================================
void CIntroManager::StartScrollStory(void)
{
	// ����̃X�N���[�����J�n����
	m_pStory->SetMoveV(story::SCROLL_MOVE);
}

//============================================================
//	�X�g�[���[�X�N���[���̐��K��
//============================================================
bool CIntroManager::NormalizeScrollStory(void)
{
	if (m_pStory->GetNumLoopV() >= 1)
	{ // �e�N�X�`�����������[�v�����ꍇ

		// �e�N�X�`���̏I���n�_�Œ�~
		m_pStory->SetMoveV(0.0f);	// �ړ��ʂ�������
		m_pStory->SetTexV(1.0f);	// �e�N�X�`�����W��␳

		return true;
	}

	return false;
}

//============================================================
//	��������̑��x�ݒ菈��
//============================================================
void CIntroManager::SetEnableSlowText(const bool bSlow)
{
	// ���x�t���O�ɉ����Đݒ�
	if (bSlow)	{ m_pText->SetNextTime(text::WAIT_TIME_SLOW); }	// �x������
	else		{ m_pText->SetNextTime(text::WAIT_TIME_NOR); }	// ��������
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
