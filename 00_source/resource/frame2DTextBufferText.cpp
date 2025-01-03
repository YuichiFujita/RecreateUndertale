//============================================================
//
//	�e�L�X�g�ۑ��o�b�t�@���� [frame2DTextBufferText.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "frame2DTextBufferText.h"
#include "frame2DModuleText.h"

//************************************************************
//	�q�N���X [CFrame2DTextBufferText] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CFrame2DTextBufferText::CFrame2DTextBufferText() :
	m_sNextTextKey	({})	// ���e�L�X�g�̌����L�[
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CFrame2DTextBufferText::~CFrame2DTextBufferText()
{

}

//============================================================
//	�e�L�X�g�@�\�̐�������
//============================================================
CFrame2DModule* CFrame2DTextBufferText::CreateModule(const CFrame2D::EPreset preset)
{
	// �e�L�X�g�\���@�\�𐶐����Ԃ�
	return new CFrame2DModuleText(preset);
}

//============================================================
//	���݃L�[�̕�����Ǎ�����
//============================================================
void CFrame2DTextBufferText::LoadKeyString(std::ifstream* pFile, std::string& rString)
{
	// �t�@�C���|�C���^���Ȃ��ꍇ������
	if (pFile == nullptr) { assert(false); return; }

	// �J���ĂȂ��t�@�C���̏ꍇ������
	if (!pFile->is_open()) { assert(false); return; }

	std::string str;	// �Ǎ�������
	if (rString == "NEXT")
	{
		*pFile >> str;				// ����Ǎ�
		*pFile >> m_sNextTextKey;	// ���e�L�X�g�̌����L�[��Ǎ�
	}
}
