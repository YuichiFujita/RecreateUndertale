//============================================================
//
//	�`���[�g���A���}�l�[�W���[���� [tutorialManager.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "tutorialManager.h"
#include "manager.h"
#include "input.h"
#include "sound.h"
#include "camera.h"
#include "texture.h"
#include "gauge2D.h"
#include "object2D.h"
#include "player.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const char *TEXTURE_FILE[] =	// �e�N�X�`���t�@�C��
	{
		"data\\TEXTURE\\tutorial000.png",	// ������@�\���̃e�N�X�`��
	};
	const char *GUIDE_TEX_FILE[] =	// �������e�N�X�`���t�@�C��
	{
		nullptr,						// ���b�X��00�F�e�N�X�`���Ȃ�
		"data\\TEXTURE\\guide000.png",	// ���b�X��01�F�ړ��E�J����	�������̃e�N�X�`��
		"data\\TEXTURE\\guide001.png",	// ���b�X��02�F�W�����v		�������̃e�N�X�`��
		"data\\TEXTURE\\guide002.png",	// ���b�X��03�F���			�������̃e�N�X�`��
		"data\\TEXTURE\\guide003.png",	// ���b�X��04�F�U��			�������̃e�N�X�`��
		"data\\TEXTURE\\guide004.png",	// ���b�X��05�F�I��			�������̃e�N�X�`��
	};
	const char *CONT_TEX_FILE[] =	// ������@�e�N�X�`���t�@�C��
	{
		nullptr,							// ���b�X��00�F�e�N�X�`���Ȃ�
		"data\\TEXTURE\\control000.png",	// ���b�X��01�F�ړ��E�J����	������@�̃e�N�X�`��
		"data\\TEXTURE\\control001.png",	// ���b�X��02�F�W�����v		������@�̃e�N�X�`��
		"data\\TEXTURE\\control002.png",	// ���b�X��03�F���			������@�̃e�N�X�`��
		"data\\TEXTURE\\control003.png",	// ���b�X��04�F�U��			������@�̃e�N�X�`��
		"data\\TEXTURE\\control004.png",	// ���b�X��05�F�I��			������@�̃e�N�X�`��
	};
	const int NEXT_LESSON[] =		// ���b�X���ڍs�J�E���g
	{
		0,		// ���b�X���Ȃ�
		320,	// ���b�X��01�F�ړ��E�J����	�I���J�E���g
		5,		// ���b�X��02�F�W�����v		�I���J�E���g
		3,		// ���b�X��03�F���			�I���J�E���g
		12,		// ���b�X��04�F�U��			�I���J�E���g
		0,		// ���b�X��05�F�I��			�I���J�E���g
	};
	const int NEXT_LESSON_WAIT[] =	// �����b�X���]�C�J�E���g
	{
		0,		// ���b�X���Ȃ�
		40,		// ���b�X��01�F�ړ��E�J����	�I�����̗]�C�J�E���g
		40,		// ���b�X��02�F�W�����v		�I�����̗]�C�J�E���g
		40,		// ���b�X��03�F���			�I�����̗]�C�J�E���g
		40,		// ���b�X��04�F�U��			�I�����̗]�C�J�E���g
		0,		// ���b�X��05�F�I��			�I�����̗]�C�J�E���g
	};

	const int PRIORITY			= 6;	// �`���[�g���A���̗D�揇��
	const int TITLE_WAIT_CNT	= 20;	// �^�C�g���J�ڂ̗]�C�t���[��

	const D3DXVECTOR3 POS_GUIDE		= D3DXVECTOR3(1020.0f, 585.0f, 0.0f);	// �������\���̈ʒu
	const D3DXVECTOR3 POS_CONTROL	= D3DXVECTOR3(260.0f, 585.0f, 0.0f);	// ������@�\���̈ʒu

	const D3DXVECTOR3 SIZE_PROGRESSION_UI	= D3DXVECTOR3(500.0f, 250.0f, 0.0f);	// �`���[�g���A���i�s����UI�\���̑傫��
	const D3DXCOLOR COL_PROGRESSION_UI_BG	= D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.6f);	// �`���[�g���A���i�s����UI�\���̔w�i�F

	const int FRAME_COUNTER = 10;	// �Q�[�W�̕ϓ��t���[��
	const D3DXVECTOR3 SIZE_COUNTER	= D3DXVECTOR3(SIZE_PROGRESSION_UI.x * 0.5f, 8.0f, 0.0f);	// �Q�[�W�̑傫��
	const D3DXVECTOR3 POS_COUNTER	= D3DXVECTOR3(POS_GUIDE.x, POS_GUIDE.y - (SIZE_PROGRESSION_UI.y * 0.5f) - SIZE_COUNTER.y, 0.0f);	// �Q�[�W�̈ʒu
	const D3DXCOLOR COL_FRONT_COUNTER	= XCOL_WHITE;	// �Q�[�W�̕\�Q�[�W�F
	const D3DXCOLOR COL_BACK_COUNTER	= XCOL_AWHITE;	// �Q�[�W�̗��Q�[�W�F

	const D3DXCOLOR COL_FADE_MIN	= D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	// �t�F�[�h�̃��l�̍ŏ�
	const D3DXCOLOR COL_FADE_MAX	= D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.8f);	// �t�F�[�h�̃��l�̍ő�
	const float FADE_LEVEL = 0.025f;	// �t�F�[�h�̃��l�̉�����

	const D3DXVECTOR3 POS_EXPLAIN	= D3DXVECTOR3(SCREEN_CENT.x, 315.0f, 0.0f);	// �����\���̈ʒu
	const D3DXVECTOR3 SIZE_EXPLAIN	= D3DXVECTOR3(1000.0f, 597.5f, 0.0f);		// �����\���̑傫��
	const float SET_SCALE = 0.05f;	// �g�嗦�̏����l
	const float ADD_SCALE = 0.1f;	// �g�嗦�̉��Z��

	const D3DXVECTOR3 POS_CLOSE		= D3DXVECTOR3(SCREEN_CENT.x, 665.0f, 0.0f);	// ������@�\���̈ʒu
	const D3DXVECTOR3 SIZE_CLOSE	= D3DXVECTOR3(SCREEN_WIDTH, 100.0f, 0.0f);	// ������@�\���̑傫��
	const float ADD_ROT	= 0.02f;	// �_�Ō����̉��Z��
}

