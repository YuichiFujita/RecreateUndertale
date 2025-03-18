//============================================================
//
//	�e�L�X�g���ۑ��o�b�t�@���� [frame2DTextBuffer.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "frame2DTextBuffer.h"

//************************************************************
//	�e�N���X [CFrame2DTextBuffer] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CFrame2DTextBuffer::CFrame2DTextBuffer() :
	m_font	(CFrame2DModuleText::FONT_DEFAULT),		// �t�H���g
	m_sound	(CFrame2DModuleText::SOUND_DEFAULT),	// �T�E���h
	m_sPath	(""),	// �e�L�X�g�ۑ��p�X
	m_sKey	(""),	// �e�L�X�g�����L�[
	m_text	({})	// �e�L�X�g�ۑ�
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CFrame2DTextBuffer::~CFrame2DTextBuffer()
{

}

//============================================================
//	�o�b�t�@���Ƃ̃Z�b�g�A�b�v����
//============================================================
void CFrame2DTextBuffer::LoadSetup(std::ifstream* pFile, const std::string& rString)
{
	// �t�@�C���|�C���^���Ȃ��ꍇ������
	if (pFile == nullptr) { assert(false); return; }

	// �J���ĂȂ��t�@�C���̏ꍇ������
	if (!pFile->is_open()) { assert(false); return; }

	// �t�@�C����Ǎ�
	std::string str;	// �Ǎ�������
	if (rString == "FONT")
	{
		int nCastFont = 0;		// EFont�^�ϊ�
		*pFile >> str;			// ����Ǎ�
		*pFile >> nCastFont;	// �t�H���g��Ǎ�

		// �ǂݍ��񂾒l��EFont�^�ɕϊ�
		assert(nCastFont > NONE_IDX && nCastFont < CFrame2DModuleText::FONT_MAX);
		m_font = (CFrame2DModuleText::EFont)nCastFont;
	}
	else if (rString == "SOUND")
	{
		int nCastSound = 0;		// ESound�^�ϊ�
		*pFile >> str;			// ����Ǎ�
		*pFile >> nCastSound;	// �T�E���h��Ǎ�

		// �ǂݍ��񂾒l��ESound�^�ɕϊ�
		assert(nCastSound > NONE_IDX && nCastSound < CFrame2DModuleText::SOUND_MAX);
		m_sound = (CFrame2DModuleText::ESound)nCastSound;
	}
}
