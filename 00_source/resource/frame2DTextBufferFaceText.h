//============================================================
//
//	�\��t���e�L�X�g�ۑ��o�b�t�@�w�b�_�[ [frame2DTextBufferFaceText.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _FRAME2D_TEXT_BUFFER_FACE_TEXT_H_
#define _FRAME2D_TEXT_BUFFER_FACE_TEXT_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "frame2DTextBufferText.h"
#include "frame2D.h"

//************************************************************
//	�N���X��`
//************************************************************
// �\��t���e�L�X�g�ۑ��o�b�t�@�N���X
class CFrame2DTextBufferFaceText : public CFrame2DTextBufferText
{
public:
	// �R���X�g���N�^
	CFrame2DTextBufferFaceText(const int nIdxFace);

	// �f�X�g���N�^
	~CFrame2DTextBufferFaceText() override;

	// �I�[�o�[���C�h�֐�
	CFrame2DTextState* CreateState(const CFrame2D::EPreset preset = CFrame2D::PRESET_NONE) override;	// �e�L�X�g�@�\��Ԑ���
	void LoadSetup(std::ifstream* pFile, const std::string& rString) override;			// �o�b�t�@���Ƃ̃Z�b�g�A�b�v
	inline CFrame2DTextBufferFaceText* GetBufferFaceText() override { return this; }	// �\��t���e�L�X�g�o�b�t�@�擾

	// �����o�ϐ�
	const int m_nIdxFace;	// ��C���f�b�N�X
	int m_nTypeEmo;			// �\����
};

#endif	// _FRAME2D_TEXT_BUFFER_FACE_TEXT_H_
