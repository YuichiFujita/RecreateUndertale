//============================================================
//
//	�e�L�X�g���ۑ��o�b�t�@�w�b�_�[ [frame2DTextBuffer.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _FRAME2D_TEXT_BUFFER_H_
#define _FRAME2D_TEXT_BUFFER_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "frame2D.h"

//************************************************************
//	�O���錾
//************************************************************
class CFrame2DModule;			// �t���[��2D�@�\�N���X
class CFrame2DTextBufferText;	// �e�L�X�g�@�\�ۑ��N���X
class CFrame2DTextBufferSelect;	// �I��t���e�L�X�g�@�\�ۑ��N���X

//************************************************************
//	�N���X��`
//************************************************************
// �e�L�X�g���ۑ��o�b�t�@�N���X
class CFrame2DTextBuffer
{
public:
	// �R���X�g���N�^
	CFrame2DTextBuffer();

	// �f�X�g���N�^
	virtual ~CFrame2DTextBuffer();

	// �������z�֐�
	virtual CFrame2DModule* CreateModule(const CFrame2D::EPreset preset) = 0;	// �e�L�X�g�@�\����

	// ���z�֐�
	virtual inline CFrame2DTextBufferText* GetText()		{ return nullptr; }	// �e�L�X�g�擾
	virtual inline CFrame2DTextBufferSelect* GetSelect()	{ return nullptr; }	// �I��t���e�L�X�g�擾
	virtual inline void LoadKeyText(std::ifstream* /*pFile*/, std::string& /*rString*/)		{}	// ���݃L�[�e�L�X�g�Ǎ�
	virtual inline void LoadKeyString(std::ifstream* /*pFile*/, std::string& /*rString*/)	{}	// ���݃L�[������Ǎ�

	// �����o�ϐ�
	AText m_text;	// �e�L�X�g�ۑ�
};

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "frame2DTextBufferText.h"
#include "frame2DTextBufferSelect.h"

#endif	// _FRAME2D_TEXT_BUFFER_H_
