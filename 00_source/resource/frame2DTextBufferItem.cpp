//============================================================
//
//	�A�C�e���e�L�X�g�ۑ��o�b�t�@���� [frame2DTextBufferItem.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "frame2DTextBufferItem.h"
#include "frame2DTextStateItem.h"

//************************************************************
//	�q�N���X [CFrame2DTextBufferItem] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CFrame2DTextBufferItem::CFrame2DTextBufferItem()
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CFrame2DTextBufferItem::~CFrame2DTextBufferItem()
{

}

//============================================================
//	�e�L�X�g�@�\��Ԃ̐�������
//============================================================
CFrame2DTextState* CFrame2DTextBufferItem::CreateState(const CFrame2D::EPreset preset)
{
	if (preset > CFrame2D::PRESET_NONE && preset < CFrame2D::PRESET_MAX)
	{ // �v���Z�b�g���͈͓��̏ꍇ

		// �A�C�e���e�L�X�g��Ԃ𐶐����Ԃ�
		return new CFrame2DTextStateItem(preset);	// �z�u�w��
	}
	else
	{ // �v���Z�b�g���͈͊O�̏ꍇ

		// �A�C�e���e�L�X�g��Ԃ𐶐����Ԃ�
		return new CFrame2DTextStateItem;	// �f�t�H���g
	}
}
