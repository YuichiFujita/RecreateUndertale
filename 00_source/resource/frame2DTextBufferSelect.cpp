//============================================================
//
//	�I��t���e�L�X�g�ۑ��o�b�t�@���� [frame2DTextBufferSelect.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "frame2DTextBufferSelect.h"
#include "frame2DModuleTextSelect.h"

//************************************************************
//	�q�N���X [CFrame2DTextBufferSelect] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CFrame2DTextBufferSelect::CFrame2DTextBufferSelect()
{
	// �����o�ϐ����N���A
	for (int i = 0; i < CFrame2DModuleTextSelect::SELECT_MAX; i++)
	{ // �I�����̑������J��Ԃ�

		m_aNextTextKey[i] = {};	// ���e�L�X�g�̌����L�[
		m_aSelect[i] = {};		// �I���e�L�X�g�ۑ�
	}
}

//============================================================
//	�f�X�g���N�^
//============================================================
CFrame2DTextBufferSelect::~CFrame2DTextBufferSelect()
{

}

//============================================================
//	�e�L�X�g�@�\�̐�������
//============================================================
CFrame2DModule* CFrame2DTextBufferSelect::CreateModule(const CFrame2D::EPreset preset)
{
	// �I��t���e�L�X�g�\���@�\�𐶐����Ԃ�
	return new CFrame2DModuleTextSelect(preset);
}

//============================================================
//	���݃L�[�̕�����Ǎ�����
//============================================================
void CFrame2DTextBufferSelect::LoadKeyString(std::ifstream* pFile, std::string& rString)
{
	// �t�@�C���|�C���^���Ȃ��ꍇ������
	if (pFile == nullptr) { assert(false); return; }

	// �J���ĂȂ��t�@�C���̏ꍇ������
	if (!pFile->is_open()) { assert(false); return; }

	if (rString == "SELECT_LEFT")
	{
		// �I����������̓Ǎ�
		LoadSelect(pFile, CFrame2DModuleTextSelect::SELECT_LEFT);
	}
	else if (rString == "SELECT_RIGHT")
	{
		// �I����������̓Ǎ�
		LoadSelect(pFile, CFrame2DModuleTextSelect::SELECT_RIGHT);
	}
}

//============================================================
//	�I����������̓Ǎ�����
//============================================================
void CFrame2DTextBufferSelect::LoadSelect(std::ifstream* pFile, const CFrame2DModuleTextSelect::ESelect select)
{
	// �t�@�C���|�C���^���Ȃ��ꍇ������
	if (pFile == nullptr) { assert(false); return; }

	// �J���ĂȂ��t�@�C���̏ꍇ������
	if (!pFile->is_open()) { assert(false); return; }

	// �I��t���e�L�X�g�ۑ��|�C���^�ɕϊ��ł��Ȃ��ꍇ������
	CFrame2DTextBufferSelect* pSelect = GetBufferSelect();
	if (pSelect == nullptr) { assert(false); return; }

	// �t�@�C����Ǎ�
	std::string str;	// �Ǎ�������
	do { // END_SELECT��ǂݍ��ނ܂Ń��[�v

		// �������ǂݍ���
		*pFile >> str;

		if (str.front() == '#') { std::getline(*pFile, str); }	// �R�����g�A�E�g
		else if (str == "NEXT")
		{
			*pFile >> str;						// ����Ǎ�
			*pFile >> m_aNextTextKey[select];	// ���e�L�X�g�̌����L�[��Ǎ�
		}
		else if (str == "STR")
		{
			*pFile >> str;					// ����Ǎ�
			pFile->seekg(1, std::ios::cur);	// �Ǎ��ʒu���󔒕����炷
			std::getline(*pFile, str);		// ��s�S�ēǂݍ���

			// ������̐擪�ɋ󔒂�ǉ�
			str.insert(0, " ");

			// ��������Ō���ɒǉ�
			pSelect->m_aSelect[select].push_back(str);
		}
	} while (str != "END_SELECT");	// END_SELECT��ǂݍ��ނ܂Ń��[�v
}