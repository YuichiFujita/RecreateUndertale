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
		"data\\FONT\\�ʂ˂�������������v7��.ttf",	// �e�X�g00
		"data\\FONT\\��S�V�b�N.otf",				// �e�X�g01
	};
	const float FONT_HEIGHT[] =	// �t�H���g�c��
	{
		42.0f,	// �f�t�H���g
		46.0f,	// �e�X�g00
		60.0f,	// �e�X�g01
	};
	const CSound::ELabel SOUND_LABEL[] =	// �T�E���h���x��
	{
		CSound::LABEL_SE_TEXT00,		// �f�t�H���g
		CSound::LABEL_SE_TEXT01,		// �C���g��
		CSound::LABEL_SE_TEXT_TORIEL00,	// �g���G��00
	};
}

//************************************************************
//	�X�^�e�B�b�N�A�T�[�g
//************************************************************
static_assert(NUM_ARRAY(FONT_PATH)   == CFrame2DModuleText::FONT_MAX,  "ERROR : Font Count Mismatch");
static_assert(NUM_ARRAY(FONT_HEIGHT) == CFrame2DModuleText::FONT_MAX,  "ERROR : Font Count Mismatch");
static_assert(NUM_ARRAY(SOUND_LABEL) == CFrame2DModuleText::SOUND_MAX, "ERROR : Sound Count Mismatch");

//************************************************************
//	�e�N���X [CFrame2DTextState] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CFrame2DTextState::CFrame2DTextState() :
	m_pContext		(nullptr),	// �R���e�L�X�g
	m_sCurTextKey	("")		// �����ς݃e�L�X�g�̌����L�[
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

	// �t�H���g������
	SetFontPath(pBuffer->m_font);

	// �T�E���h������
	SetSoundLabel(pBuffer->m_sound);

	// ���Έʒu�̐ݒ�
	SetPositionRelative();
}

//============================================================
//	�t�H���g�p�X�̎擾����
//============================================================
std::string CFrame2DTextState::GetFontPath(const CFrame2DModuleText::EFont font)
{
	// �t�H���g�p�X��Ԃ�
	return FONT_PATH[font];
}

//============================================================
//	�t�H���g�c���̎擾����
//============================================================
float CFrame2DTextState::GetFontHeight(const CFrame2DModuleText::EFont font)
{
	// �t�H���g�c����Ԃ�
	return FONT_HEIGHT[font];
}

//============================================================
//	�T�E���h���x���̎擾����
//============================================================
CSound::ELabel CFrame2DTextState::GetSoundLabel(const CFrame2DModuleText::ESound sound)
{
	// �T�E���h���x����Ԃ�
	return SOUND_LABEL[sound];
}
