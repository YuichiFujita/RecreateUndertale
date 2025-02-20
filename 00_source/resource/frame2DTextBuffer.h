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
class CFrame2DTextState;			// �e�L�X�g�@�\��ԃN���X
class CFrame2DTextBufferText;		// �e�L�X�g�ۑ��o�b�t�@�N���X
class CFrame2DTextBufferSelect;		// �I��t���e�L�X�g�ۑ��o�b�t�@�N���X
class CFrame2DTextBufferFaceText;	// �\��t���e�L�X�g�ۑ��o�b�t�@�N���X
class CFrame2DTextBufferFaceSelect;	// �\��/�I��t���e�L�X�g�ۑ��o�b�t�@�N���X
class CFrame2DTextBufferItem;		// �A�C�e���e�L�X�g�ۑ��o�b�t�@�N���X

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
	virtual CFrame2DTextState* CreateState(const CFrame2D::EPreset preset) = 0;	// �e�L�X�g�@�\��Ԑ���

	// ���z�֐�
	virtual inline CFrame2DTextBufferText* GetBufferText()				{ return nullptr; }		// �e�L�X�g�o�b�t�@�擾
	virtual inline CFrame2DTextBufferSelect* GetBufferSelect()			{ return nullptr; }		// �I��t���e�L�X�g�o�b�t�@�擾
	virtual inline CFrame2DTextBufferFaceText* GetBufferFaceText()		{ return nullptr; }		// �\��t���e�L�X�g�o�b�t�@�擾
	virtual inline CFrame2DTextBufferFaceSelect* GetBufferFaceSelect()	{ return nullptr; }		// �\��/�I��t���e�L�X�g�o�b�t�@�擾
	virtual inline CFrame2DTextBufferItem* GetBufferItem()				{ return nullptr; }		// �A�C�e���e�L�X�g�o�b�t�@�擾
	virtual inline void LoadSetup(std::ifstream* /*pFile*/, const std::string& /*rString*/)	{}	// �o�b�t�@���Ƃ̃Z�b�g�A�b�v

	// �����o�ϐ�
	std::string m_sPath;	// �e�L�X�g�ۑ��p�X
	std::string m_sKey;		// �e�L�X�g�����L�[
	AText m_text;			// �e�L�X�g�ۑ�
};

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "frame2DTextBufferText.h"
#include "frame2DTextBufferSelect.h"

#endif	// _FRAME2D_TEXT_BUFFER_H_
