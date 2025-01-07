//============================================================
//
//	�e�L�X�g��ԏ��� [frame2DTextStateText.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "frame2DTextStateText.h"
#include "frame2DModuleText.h"
#include "frame2DTextBuffer.h"

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
		const int	PRIORITY	= 6;			// �e�L�X�g�̗D�揇��
		const bool	ITALIC		= false;		// �C�^���b�N
		const float	CHAR_HEIGHT	= 42.0f;		// �����c��
		const float	LINE_HEIGHT	= 54.0f;		// �s�ԏc��
		const float	WAIT_TIME	= 0.045f;		// �����\���̑ҋ@����
		const EAlignX ALIGN_X	= XALIGN_LEFT;	// ���z�u
		const EAlignY ALIGN_Y	= YALIGN_TOP;	// �c�z�u
	}
}

//************************************************************
//	�X�^�e�B�b�N�A�T�[�g
//************************************************************
static_assert(NUM_ARRAY(text::OFFSET) == CFrame2D::PRESET_MAX, "ERROR : Preset Count Mismatch");

//************************************************************
//	�q�N���X [CFrame2DTextStateText] �̃����o�֐�
//************************************************************
//============================================================
//	�ڏ��R���X�g���N�^ (�f�t�H���g)
//============================================================
CFrame2DTextStateText::CFrame2DTextStateText() : CFrame2DTextStateText(VEC3_ZERO)	// TODO�F�R���X�g���N�^�Q���ꂼ��z�肵�������ɂȂ��Ă��邩����
{

}

//============================================================
//	�ڏ��R���X�g���N�^ (�z�u�v���Z�b�g)
//============================================================
CFrame2DTextStateText::CFrame2DTextStateText(const CFrame2D::EPreset preset) : CFrame2DTextStateText(text::OFFSET[preset])
{
	// �v���Z�b�g�͈͊O�G���[
	assert(preset > CFrame2D::PRESET_NONE && preset < CFrame2D::PRESET_MAX);
}

//============================================================
//	�R���X�g���N�^ (�z�u�w��)
//============================================================
CFrame2DTextStateText::CFrame2DTextStateText(const VECTOR3& rOffset) :
	m_sNextTextKey	({}),		// ���e�L�X�g�̌����L�[
	m_pText			(nullptr),	// �e�L�X�g���
	m_offset		(rOffset)	// �e�L�X�g�I�t�Z�b�g
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CFrame2DTextStateText::~CFrame2DTextStateText()
{

}

