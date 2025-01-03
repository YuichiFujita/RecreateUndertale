//============================================================
//
//	�e�L�X�g�ۑ��o�b�t�@�w�b�_�[ [frame2DTextBufferText.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _FRAME2D_TEXT_BUFFER_TEXT_H_
#define _FRAME2D_TEXT_BUFFER_TEXT_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "frame2DTextBuffer.h"
#include "frame2D.h"

//************************************************************
//	�O���錾
//************************************************************
class CFrame2DModule;	// �t���[��2D�@�\�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �e�L�X�g�ۑ��o�b�t�@�N���X
class CFrame2DTextBufferText : public CFrame2DTextBuffer
{
public:
	// �R���X�g���N�^
	CFrame2DTextBufferText();

	// �f�X�g���N�^
	~CFrame2DTextBufferText() override;

	// �I�[�o�[���C�h�֐�
	CFrame2DModule* CreateModule(const CFrame2D::EPreset preset) override;		// �e�L�X�g�@�\����
	void LoadKeyString(std::ifstream* pFile, std::string& rString) override;	// ���݃L�[������Ǎ�
	inline CFrame2DTextBufferText* GetText() override { return this; }			// �e�L�X�g�擾

	// �����o�ϐ�
	std::string m_sNextTextKey;	// ���e�L�X�g�̌����L�[
};

#endif	// _FRAME2D_TEXT_BUFFER_TEXT_H_
