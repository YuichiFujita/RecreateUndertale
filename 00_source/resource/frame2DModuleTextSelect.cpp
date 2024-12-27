//============================================================
//
//	�I��t���e�L�X�g�\���@�\���� [frame2DModuleTextSelect.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "frame2DModuleTextSelect.h"
#include "manager.h"
#include "object2D.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	namespace text
	{
		const VECTOR3 OFFSET[] =	// �e�L�X�g�I�t�Z�b�g�v���Z�b�g
		{
			VECTOR3(-410.0f, -80.0f, 0.0f)	// �����z�u
		};
		const char*	FONT = "data\\FONT\\JF�h�b�g���_�S�V�b�N14.ttf";	// �t�H���g�p�X
		const int	PRIORITY	= 6;				// �e�L�X�g�̗D�揇��
		const bool	ITALIC		= false;			// �C�^���b�N
		const float	CHAR_HEIGHT	= 42.0f;			// �����c��
		const float	LINE_HEIGHT	= 54.0f;			// �s�ԏc��
		const float	WAIT_TIME	= 0.045f;			// �����\���̑ҋ@����
		const EAlignX ALIGN_X	= XALIGN_CENTER;	// ���z�u
		const EAlignY ALIGN_Y	= YALIGN_TOP;		// �c�z�u
	}

	namespace soul
	{
		const char* PATH	= "data\\TEXTURE\\spr_heartsmall.png";	// �\�E���J�[�\���e�N�X�`���p�X
		const VECTOR3 POS	= VECTOR3(97.5f, 308.5f, 0.0f);			// �\�E���J�[�\���ʒu
		const VECTOR3 SIZE	= VECTOR3(26.5f, 26.5f, 0.0f);			// �\�E���J�[�\���傫��
	}
}

//************************************************************
//	�X�^�e�B�b�N�A�T�[�g
//************************************************************
static_assert(NUM_ARRAY(text::OFFSET) == CFrame2D::PRESET_MAX, "ERROR : Preset Count Mismatch");

//************************************************************
//	�q�N���X [CFrame2DModuleTextSelect] �̃����o�֐�
//************************************************************
//============================================================
//	�ڏ��R���X�g���N�^ (�z�u�v���Z�b�g)
//============================================================
CFrame2DModuleTextSelect::CFrame2DModuleTextSelect(const CFrame2D::EPreset preset) : CFrame2DModuleTextSelect(text::OFFSET[preset])
{
	// �v���Z�b�g�͈͊O�G���[
	assert(preset > NONE_IDX && preset < CFrame2D::PRESET_MAX);
}

//============================================================
//	�R���X�g���N�^ (�z�u�w��)
//============================================================
CFrame2DModuleTextSelect::CFrame2DModuleTextSelect(const VECTOR3& rOffset) : CFrame2DModuleText(rOffset),
	m_pSoul		 (nullptr),	// �\�E���J�[�\�����
	m_nCurSelect (0)		// ���݂̑I����
{
	// �����o�ϐ����N���A
	memset(&m_apSelect[0], 0, sizeof(m_apSelect));	// �I�������
}

//============================================================
//	�f�X�g���N�^
//============================================================
CFrame2DModuleTextSelect::~CFrame2DModuleTextSelect()
{

}

