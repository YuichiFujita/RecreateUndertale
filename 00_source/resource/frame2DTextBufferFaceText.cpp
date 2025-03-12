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
CFrame2DTextBufferFaceText::CFrame2DTextBufferFaceText(const int nIdxFace) :
	m_nIdxFace		(nIdxFace),	// ��C���f�b�N�X
	m_nTypeTalkEmo	(0),		// ��b���̕\����
	m_nTypeIdolEmo	(0)			// �ҋ@���̕\����
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
CFrame2DTextState* CFrame2DTextBufferFaceText::CreateState()
{
	// �\��t���e�L�X�g��Ԃ𐶐����Ԃ�
	return new CFrame2DTextStateFaceText;
}

//============================================================
//	�o�b�t�@���Ƃ̃Z�b�g�A�b�v����
//============================================================
void CFrame2DTextBufferFaceText::LoadSetup(std::ifstream* pFile, const std::string& rString)
{
	// ���o�b�t�@�̃Z�b�g�A�b�v
	CFrame2DTextBufferText::LoadSetup(pFile, rString);

	// �t�@�C���|�C���^���Ȃ��ꍇ������
	if (pFile == nullptr) { assert(false); return; }

	// �J���ĂȂ��t�@�C���̏ꍇ������
	if (!pFile->is_open()) { assert(false); return; }

	// �\��t���e�L�X�g�ۑ��o�b�t�@�ɕϊ��ł��Ȃ��ꍇ������
	CFrame2DTextBufferFaceText* pBuffFaceText = GetBufferFaceText();
	if (pBuffFaceText == nullptr) { assert(false); return; }

	// �t�@�C����Ǎ�
	std::string str;	// �Ǎ�������
	if (rString == "TALK_EMO")
	{
		*pFile >> str;								// ����Ǎ�
		*pFile >> pBuffFaceText->m_nTypeTalkEmo;	// ��b���̕\���ނ�Ǎ�
	}
	else if (rString == "IDOL_EMO")
	{
		*pFile >> str;								// ����Ǎ�
		*pFile >> pBuffFaceText->m_nTypeIdolEmo;	// �ҋ@���̕\���ނ�Ǎ�
	}
}
