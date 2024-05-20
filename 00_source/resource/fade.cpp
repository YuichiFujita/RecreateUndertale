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
	m_pObject2D		(nullptr),				// �t�F�[�h�\���̏��
	m_fade			(FADE_NONE),			// �t�F�[�h���
	m_modeNext		(CScene::MODE_INTRO),	// ���̃V�[�����[�h
	m_nCounterWait	(0)						// �]�C�Ǘ��J�E���^�[
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
	m_pObject2D = nullptr;		// �t�F�[�h�\���̏��
	m_fade		= FADE_IN;		// �t�F�[�h���
	m_modeNext	= INIT_SCENE;	// ���̃V�[�����[�h
	m_nCounterWait = 0;			// �]�C�Ǘ��J�E���^�[

	// �I�u�W�F�N�g2D�̐���
	m_pObject2D = CObject2D::Create
	( // ����
		SCREEN_CENT,	// �ʒu
		SCREEN_SIZE,	// �傫��
		VEC3_ZERO,		// ����
		XCOL_BLACK		// �F
	);
	if (m_pObject2D == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ̐ݒ�
	m_pObject2D->SetPriority(PRIORITY);

	// ���x���w��Ȃ��ɐݒ�
	m_pObject2D->SetLabel(CObject::LABEL_NONE);

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
	SAFE_UNINIT(m_pObject2D);
}

//============================================================
//	�X�V����
//============================================================
void CFade::Update(const float fDeltaTime)
{
	if (m_fade != FADE_NONE)
	{ // �������Ȃ���Ԃł͂Ȃ��ꍇ

		D3DXCOLOR colFade = m_pObject2D->GetColor();	// �t�F�[�h�F
		switch (m_fade)
		{ // �t�F�[�h��Ԃ��Ƃ̏���
		case FADE_WAIT:	// �t�F�[�h�]�C���

			if (m_nCounterWait > 0)
			{ // �J�E���^�[�� 0���傫���ꍇ

				// �J�E���^�[�����Z
				m_nCounterWait--;
			}
			else
			{ // �J�E���^�[�� 0�ȉ��̏ꍇ

				// �t�F�[�h��Ԃ�ݒ�
				m_fade = FADE_OUT;	// �t�F�[�h�A�E�g���
			}

			break;

		case FADE_IN:	// �t�F�[�h�C�����

			if (GET_MANAGER->GetLoading()->GetState() == CLoading::LOAD_NONE)
			{ // ���[�h���Ă��Ȃ��ꍇ

				// ���l�����Z
				colFade.a -= FADE_LEVEL;
				if (colFade.a <= 0.0f)
				{ // ���l�� 0.0f����������ꍇ

					// ���l��␳
					colFade.a = 0.0f;

					// �t�F�[�h��Ԃ�ݒ�
					m_fade = FADE_NONE;	// �������Ȃ����
				}
			}

			break;

		case FADE_OUT:	// �t�F�[�h�A�E�g���

			// ���l�����Z
			colFade.a += FADE_LEVEL;
			if (colFade.a >= 1.0f)
			{ // ���l�� 1.0f ���������ꍇ

				// ���l��␳
				colFade.a = 1.0f;

				// �t�F�[�h��Ԃ�ݒ�
				m_fade = FADE_IN;	// �t�F�[�h�C�����

				// ���[�h�̐ݒ�
				if (FAILED(GET_MANAGER->SetMode(m_modeNext)))
				{ // ���[�h�̐ݒ�Ɏ��s�����ꍇ

					// �E�C���h�E��j������
					CManager::ReleaseWindow();
				}
			}

			break;

		default:	// ��O����
			assert(false);
			break;
		}

		// �F�̍X�V
		m_pObject2D->SetColor(colFade);

		// �I�u�W�F�N�g2D�̍X�V
		m_pObject2D->Update(fDeltaTime);
	}
}

//============================================================
//	�`�揈��
//============================================================
void CFade::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;	// �f�o�C�X�̃|�C���^

	// �T���v���[�X�e�[�g��ݒ�
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);	// U�����̃��b�s���O�𖳌���
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);	// V�����̃��b�s���O�𖳌���

	// �I�u�W�F�N�g2D�̕`��
	m_pObject2D->Draw();

	// �T���v���[�X�e�[�g��ݒ�
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// U�����̃��b�s���O��L����
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// V�����̃��b�s���O��L����
}

//============================================================
//	���V�[���ւ̃t�F�[�h�ݒ菈��
//============================================================
void CFade::Set(const CScene::EMode mode, const int nWait)
{
	// ��O����
	assert(nWait >= 0);	// �]�C�t���[���I�[�o�[

	if (m_fade == FADE_NONE)
	{ // �t�F�[�h���s���Ă��Ȃ��ꍇ

		// �����̃��[�h��ݒ�
		m_modeNext = mode;

		// �]�C�Ǘ��J�E���^�[��ݒ�
		m_nCounterWait = nWait;

		// �t�F�[�h��Ԃ�ݒ�
		if (m_nCounterWait <= 0)
		{ // �J�E���^�[�� 0�ȉ��̏ꍇ

			m_fade = FADE_OUT;	// �t�F�[�h�A�E�g���
		}
		else
		{ // �J�E���^�[�� 0���傫���ꍇ

			m_fade = FADE_WAIT;	// �t�F�[�h�]�C���
		}
	}
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
