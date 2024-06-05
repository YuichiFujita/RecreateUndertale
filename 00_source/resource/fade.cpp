//============================================================
//
//	�t�F�[�h���� [fade.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "fade.h"
#include "manager.h"
#include "renderer.h"
#include "loading.h"
#include "object2D.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
#ifdef _DEBUG

	const CScene::EMode INIT_SCENE = CScene::MODE_INTRO;	// �����V�[��

#else	// NDEBUG

	const CScene::EMode INIT_SCENE = CScene::MODE_INTRO;	// �����V�[��

#endif	// _DEBUG

	const int	PRIORITY = 7;		// �t�F�[�h�̗D�揇��
	const float	LEVEL	 = 0.03f;	// �t�F�[�h�̃��l������
}

//************************************************************
//	�e�N���X [CFade] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CFade::CFade() :
	m_pFuncSetMode	(nullptr),		// ���[�h�ݒ�֐��|�C���^
	m_modeNext		(INIT_SCENE),	// ���V�[��
	m_fade			(FADE_NONE),	// �t�F�[�h���
	m_fWaitTime		(0.0f),			// ���݂̗]�C����
	m_fLevel		(LEVEL)			// ���l������
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CFade::~CFade()
{

}

//============================================================
//	����������
//============================================================
HRESULT CFade::Init(void)
{
	// �����o�ϐ���������
	m_pFuncSetMode	= nullptr;		// ���[�h�ݒ�֐��|�C���^
	m_modeNext		= INIT_SCENE;	// ���V�[��
	m_fade			= FADE_IN;		// �t�F�[�h���
	m_fWaitTime		= 0.0f;			// ���݂̗]�C����
	m_fLevel		= LEVEL;		// ���l������

	// �I�u�W�F�N�g2D�̏�����
	if (FAILED(CObject2D::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �ʒu���X�N���[�������ɂ���
	SetVec3Position(SCREEN_CENT);

	// �傫�����X�N���[���T�C�Y�ɂ���
	SetVec3Sizing(SCREEN_SIZE);

	// �F�����ɂ���
	SetColor(XCOL_BLACK);

	// �D�揇�ʂ���ԏ�ɂ���
	SetPriority(PRIORITY);

	// ���x���w��Ȃ��ɂ���
	SetLabel(CObject::LABEL_NONE);	// �����j���E�X�V���~����

	// �V�[���̏�����
	if (FAILED(GET_MANAGER->InitScene(m_modeNext)))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CFade::Uninit(void)
{
	// �I�u�W�F�N�g2D�̏I��
	CObject2D::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CFade::Update(const float fDeltaTime)
{
	// �t�F�[�h���Ă��Ȃ��ꍇ������
	if (m_fade == FADE_NONE) { return; }

	D3DXCOLOR colFade = GetColor();	// �t�F�[�h�F
	switch (m_fade)
	{ // �t�F�[�h��Ԃ��Ƃ̏���
	case FADE_WAIT:	// �t�F�[�h�]�C���

		// �]�C���������炷
		m_fWaitTime -= fDeltaTime;
		if (m_fWaitTime <= 0.0f)
		{ // �]�C�I�������ꍇ

			// �]�C���Ԃ�������
			m_fWaitTime = 0.0f;

			// �t�F�[�h�A�E�g��Ԃɂ���
			m_fade = FADE_OUT;
		}

		break;

	case FADE_IN:	// �t�F�[�h�C�����

		// ���[�h���������Ă��Ȃ��ꍇ������
		if (GET_MANAGER->GetLoading()->GetState() != CLoading::LOAD_NONE) { break; }

		// �����ɂ��Ă���
		colFade.a -= m_fLevel * fDeltaTime;
		if (colFade.a <= 0.0f)
		{ // �����ɂȂ����ꍇ

			// ���l��␳
			colFade.a = 0.0f;

			// �������Ȃ���Ԃɂ���
			m_fade = FADE_NONE;
		}

		break;

	case FADE_OUT:	// �t�F�[�h�A�E�g���

		// �s�����ɂ��Ă���
		colFade.a += m_fLevel * fDeltaTime;
		if (colFade.a >= 1.0f)
		{ // �s�����ɂȂ����ꍇ

			// ���l��␳
			colFade.a = 1.0f;

			// �t�F�[�h�C����Ԃɂ���
			m_fade = FADE_IN;

			if (m_pFuncSetMode != nullptr)
			{ // ���[�h�ݒ�֐����w�肳��Ă���ꍇ

				// ���[�h�̐ݒ�
				m_pFuncSetMode(m_modeNext);
			}
		}

		break;

	default:	// ��O����
		assert(false);
		break;
	}

	// �F�𔽉f
	SetColor(colFade);

	// �I�u�W�F�N�g2D�̍X�V
	CObject2D::Update(fDeltaTime);
}

//============================================================
//	�`�揈��
//============================================================
void CFade::Draw(CShader *pShader)
{
	// �I�u�W�F�N�g2D�̕`��
	CObject2D::Draw(pShader);
}

//============================================================
//	�t�F�[�h�̊J�n����
//============================================================
void CFade::SetFade(const float fLevel, const int nPriority)
{
	// �t�F�[�h���̏ꍇ������
	if (m_fade != FADE_NONE) { return; }

	// ���l�����ʂ�ݒ�
	m_fLevel = fLevel;

	// �D�揇�ʂ�ݒ�
	SetPriority(nPriority);

	// ���[�h�ݒ�֐��|�C���^��������
	m_pFuncSetMode = nullptr;

	// �t�F�[�h�A�E�g��Ԃɂ���
	m_fade = FADE_OUT;
}

//============================================================
//	���V�[���̐ݒ菈�� (�t�F�[�h�̂�)
//============================================================
void CFade::SetModeFade(const CScene::EMode mode, const float fWaitTime)
{
	// �t�F�[�h���̏ꍇ������
	if (m_fade != FADE_NONE) { return; }

	// �]�C�t���[���I�[�o�[
	assert(fWaitTime >= 0.0f);

	// �����̃��[�h��ݒ�
	m_modeNext = mode;

	// �]�C���Ԃ�ݒ�
	m_fWaitTime = fWaitTime;

	// ���l�����ʂ�ݒ�
	m_fLevel = LEVEL;

	// �D�揇�ʂ�ݒ�
	SetPriority(PRIORITY);

	// ���[�h��ʂ����܂Ȃ����[�h�ݒ�֐���ݒ�
	m_pFuncSetMode = std::bind(&CManager::SetMode, GET_MANAGER, std::placeholders::_1);

	if (m_fWaitTime <= 0.0f)
	{ // �J�E���^�[�����ݒ�̏ꍇ

		// �t�F�[�h�A�E�g��Ԃɂ���
		m_fade = FADE_OUT;
	}
	else
	{ // �J�E���^�[���ݒ肳�ꂽ�ꍇ

		// �t�F�[�h�]�C��Ԃɂ���
		m_fade = FADE_WAIT;
	}
}

//============================================================
//	���V�[���̐ݒ菈�� (���[�h��ʕt��)
//============================================================
void CFade::SetLoadFade(const CScene::EMode mode, const float fWaitTime)
{
	// �t�F�[�h���̏ꍇ������
	if (m_fade != FADE_NONE) { return; }

	// �]�C�t���[���I�[�o�[
	assert(fWaitTime >= 0.0f);

	// �����̃��[�h��ݒ�
	m_modeNext = mode;

	// �]�C���Ԃ�ݒ�
	m_fWaitTime = fWaitTime;

	// ���l�����ʂ�ݒ�
	m_fLevel = LEVEL;

	// �D�揇�ʂ�ݒ�
	SetPriority(PRIORITY);

	// ���[�h��ʂ����ރ��[�h�ݒ�֐���ݒ�
	m_pFuncSetMode = std::bind(&CManager::SetLoadMode, GET_MANAGER, std::placeholders::_1);

	if (m_fWaitTime <= 0.0f)
	{ // �J�E���^�[�����ݒ�̏ꍇ

		// �t�F�[�h�A�E�g��Ԃɂ���
		m_fade = FADE_OUT;
	}
	else
	{ // �J�E���^�[���ݒ肳�ꂽ�ꍇ

		// �t�F�[�h�]�C��Ԃɂ���
		m_fade = FADE_WAIT;
	}
}

//============================================================
//	��������
//============================================================
CFade *CFade::Create(void)
{
	// �t�F�[�h�̐���
	CFade *pFade = new CFade;
	if (pFade == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �t�F�[�h�̏�����
		if (FAILED(pFade->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �t�F�[�h�̔j��
			SAFE_DELETE(pFade);
			return nullptr;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return pFade;
	}
}
