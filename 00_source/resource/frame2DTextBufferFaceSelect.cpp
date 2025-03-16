//============================================================
//
//	�\��/�I��t���e�L�X�g�ۑ��o�b�t�@���� [frame2DTextBufferFaceSelect.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "frame2DTextBufferFaceSelect.h"
#include "frame2DTextStateFaceSelect.h"

//************************************************************
//	�q�N���X [CFrame2DTextBufferFaceSelect] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CFrame2DTextBufferFaceSelect::CFrame2DTextBufferFaceSelect(const int nIdxFace) :
	m_nIdxFace		(nIdxFace),	// ��C���f�b�N�X
	m_nTypeTalkEmo	(0),		// ��b���̕\����
	m_nTypeIdolEmo	(0)			// �ҋ@���̕\����
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CFrame2DTextBufferFaceSelect::~CFrame2DTextBufferFaceSelect()
{

}

//============================================================
//	�e�L�X�g�@�\��Ԃ̐�������
//============================================================
CFrame2DTextState* CFrame2DTextBufferFaceSelect::CreateState()
{
	// �\��/�I��t���e�L�X�g��Ԃ𐶐����Ԃ�
	return new CFrame2DTextStateFaceSelect;
}

//============================================================
//	�o�b�t�@���Ƃ̃Z�b�g�A�b�v����
//============================================================
void CFrame2DTextBufferFaceSelect::LoadSetup(std::ifstream* pFile, const std::string& rString)
{
	// ���o�b�t�@�̃Z�b�g�A�b�v
	CFrame2DTextBufferSelect::LoadSetup(pFile, rString);

	// �t�@�C���|�C���^���Ȃ��ꍇ������
	if (pFile == nullptr) { assert(false); return; }

	// �J���ĂȂ��t�@�C���̏ꍇ������
	if (!pFile->is_open()) { assert(false); return; }

	// �\��/�I��t���e�L�X�g�ۑ��o�b�t�@�ɕϊ��ł��Ȃ��ꍇ������
	CFrame2DTextBufferFaceSelect* pBuffFaceSelect = GetBufferFaceSelect();
	if (pBuffFaceSelect == nullptr) { assert(false); return; }

	// �t�@�C����Ǎ�
	std::string str;	// �Ǎ�������
	if (rString == "TALK_EMO")
	{
		*pFile >> str;								// ����Ǎ�
		*pFile >> pBuffFaceSelect->m_nTypeTalkEmo;	// ��b���̕\���ނ�Ǎ�
	}
	else if (rString == "IDOL_EMO")
	{
		*pFile >> str;								// ����Ǎ�
		*pFile >> pBuffFaceSelect->m_nTypeIdolEmo;	// �ҋ@���̕\���ނ�Ǎ�
	}
}
