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
//	�e�L�X�g�̓Ǎ�����
//============================================================
std::vector<std::wstring> loadtext::LoadText(const char *pFilePass, const int nTextID)
{
	std::vector<std::wstring> vecStr;	// ������̓��I�z��
	std::string sLoadStart;				// �Ǎ��J�n�̕�����

	// �Ǎ��̊J�n��������쐬
	sLoadStart = "TEXT_" + std::to_string(nTextID);	// �����̃C���f�b�N�X�ƍ��킹��

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
		else if (sStr == sLoadStart)
		{ // �Ǎ��J�n�̕�����ƈ�v�����ꍇ

			do
			{ // END_TEXT��ǂݍ��ނ܂Ń��[�v

				// �������ǂݍ���
				file >> sStr;

				if (sStr.front() == '#')
				{ // �R�����g�A�E�g����Ă���ꍇ

					// ��s�S�ēǂݍ���
					std::getline(file, sStr);
				}
				else if (sStr == "STR")
				{
					file >> sStr;					// ����Ǎ�
					file.seekg(1, std::ios::cur);	// �Ǎ��ʒu���󔒕����炷
					std::getline(file, sStr);		// ��s�S�ēǂݍ���

					// ��������Ō���ɒǉ�
					vecStr.push_back(useful::MultiByteToWide(&sStr));	// ���C�h������ɕϊ�
				}
			} while (sStr != "END_TEXT");	// END_TEXT��ǂݍ��ނ܂Ń��[�v
		}
	}

	// �t�@�C�������
	file.close();

	// ������̓��I�z���Ԃ�
	return vecStr;
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
