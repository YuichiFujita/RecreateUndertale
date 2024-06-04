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
	const int	PRIORITY	= 7;		// �t�F�[�h�̗D�揇��
	const float	FADE_LEVEL	= 0.05f;	// �t�F�[�h�̃��l�̉�����

#ifdef _DEBUG

	const CScene::EMode INIT_SCENE = CScene::MODE_INTRO;	// �����V�[��

#else	// NDEBUG

	const CScene::EMode INIT_SCENE = CScene::MODE_INTRO;	// �����V�[��

#endif	// _DEBUG
}

//************************************************************
//	�e�N���X [CFade] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CFade::CFade() :
	m_pFade		(nullptr),		// �t�F�[�h���
	m_modeNext	(INIT_SCENE),	// ���V�[��
	m_fade		(FADE_NONE),	// �t�F�[�h���
	m_fWaitTime	(0.0f)			// �]�C�Ǘ��J�E���^�[
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
	m_pFade		= nullptr;		// �t�F�[�h���
	m_modeNext	= INIT_SCENE;	// ���V�[��
	m_fade		= FADE_IN;		// �t�F�[�h���
	m_fWaitTime	= 0.0f;			// �]�C�Ǘ��J�E���^�[

	// �t�F�[�h�̐���
	m_pFade = CObject2D::Create
	( // ����
		SCREEN_CENT,	// �ʒu
		SCREEN_SIZE,	// �傫��
		VEC3_ZERO,		// ����
		XCOL_BLACK		// �F
	);
	if (m_pFade == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ̐ݒ�
	m_pFade->SetPriority(PRIORITY);

	// ���x���w��Ȃ��ɐݒ�
	m_pFade->SetLabel(CObject::LABEL_NONE);	// �����j���E�X�V���~����

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
	// �t�F�[�h�̏I��
	SAFE_UNINIT(m_pFade);
}

//============================================================
//	�X�V����
//============================================================
void CFade::Update(const float fDeltaTime)
{
	// �t�F�[�h���Ă��Ȃ��ꍇ������
	if (m_fade == FADE_NONE) { return; }

	D3DXCOLOR colFade = m_pFade->GetColor();	// �t�F�[�h�F
	switch (m_fade)
	{ // �t�F�[�h��Ԃ��Ƃ̏���
	case FADE_WAIT:	// �t�F�[�h�]�C���

		// �]�C���������炷
		m_fWaitTime -= fDeltaTime;
		if (m_fWaitTime <= 0.0f)
		{ // �]�C�I�������ꍇ

			// �t�F�[�h�A�E�g��Ԃɂ���
			m_fade = FADE_OUT;
		}

		break;

	case FADE_IN:	// �t�F�[�h�C�����

		// ���[�h���������Ă��Ȃ��ꍇ������
		if (GET_MANAGER->GetLoading()->GetState() != CLoading::LOAD_NONE) { break; }

		// �����ɂ��Ă���
		colFade.a -= FADE_LEVEL;
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
		colFade.a += FADE_LEVEL;
		if (colFade.a >= 1.0f)
		{ // �s�����ɂȂ����ꍇ

			// ���l��␳
			colFade.a = 1.0f;

			// �t�F�[�h�C����Ԃɂ���
			m_fade = FADE_IN;

			// ���[�h�̐ݒ�
			GET_MANAGER->SetMode(m_modeNext);
		}

		break;

	default:	// ��O����
		assert(false);
		break;
	}

	// �F�𔽉f
	m_pFade->SetColor(colFade);

	// �t�F�[�h�̍X�V
	m_pFade->Update(fDeltaTime);
}

//============================================================
//	�`�揈��
//============================================================
void CFade::Draw(void)
{

}

//============================================================
//	�t�F�[�h��Ԏ擾����
//============================================================
CFade::EFade CFade::GetState(void) const
{
	// ���݂̃t�F�[�h��Ԃ�Ԃ�
	return m_fade;
}

//============================================================
//	�t�F�[�h�̊J�n����
//============================================================
void CFade::SetFade(const float fWaitTime)
{
	// �t�F�[�h���̏ꍇ������
	if (m_fade != FADE_NONE) { return; }

	// �]�C�t���[���I�[�o�[
	assert(fWaitTime >= 0.0f);

	// �]�C���Ԃ�ݒ�
	m_fWaitTime = fWaitTime;

	// TODO�F�t�F�[�h�������Ȃ���ԍ�낤
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
//	���V�[���̐ݒ菈�� (�t�F�[�h�̂�)
//============================================================
void CFade::SetFade(const CScene::EMode mode, const float fWaitTime)
{
	// �t�F�[�h���̏ꍇ������
	if (m_fade != FADE_NONE) { return; }

	// �]�C�t���[���I�[�o�[
	assert(fWaitTime >= 0.0f);

	// �����̃��[�h��ݒ�
	m_modeNext = mode;

	// �]�C���Ԃ�ݒ�
	m_fWaitTime = fWaitTime;

	// TODO�F���[�h��ʂɍs���Ȃ��t�F�[�h��ԍ�낤
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

	// TODO�F���[�h��ʂɍs���t�F�[�h��ԍ�낤
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

//============================================================
//	�j������
//============================================================
void CFade::Release(CFade *&prFade)
{
	// �t�F�[�h�̏I��
	assert(prFade != nullptr);
	prFade->Uninit();

	// �������J��
	SAFE_DELETE(prFade);
}