//************************************************************
//	�X�^�e�B�b�N�A�T�[�g
//************************************************************
static_assert(NUM_ARRAY(TEXTURE_FILE)		== CTutorialManager::TEXTURE_MAX,	"ERROR : Texture Count Mismatch");
static_assert(NUM_ARRAY(GUIDE_TEX_FILE)		== CTutorialManager::LESSON_MAX,	"ERROR : Lesson Count Mismatch");
static_assert(NUM_ARRAY(CONT_TEX_FILE)		== CTutorialManager::LESSON_MAX,	"ERROR : Lesson Count Mismatch");
static_assert(NUM_ARRAY(NEXT_LESSON)		== CTutorialManager::LESSON_MAX,	"ERROR : Lesson Count Mismatch");
static_assert(NUM_ARRAY(NEXT_LESSON_WAIT)	== CTutorialManager::LESSON_MAX,	"ERROR : Lesson Count Mismatch");

//************************************************************
//	�e�N���X [CTutorialManager] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CTutorialManager::CTutorialManager() :
	m_pCounterLesson	(nullptr),		// ���b�X���Ǘ��J�E���^�[�̏��
	m_pGuide			(nullptr),		// �������\���̏��
	m_pGuideBG			(nullptr),		// �������\���̔w�i���
	m_pControl			(nullptr),		// ������@�\���̏��
	m_pControlBG		(nullptr),		// ������@�\���̔w�i���
	m_state				(STATE_NONE),	// ���
	m_nLesson			(0),			// ���b�X��
	m_nCounterState		(0)				// ��ԊǗ��J�E���^�[
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CTutorialManager::~CTutorialManager()
{

}

