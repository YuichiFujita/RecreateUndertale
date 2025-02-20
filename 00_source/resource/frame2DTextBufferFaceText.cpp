//============================================================
//
//	�\��t���e�L�X�g�ۑ��o�b�t�@���� [frame2DTextBufferFaceText.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "frame2DTextBufferFaceText.h"
#include "frame2DTextStateFaceText.h"

//************************************************************
//	�q�N���X [CFrame2DTextBufferFaceText] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CFrame2DTextBufferFaceText::CFrame2DTextBufferFaceText()
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CFrame2DTextBufferFaceText::~CFrame2DTextBufferFaceText()
{

}

//============================================================
//	�e�L�X�g�@�\��Ԃ̐�������
//============================================================
CFrame2DTextState* CFrame2DTextBufferFaceText::CreateState(const CFrame2D::EPreset preset)
{
	if (preset > CFrame2D::PRESET_NONE && preset < CFrame2D::PRESET_MAX)
	{ // �v���Z�b�g���͈͓��̏ꍇ

		// �\��t���e�L�X�g��Ԃ𐶐����Ԃ�
		return new CFrame2DTextStateFaceText(preset);	// �z�u�w��
	}
	else
	{ // �v���Z�b�g���͈͊O�̏ꍇ

		// �\��t���e�L�X�g��Ԃ𐶐����Ԃ�
		return new CFrame2DTextStateFaceText;	// �f�t�H���g
	}
}
