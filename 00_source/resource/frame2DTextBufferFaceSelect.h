//============================================================
//
//	�\��/�I��t���e�L�X�g�ۑ��o�b�t�@�w�b�_�[ [frame2DTextBufferFaceSelect.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _FRAME2D_TEXT_BUFFER_FACE_SELECT_H_
#define _FRAME2D_TEXT_BUFFER_FACE_SELECT_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "frame2DTextBufferSelect.h"
#include "frame2D.h"

//************************************************************
//	�N���X��`
//************************************************************
// �\��/�I��t���e�L�X�g�ۑ��o�b�t�@�N���X
class CFrame2DTextBufferFaceSelect : public CFrame2DTextBufferSelect
{
public:
	// �R���X�g���N�^
	CFrame2DTextBufferFaceSelect(const int nIdxFace);

	// �f�X�g���N�^
	~CFrame2DTextBufferFaceSelect() override;

	// �I�[�o�[���C�h�֐�
	CFrame2DTextState* CreateState() override;	// �e�L�X�g�@�\��Ԑ���
	void LoadSetup(std::ifstream* pFile, const std::string& rString) override;				// �o�b�t�@���Ƃ̃Z�b�g�A�b�v
	inline CFrame2DTextBufferFaceSelect* GetBufferFaceSelect() override { return this; }	// �\��/�I��t���e�L�X�g�o�b�t�@�擾

	// �����o�ϐ�
	const int m_nIdxFace;	// ��C���f�b�N�X
	int m_nTypeTalkEmo;		// ��b���̕\����
	int m_nTypeIdolEmo;		// �ҋ@���̕\����
};

#endif	// _FRAME2D_TEXT_BUFFER_FACE_SELECT_H_
