//============================================================
//
//	�e�L�X�g�@�\��ԏ��� [frame2DTextState.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "frame2DTextState.h"
#include "frame2DTextBuffer.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const char* FONT_PATH[] =	// �t�H���g�p�X
	{
		"data\\FONT\\JF�h�b�g���_�S�V�b�N14.ttf",	// �f�t�H���g
	};

	const CSound::ELabel SOUND_LABEL[] =	// �T�E���h���x��
	{
		CSound::LABEL_SE_TEXT00,	// �f�t�H���g
	};
}

//************************************************************
//	�X�^�e�B�b�N�A�T�[�g
//************************************************************
static_assert(NUM_ARRAY(FONT_PATH)   == CFrame2DTextState::FONT_MAX,  "ERROR : Font Count Mismatch");
static_assert(NUM_ARRAY(SOUND_LABEL) == CFrame2DTextState::SOUND_MAX, "ERROR : Sound Count Mismatch");

//************************************************************
//	�e�N���X [CFrame2DTextState] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CFrame2DTextState::CFrame2DTextState() :
	m_pContext		(nullptr),		// �R���e�L�X�g
	m_sCurTextKey	(""),			// �����ς݃e�L�X�g�̌����L�[
	m_font			(FONT_DEFAULT),	// �t�H���g
	m_sound			(SOUND_DEFAULT)	// �T�E���h
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CFrame2DTextState::~CFrame2DTextState()
{

}

//============================================================
//	�e�L�X�g���ۑ��o�b�t�@�̊�������
//============================================================
void CFrame2DTextState::BindTextBuffer(CFrame2DTextBuffer* pBuffer)
{
	// ���蓖�Ă�e�L�X�g�̌����L�[��ۑ�
	m_sCurTextKey = pBuffer->m_sKey;

	// �t�H���g��ۑ�/����
	m_font = pBuffer->m_font;
	SetFontPath(m_font);

	// �T�E���h��ۑ�/����
	m_sound = pBuffer->m_sound;
	SetSoundLabel(m_sound);

	// ���Έʒu�̐ݒ�
	SetPositionRelative();
}

//============================================================
//	�t�H���g�p�X�̎擾����
//============================================================
std::string CFrame2DTextState::GetFontPath(const EFont font)
{
	// �t�H���g�p�X��Ԃ�
	return FONT_PATH[font];
}

//============================================================
//	�T�E���h���x���̎擾����
//============================================================
CSound::ELabel CFrame2DTextState::GetSoundLabel(const ESound sound)
{
	// �T�E���h���x����Ԃ�
	return SOUND_LABEL[sound];
}
