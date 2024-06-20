//============================================================
//
//	�e�L�X�g�Ǎ��֐����� [loadtext.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "loadtext.h"
#include "text2D.h"
#include "string2D.h"

//============================================================
//	������z��̓Ǎ�����
//============================================================
void loadtext::LoadVector(std::ifstream *pFile, std::vector<std::wstring> *pVecStr)
{
	// ���I�z��|�C���^���Ȃ��ꍇ������
	if (pVecStr == nullptr) { assert(false); return; }

	// �t�@�C���|�C���^���Ȃ��ꍇ������
	if (pFile == nullptr)	{ assert(false); return; }

	// �J���ĂȂ��t�@�C���̏ꍇ������
	if (!pFile->is_open())	{ assert(false); return; }

	std::string sStr;	// �Ǎ�������
	do { // END_TEXT��ǂݍ��ނ܂Ń��[�v

		// �������ǂݍ���
		*pFile >> sStr;

		if (sStr.front() == '#')
		{ // �R�����g�A�E�g����Ă���ꍇ

			// ��s�S�ēǂݍ���
			std::getline(*pFile, sStr);
		}
		else if (sStr == "STR")
		{
			*pFile >> sStr;					// ����Ǎ�
			pFile->seekg(1, std::ios::cur);	// �Ǎ��ʒu���󔒕����炷
			std::getline(*pFile, sStr);		// ��s�S�ēǂݍ���

			// ��������Ō���ɒǉ�
			pVecStr->push_back(useful::MultiByteToWide(sStr));	// ���C�h������ɕϊ�
		}

	} while (sStr != "END_TEXT");	// END_TEXT��ǂݍ��ނ܂Ń��[�v
}

//============================================================
//	�e�L�X�g�̓Ǎ����� (������)
//============================================================
std::vector<std::wstring> loadtext::LoadText(const char *pFilePass, const char *pTextStr)
{
	std::vector<std::wstring> vecStr;	// ������̓��I�z��
	std::string sLoadStart;				// �Ǎ��J�n�̕�����

	// �Ǎ��̊J�n��������쐬
	sLoadStart = "TEXT_";			// �F���p�̐擪������ݒ�
	sLoadStart.append(pTextStr);	// �����̔F���p������ƘA��

	// �t�@�C�����J��
	std::ifstream file(pFilePass);	// �t�@�C���X�g���[��
	if (file.fail())
	{ // �t�@�C�����J���Ȃ������ꍇ

		// �G���[���b�Z�[�W�{�b�N�X
		MessageBox(nullptr, "�e�L�X�g�t�@�C���̓ǂݍ��݂Ɏ��s�I", "�x���I", MB_ICONWARNING);

		// �����l��Ԃ�
		return vecStr;
	}

	// �t�@�C����Ǎ�
	std::string sStr;	// �Ǎ�������
	while (file >> sStr)
	{ // �t�@�C���̏I�[�ł͂Ȃ��ꍇ���[�v

		if (sStr.front() == '#')
		{ // �R�����g�A�E�g����Ă���ꍇ

			// ��s�S�ēǂݍ���
			std::getline(file, sStr);
		}
		else if (sStr == "TEXT_ELSE")
		{ // �ėp�I�ȓǍ��J�n�̕�����ƈ�v�����ꍇ

			// ������̓��I�z���Ǎ�
			LoadVector(&file, &vecStr);
		}
		else if (sStr == sLoadStart)
		{ // �Ǎ��J�n�̕�����ƈ�v�����ꍇ

			// ������̓��I�z���Ǎ�
			LoadVector(&file, &vecStr);

			break;	// ELSE��ǂݍ��܂Ȃ��悤�J��Ԃ����甲����
		}
	}

	// �t�@�C�������
	file.close();

	// ������̓��I�z���Ԃ�
	return vecStr;
}

//============================================================
//	�e�L�X�g�̓Ǎ����� (�C���f�b�N�X)
//============================================================
std::vector<std::wstring> loadtext::LoadText(const char *pFilePass, const int nTextID)
{
	// �e�L�X�g�̓Ǎ�
	return LoadText(pFilePass, std::to_string(nTextID).c_str());
}

//============================================================
//	�e�L�X�g�̊�������
//============================================================
void loadtext::BindText(CText2D *pText2D, const std::vector<std::wstring>& rVecStr)
{
	for (int i = 0; i < (int)rVecStr.size(); i++)
	{ // �����񐔕��J��Ԃ�

		// �������ǉ�
		pText2D->AddString(rVecStr[i]);
	}
}

//============================================================
//	������̊�������
//============================================================
void loadtext::BindString(CString2D *pString2D, const std::vector<std::wstring> &rVecStr)
{
	// �����񂪈�ł͂Ȃ��ꍇ�G���[
	assert((int)rVecStr.size() == 1);

	// �������ݒ�
	pString2D->SetString(rVecStr[0]);
}