//============================================================
//	����������
//============================================================
HRESULT CFrame2DTextStateText::Init()
{
	// �����o�ϐ���������
	m_sNextTextKey	= "NONE";	// ���e�L�X�g�̌����L�[
	m_pText			= nullptr;	// �e�L�X�g���

	// �e�L�X�g�̐���
	m_pText = CScrollText2D::Create
	( // ����
		text::FONT,			// �t�H���g�p�X
		text::ITALIC,		// �C�^���b�N
		VEC3_ZERO,			// ���_�ʒu
		text::WAIT_TIME,	// �����\���̑ҋ@����
		text::CHAR_HEIGHT,	// �����c��
		text::LINE_HEIGHT,	// �s�ԏc��
		text::ALIGN_X,		// ���z�u
		text::ALIGN_Y		// �c�z�u
	);
	if (m_pText == nullptr)
	{ // �����Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	m_pText->SetPriority(m_pContext->GetFramePriority());

	// �������莞�̍Đ�SE��ݒ�
	m_pText->SetScrollSE(CSound::LABEL_SE_TEXT01);

	// ���Έʒu�̐ݒ�
	CFrame2DTextStateText::SetPositionRelative();	// ���g�̑��Έʒu

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CFrame2DTextStateText::Uninit()
{
	// �e�L�X�g�̏I��
	SAFE_UNINIT(m_pText);

	// ���g�̔j��
	delete this;
}

//============================================================
//	�X�V����
//============================================================
void CFrame2DTextStateText::Update(const float fDeltaTime)
{
	if (input::Decide())
	{
		if (!m_pText->IsEndScroll())
		{ // �������蒆�̏ꍇ

			// ������S�\��������
			m_pText->SetEnableDraw(true);
			return;
		}

		// �e�L�X�g�̑J��
		m_pContext->TransText(m_sNextTextKey);
	}
}

//============================================================
//	�D�揇�ʂ̐ݒ菈��
//============================================================
void CFrame2DTextStateText::SetPriority(const int nPriority)
{
	// �e�L�X�g�̗D�揇�ʂ�ݒ�
	m_pText->SetPriority(nPriority);
}

//============================================================
//	�ʒu�̐ݒ菈��
//============================================================
void CFrame2DTextStateText::SetVec3Position(const VECTOR3& /*rPos*/)
{
	// ���Έʒu�̐ݒ�
	SetPositionRelative();
}

//============================================================
//	�����̐ݒ菈��
//============================================================
void CFrame2DTextStateText::SetVec3Rotation(const VECTOR3& rRot)
{
	// �e�L�X�g�̌�����ݒ�
	m_pText->SetVec3Rotation(rRot);

	// ���Έʒu�̐ݒ�
	SetPositionRelative();
}

//============================================================
//	�e�L�X�g���ۑ��o�b�t�@�̊�������
//============================================================
void CFrame2DTextStateText::BindTextBuffer(CFrame2DTextBuffer* pBuffer)
{
	// �e�L�X�g�ۑ��o�b�t�@�ɕϊ��ł��Ȃ��ꍇ������
	CFrame2DTextBufferText* pBuffText = pBuffer->GetBufferText();
	if (pBuffText == nullptr) { assert(false); return; }

	// ���e�L�X�g�̌����L�[������
	m_sNextTextKey = pBuffText->m_sNextTextKey;

	// �e�L�X�g��������
	int nNumStr = (int)pBuffText->m_text.size();	// ������
	for (int i = 0; i < nNumStr; i++)
	{ // �����񐔕��J��Ԃ�

		// ��������Ō���ɒǉ�
		m_pText->PushBackString(pBuffText->m_text[i]);
	}

	// ����������J�n����
	m_pText->SetEnableScroll(true);

	// ���Έʒu�̐ݒ�
	SetPositionRelative();
}

//============================================================
//	�e�L�X�g�ύX����
//============================================================
void CFrame2DTextStateText::ChangeText(const AText& rText)
{
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

	// ���Έʒu�̐ݒ�
	SetPositionRelative();
}

//============================================================
//	�e�L�X�g�I�t�Z�b�g�̐ݒ菈��
//============================================================
void CFrame2DTextStateText::SetOffset(const VECTOR3& rOffset)
{
	// �e�L�X�g�I�t�Z�b�g�̐ݒ�
	m_offset = rOffset;

	// ���Έʒu�̐ݒ�
	SetPositionRelative();
}

//============================================================
//	���Έʒu�̐ݒ菈��
//============================================================
void CFrame2DTextStateText::SetPositionRelative()
{
	VECTOR3 posFrame = m_pContext->GetFramePosition();	// �t���[���ʒu
	VECTOR3 rotFrame = m_pContext->GetFrameRotation();	// �t���[������

	// X���W�I�t�Z�b�g�����炷
	posFrame.x += sinf(rotFrame.z + HALF_PI) * m_offset.x;
	posFrame.y += cosf(rotFrame.z + HALF_PI) * m_offset.x;

	// Y���W�I�t�Z�b�g�����炷
	posFrame.x += sinf(rotFrame.z) * m_offset.y;
	posFrame.y += cosf(rotFrame.z) * m_offset.y;

	// �e�L�X�g�ʒu�̔��f
	m_pText->SetVec3Position(posFrame);
}