//============================================================
//	����������
//============================================================
HRESULT CFrame2DModuleTextSelect::Init()
{
	// �����o�ϐ���������
	memset(&m_apSelect[0], 0, sizeof(m_apSelect));	// �I�������
	m_pSoul		 = nullptr;	// �\�E���J�[�\�����
	m_nCurSelect = 0;		// ���݂̑I����

	// �e�N���X�̏�����
	if (FAILED(CFrame2DModuleText::Init()))
	{ // �������Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	const int nPrioContext = m_pContext->GetPriority();	// �R���e�L�X�g�̗D�揇��
	for (int i = 0; i < SELECT_MAX; i++)
	{ // �I�����̑������J��Ԃ�

		// �I�����̐���
		m_apSelect[i] = CScrollText2D::Create
		( // ����
			text::FONT,			// �t�H���g�p�X
			text::ITALIC,		// �C�^���b�N
// TODO
#if 0
			VEC3_ZERO,			// ���_�ʒu
#else
			VECTOR3(SCREEN_CENT.x - 150.0f + 300.0f * (float)i, 600.0f, 0.0f),	// ���_�ʒu
#endif
			text::WAIT_TIME,	// �����\���̑ҋ@����
			text::CHAR_HEIGHT,	// �����c��
			text::LINE_HEIGHT,	// �s�ԏc��
			text::ALIGN_X,		// ���z�u
			text::ALIGN_Y		// �c�z�u
		);
		if (m_apSelect[i] == nullptr)
		{ // �����Ɏ��s�����ꍇ

			assert(false);
			return E_FAIL;
		}

		// �D�揇�ʂ�ݒ�
		m_apSelect[i]->SetPriority(nPrioContext);

		// �������莞�̍Đ�SE��ݒ�
		m_apSelect[i]->SetScrollSE(CSound::LABEL_SE_TEXT01);

		// TODO
		m_apSelect[i]->PushBackString("������");
		m_apSelect[i]->PushBackString("������");
	}

	// �\�E���J�[�\���̐���
	m_pSoul = CObject2D::Create
	( // ����
		soul::POS,	// �ʒu
		soul::SIZE	// �傫��
	);
	if (m_pSoul == nullptr)
	{ // �����Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// �\�E���e�N�X�`��������
	m_pSoul->BindTexture(soul::PATH);

	// ���x����ݒ�
	m_pSoul->SetLabel(CObject::LABEL_UI);

	// �D�揇�ʂ�ݒ�
	m_pSoul->SetPriority(nPrioContext);

	// �J�[�\���̎����`���OFF�ɂ���
	m_pSoul->SetEnableDraw(false);

	// ���Έʒu�̐ݒ�
	SetPositionRelative();

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CFrame2DModuleTextSelect::Uninit()
{
	for (int i = 0; i < SELECT_MAX; i++)
	{ // �I�����̑������J��Ԃ�

		// �e�L�X�g�̏I��
		SAFE_UNINIT(m_apSelect[i]);
	}

	// �\�E���J�[�\���̏I��
	SAFE_UNINIT(m_pSoul);

	// �e�N���X�̏I��
	CFrame2DModuleText::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CFrame2DModuleTextSelect::Update(const float fDeltaTime)
{
	if (!m_pSoul->IsDraw())
	{ // �J�[�\�����\������Ă��Ȃ��ꍇ

		if (IsTextEndScroll())
		{ // �{���̕������肪�I�������ꍇ

			// ���I�����̕���������J�n
			m_apSelect[SELECT_LEFT]->SetEnableScroll(true);
		}
		else { return; }

		if (m_apSelect[SELECT_LEFT]->IsEndScroll())
		{ // ���I�����̕������肪�I�������ꍇ

			// �E�I�����̕���������J�n
			m_apSelect[SELECT_RIGHT]->SetEnableScroll(true);
		}
		else { return; }

		if (m_apSelect[SELECT_RIGHT]->IsEndScroll())
		{ // �E�I�����̕������肪�I�������ꍇ

			// �J�[�\���̎����`���ON�ɂ���
			m_pSoul->SetEnableDraw(true);
		}
	}
	else
	{ // �J�[�\�����\������Ă���ꍇ

		// �I���̍X�V
		UpdateSelect();

		// ����̍X�V
		UpdateDecide();
	}

	// �e�N���X�̍X�V
	CFrame2DModuleText::Update(fDeltaTime);
}

//============================================================
//	�D�揇�ʂ̐ݒ菈��
//============================================================
void CFrame2DModuleTextSelect::SetPriority(const int nPriority)
{
	for (int i = 0; i < SELECT_MAX; i++)
	{ // �I�����̑������J��Ԃ�

		// �e�L�X�g�̗D�揇�ʂ�ݒ�
		m_apSelect[i]->SetPriority(nPriority);
	}
}

//============================================================
//	�ʒu�̐ݒ菈��
//============================================================
void CFrame2DModuleTextSelect::SetVec3Position(const VECTOR3& /*rPos*/)
{
	// ���Έʒu�̐ݒ�
	SetPositionRelative();
}

//============================================================
//	�����̐ݒ菈��
//============================================================
void CFrame2DModuleTextSelect::SetVec3Rotation(const VECTOR3& rRot)
{
	for (int i = 0; i < SELECT_MAX; i++)
	{ // �I�����̑������J��Ԃ�

		// �e�L�X�g�̌�����ݒ�
		m_apSelect[i]->SetVec3Rotation(rRot);
	}

	// ���Έʒu�̐ݒ�
	SetPositionRelative();
}

#if 0
//============================================================
//	�e�L�X�g�ύX����
//============================================================
void CFrame2DModuleTextSelect::ChangeText(const ESelect select, const AText& rText)
{
#if 0
	// �������S�č폜
	m_pText->DeleteStringAll();

	// �e�L�X�g������
	int nLoop = (int)rText.size();	// ������
	for (int i = 0; i < nLoop; i++)
	{ // ������̐����J��Ԃ�

		// ��������Ō���ɒǉ�
		m_pText->PushBackString(rText[i]);
	}

	// ����������J�n����
	m_pText->SetEnableScroll(true);
#else

#endif
}
#endif

//============================================================
//	�I���̍X�V����
//============================================================
void CFrame2DModuleTextSelect::UpdateSelect()
{
	// �I��������
	CInputKeyboard* pKey = GET_INPUTKEY;	// �L�[�{�[�h���
	if (pKey->IsTrigger(DIK_LEFT))
	{
		// ���ɑI�������炷
		m_nCurSelect = (m_nCurSelect + 1) % SELECT_MAX;
	}
	if (pKey->IsTrigger(DIK_RIGHT))
	{
		// �E�ɑI�������炷
		m_nCurSelect = (m_nCurSelect + (SELECT_MAX - 1)) % SELECT_MAX;
	}

	// TODO
	VECTOR3 posSelect = m_apSelect[m_nCurSelect]->GetVec3Position();
	posSelect.x -= m_apSelect[m_nCurSelect]->GetTextWidth() * 0.5f + 30.0f;
	posSelect.y += m_apSelect[m_nCurSelect]->GetCharHeight() * 0.5f;

	// �\�E���J�[�\���̈ʒu���ړ�
	m_pSoul->SetVec3Position(posSelect);
}

//============================================================
//	����̍X�V����
//============================================================
void CFrame2DModuleTextSelect::UpdateDecide()
{
	if (input::Decide())
	{

	}
}

//============================================================
//	���Έʒu�̐ݒ菈��
//============================================================
void CFrame2DModuleTextSelect::SetPositionRelative()
{
#if 0
	VECTOR3 posFrame = m_pContext->GetVec3Position();	// �t���[���ʒu
	VECTOR3 rotFrame = m_pContext->GetVec3Rotation();	// �t���[������

	// X���W�I�t�Z�b�g�����炷
	posFrame.x += sinf(rotFrame.z + HALF_PI) * m_offset.x;
	posFrame.y += cosf(rotFrame.z + HALF_PI) * m_offset.x;

	// Y���W�I�t�Z�b�g�����炷
	posFrame.x += sinf(rotFrame.z) * m_offset.y;
	posFrame.y += cosf(rotFrame.z) * m_offset.y;

	// �e�L�X�g�ʒu�̔��f
	m_pText->SetVec3Position(posFrame);
#else

#endif
}