//============================================================
//	����������
//============================================================
HRESULT CTutorialManager::Init(void)
{
	// �����o�ϐ���������
	m_pCounterLesson	= nullptr;			// ���b�X���Ǘ��J�E���^�[�̏��
	m_pGuide			= nullptr;			// �������\���̏��
	m_pGuideBG			= nullptr;			// �������\���̔w�i���
	m_pControl			= nullptr;			// ������@�\���̏��
	m_pControlBG		= nullptr;			// ������@�\���̔w�i���
	m_state				= STATE_NEXTWAIT;	// ���
	m_nLesson			= LESSON_NONE;		// ���b�X��
	m_nCounterState		= 0;				// ��ԊǗ��J�E���^�[

	//--------------------------------------------------------
	//	���b�X���Ǘ��J�E���^�[�̐����E�ݒ�
	//--------------------------------------------------------
	// ���b�X���Ǘ��J�E���^�[�̐���
	m_pCounterLesson = CGauge2D::Create
	( // ����
		NEXT_LESSON[0],		// �ő�\���l
		FRAME_COUNTER,		// �\���l�ϓ��t���[��
		POS_COUNTER,		// �ʒu
		SIZE_COUNTER,		// �Q�[�W�傫��
		COL_FRONT_COUNTER,	// �\�Q�[�W�F
		COL_BACK_COUNTER	// ���Q�[�W�F
	);
	if (m_pCounterLesson == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	m_pCounterLesson->SetPriority(PRIORITY);

	//--------------------------------------------------------
	//	�������\���̔w�i�����E�ݒ�
	//--------------------------------------------------------
	// �������\���̔w�i����
	m_pGuideBG = CObject2D::Create
	( // ����
		POS_GUIDE,				// �ʒu
		SIZE_PROGRESSION_UI,	// �傫��
		VEC3_ZERO,				// ����
		COL_PROGRESSION_UI_BG	// �F
	);
	if (m_pGuideBG == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	m_pGuideBG->SetPriority(PRIORITY);

	//--------------------------------------------------------
	//	�������\���̐����E�ݒ�
	//--------------------------------------------------------
	// �������\���̐���
	m_pGuide = CObject2D::Create
	( // ����
		POS_GUIDE,			// �ʒu
		SIZE_PROGRESSION_UI	// �傫��
	);
	if (m_pGuide == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	m_pGuide->SetPriority(PRIORITY);

	//--------------------------------------------------------
	//	������@�\���̔w�i�����E�ݒ�
	//--------------------------------------------------------
	// ������@�\���̔w�i����
	m_pControlBG = CObject2D::Create
	( // ����
		POS_CONTROL,			// �ʒu
		SIZE_PROGRESSION_UI,	// �傫��
		VEC3_ZERO,				// ����
		COL_PROGRESSION_UI_BG	// �F
	);
	if (m_pControlBG == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	m_pControlBG->SetPriority(PRIORITY);

	//--------------------------------------------------------
	//	������@�\���̐����E�ݒ�
	//--------------------------------------------------------
	// ������@�\���̐���
	m_pControl = CObject2D::Create
	( // ����
		POS_CONTROL,		// �ʒu
		SIZE_PROGRESSION_UI	// �傫��
	);
	if (m_pControl == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	m_pControl->SetPriority(PRIORITY);

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CTutorialManager::Uninit(void)
{
	// �������\���̔w�i�I��
	SAFE_UNINIT(m_pGuideBG);

	// �������\���̏I��
	SAFE_UNINIT(m_pGuide);

	// ������@�\���̔w�i�I��
	SAFE_UNINIT(m_pControlBG);

	// ������@�\���̏I��
	SAFE_UNINIT(m_pControl);
}

//============================================================
//	�X�V����
//============================================================
void CTutorialManager::Update(const float fDeltaTime)
{
	switch (m_state)
	{ // ��Ԃ��Ƃ̏���
	case STATE_NONE:		// �������Ȃ����
		break;

	case STATE_NEXTWAIT:	// �����b�X���ҋ@���

		// �����b�X���ҋ@�̍X�V
		UpdateNextWait();

		break;

	case STATE_PROGRESSION:	// �i�s���

		if (m_nLesson == CTutorialManager::LESSON_05)
		{ // ���b�X��05�F���b�X�����I�����Ă���ꍇ

			if (GET_INPUTKEY->IsTrigger(DIK_RETURN)
			||  GET_INPUTPAD->IsTrigger(CInputPad::KEY_START))
			{
				// ���b�X���J�E���^�[���Z
				AddLessonCounter();
			}
		}

		break;

	case STATE_END:			// �I�����

		// �V�[���̐ݒ�
		GET_MANAGER->SetFadeScene(CScene::MODE_TITLE, TITLE_WAIT_CNT);	// �^�C�g�����

		break;

	default:	// ��O����
		assert(false);
		break;
	}

	// �������\���̔w�i�X�V
	m_pGuideBG->Update(fDeltaTime);

	// �������\���̍X�V
	m_pGuide->Update(fDeltaTime);

	// ������@�\���̔w�i�X�V
	m_pControlBG->Update(fDeltaTime);

	// ������@�\���̍X�V
	m_pControl->Update(fDeltaTime);
}

//============================================================
//	���b�X���J�E���^�[�̉��Z����
//============================================================
void CTutorialManager::AddLessonCounter(void)
{
	if (m_nLesson < LESSON_MAX && m_state != STATE_NEXTWAIT)
	{ // ���b�X�����܂����銎�A�����b�X���̑ҋ@���ł͂Ȃ��ꍇ

		// ���b�X���J�E���^�[�����Z
		m_pCounterLesson->AddNum(1);
		if (m_pCounterLesson->GetNum() >= NEXT_LESSON[m_nLesson])
		{ // ���b�X�������ɐi�߂�J�E���g�܂œ��B�����ꍇ

			// ��Ԃ�ݒ�
			m_state = STATE_NEXTWAIT;	// �����b�X���ҋ@���

			// ���艹01�̍Đ�
			PLAY_SOUND(CSound::LABEL_SE_DECISION_001);
		}
	}
}

//============================================================
//	���b�X���擾����
//============================================================
int CTutorialManager::GetLesson(void) const
{
	// ���݂̃��b�X����Ԃ�
	return m_nLesson;
}

//============================================================
//	��Ԏ擾����
//============================================================
CTutorialManager::EState CTutorialManager::GetState(void) const
{
	// ��Ԃ�Ԃ�
	return m_state;
}

//============================================================
//	��������
//============================================================
CTutorialManager *CTutorialManager::Create(void)
{
	// �`���[�g���A���}�l�[�W���[�̐���
	CTutorialManager *pTutorialManager = new CTutorialManager;
	if (pTutorialManager == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �`���[�g���A���}�l�[�W���[�̏�����
		if (FAILED(pTutorialManager->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �`���[�g���A���}�l�[�W���[�̔j��
			SAFE_DELETE(pTutorialManager);
			return nullptr;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return pTutorialManager;
	}
}

//============================================================
//	�j������
//============================================================
void CTutorialManager::Release(CTutorialManager *&prTutorialManager)
{
	// �`���[�g���A���}�l�[�W���[�̏I��
	assert(prTutorialManager != nullptr);
	prTutorialManager->Uninit();

	// �������J��
	SAFE_DELETE(prTutorialManager);
}

//============================================================
//	���b�X���ڍs�J�E���g�擾����
//============================================================
int CTutorialManager::GetNextLessonCounter(const int nID)
{
	if (nID < LESSON_MAX)
	{ // �C���f�b�N�X���͈͓��̏ꍇ

		// �����̃C���f�b�N�X�̃��b�X���ڍs�J�E���g��Ԃ�
		return NEXT_LESSON[nID];
	}
	else { assert(false); return NONE_IDX; }	// �͈͊O
}

//============================================================
//	�i�s��Ԏ��ɕ\������UI�̕`��󋵂̐ݒ菈��
//============================================================
void CTutorialManager::SetEnableProgressionDraw(const bool bDraw)
{
	//--------------------------------------------------------
	//	�����̕`��󋵂�ݒ�
	//--------------------------------------------------------
	// �������\���̔w�i�`��󋵂�ݒ�
	m_pGuideBG->SetEnableDraw(bDraw);

	// �������\���̕`��󋵂�ݒ�
	m_pGuide->SetEnableDraw(bDraw);

	// ������@�\���̔w�i�`��󋵂�ݒ�
	m_pControlBG->SetEnableDraw(bDraw);

	// ������@�\���̕`��󋵂�ݒ�
	m_pControl->SetEnableDraw(bDraw);

	//--------------------------------------------------------
	//	�`��󋵂��󋵂ɉ����ĕύX���Đݒ�
	//--------------------------------------------------------
	bool bDrawControl = bDraw;	// ������@�̕\����
	if (m_nLesson == LESSON_05)
	{ // �Ō�̃��b�X���̏ꍇ

		// ������@��\�����Ȃ���Ԃɂ���
		bDrawControl = false;
	}

	// ���b�X���Ǘ��J�E���^�[�̕`��󋵂�ݒ�
	m_pCounterLesson->SetEnableDraw(bDrawControl);
}

//============================================================
//	�����b�X���ҋ@�̍X�V����
//============================================================
void CTutorialManager::UpdateNextWait(void)
{
	if (m_nCounterState < NEXT_LESSON_WAIT[m_nLesson])
	{ // �J�E���^�[���]�C���Ԗ����̏ꍇ

		// �J�E���^�[�����Z
		m_nCounterState++;
	}
	else
	{ // �]�C���Ԃ��I�������ꍇ

		// �J�E���^�[��������
		m_nCounterState = 0;

		// �����b�X���ւ̈ڍs
		NextLesson();
	}
}

//============================================================
//	�����b�X���ւ̈ڍs����
//============================================================
void CTutorialManager::NextLesson(void)
{
	//--------------------------------------------------------
	//	���b�X���E�J�E���^�[���X�V
	//--------------------------------------------------------
	// ���b�X�������ɐi�߂�
	m_nLesson++;

	// �i�s��Ԏ��ɕ\������UI�̕`����ĊJ
	SetEnableProgressionDraw(true);

	if (m_nLesson < LESSON_MAX)
	{ // ���b�X�����܂�����ꍇ

		// ��Ԃ�ݒ�
		m_state = STATE_PROGRESSION;	// �i�s���
	}
	else
	{ // ���b�X���������Ȃ��ꍇ

		// ��Ԃ�ݒ�
		m_state = STATE_END;	// �I�����

		// �֐��𔲂���
		return;
	}

	// ���b�X���J�E���^�[�̍ő�l��ݒ�
	m_pCounterLesson->SetMaxNum(NEXT_LESSON[m_nLesson]);

	// ���b�X���J�E���^�[��������
	m_pCounterLesson->SetNum(0);

	//--------------------------------------------------------
	//	���b�X���\�����X�V
	//--------------------------------------------------------
	// ���b�X���������e�N�X�`����o�^�E����
	m_pGuide->BindTexture(GUIDE_TEX_FILE[m_nLesson]);

	// ���b�X��������@�e�N�X�`����o�^�E����
	m_pControl->BindTexture(CONT_TEX_FILE[m_nLesson]);
}
