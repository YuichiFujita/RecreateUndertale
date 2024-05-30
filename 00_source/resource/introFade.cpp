//============================================================
//
//	�C���g���t�F�[�h���� [introFade.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "introFade.h"
#include "introManager.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const int	PRIORITY	= 5;	// �t�F�[�h�̗D�揇��
	const float	FADE_LEVEL	= 2.8f;	// �t�F�[�h�̃��ω���
}

//************************************************************
//	�q�N���X [CIntroFade] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CIntroFade::CIntroFade(CIntroManager *pIntro) :
	m_pIntro	(pIntro),	// �C���g���}�l�[�W���[
	m_fade		(FADE_IN)	// �t�F�[�h��
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CIntroFade::~CIntroFade()
{

}

//============================================================
//	����������
//============================================================
HRESULT CIntroFade::Init(void)
{
	// �����o�ϐ���������
	m_fade = FADE_IN;	// �t�F�[�h��

	// �I�u�W�F�N�g2D�̏�����
	if (FAILED(CObject2D::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// ���x����UI�ɂ���
	SetLabel(LABEL_UI);

	// �D�揇�ʂ𕨌�\���|���S������ɂ���
	SetPriority(PRIORITY);

	// �ʒu���X�N���[�������ɂ���
	SetVec3Position(SCREEN_CENT);

	// �傫�����X�N���[���T�C�Y�ɂ���
	SetVec3Sizing(SCREEN_SIZE);

	// �|���S�������ɂ���
	SetColor(XCOL_ABLACK);

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CIntroFade::Uninit(void)
{
	// �I�u�W�F�N�g2D�̏I��
	CObject2D::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CIntroFade::Update(const float fDeltaTime)
{
	D3DXCOLOR colFade = GetColor();	// �t�F�[�h�F

	switch (m_fade)
	{ // �t�F�[�h��Ԃ��Ƃ̏���
	case FADE_IN:	// �t�F�[�h�C��

		// �����x���グ��
		colFade.a += FADE_LEVEL * fDeltaTime;
		if (colFade.a >= 1.0f)
		{ // �t�F�[�h�d�؂����ꍇ

			// �C���g���̕\�������ύX����
			m_pIntro->ChangeStory(m_pIntro->GetStoryID());

			// �t�F�[�h�A�E�g��Ԃɂ���
			m_fade = FADE_OUT;
		}

		break;

	case FADE_OUT:	// �t�F�[�h�A�E�g

		// �����x��������
		colFade.a -= FADE_LEVEL * fDeltaTime;
		if (colFade.a <= 0.0f)
		{ // �t�F�[�h�d�؂����ꍇ

			// �t�F�[�h�̏I��
			Uninit();
			return;
		}

		break;

	default:
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
void CIntroFade::Draw(CShader *pShader)
{
	// �I�u�W�F�N�g2D�̕`��
	CObject2D::Draw(pShader);
}

//============================================================
//	��������
//============================================================
CIntroFade *CIntroFade::Create(CIntroManager *pIntro)
{
	// �C���g���t�F�[�h�̐���
	CIntroFade *pIntroFade = new CIntroFade(pIntro);
	if (pIntroFade == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �C���g���t�F�[�h�̏�����
		if (FAILED(pIntroFade->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �C���g���t�F�[�h�̔j��
			SAFE_DELETE(pIntroFade);
			return nullptr;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return pIntroFade;
	}
}
