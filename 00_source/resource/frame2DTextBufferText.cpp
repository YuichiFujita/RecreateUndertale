//============================================================
//
//	�e�L�X�g�ۑ��o�b�t�@���� [frame2DTextBufferText.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "frame2DTextBufferText.h"
#include "frame2DTextStateText.h"

//************************************************************
//	�q�N���X [CFrame2DTextBufferText] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CFrame2DTextBufferText::CFrame2DTextBufferText() :
	m_sNextTextKey	("NONE")	// ���e�L�X�g�̌����L�[
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CFrame2DTextBufferText::~CFrame2DTextBufferText()
{

}

//============================================================
//	�e�L�X�g�@�\��Ԃ̐�������
//============================================================
CFrame2DTextState* CFrame2DTextBufferText::CreateState(const CFrame2D::EPreset preset)
{
	if (preset > CFrame2D::PRESET_NONE && preset < CFrame2D::PRESET_MAX)
	{ // �v���Z�b�g���͈͓��̏ꍇ

		// �e�L�X�g��Ԃ𐶐����Ԃ�
		return new CFrame2DTextStateText(preset);	// �z�u�w��
	}
	else
	{ // �v���Z�b�g���͈͊O�̏ꍇ

		// �e�L�X�g��Ԃ𐶐����Ԃ�
		return new CFrame2DTextStateText;	// �f�t�H���g
	}
}

//============================================================
//	�o�b�t�@���Ƃ̃Z�b�g�A�b�v����
//============================================================
void CFrame2DTextBufferText::LoadSetup(std::ifstream* pFile, const std::string& rString)
{
	// �t�@�C���|�C���^���Ȃ��ꍇ������
	if (pFile == nullptr) { assert(false); return; }

	// �J���ĂȂ��t�@�C���̏ꍇ������
	if (!pFile->is_open()) { assert(false); return; }

	// �t�@�C����Ǎ�
	std::string str;	// �Ǎ�������
	if (rString == "NEXT")
	{
		*pFile >> str;				// ����Ǎ�
		*pFile >> m_sNextTextKey;	// ���e�L�X�g�̌����L�[��Ǎ�
	}
}
