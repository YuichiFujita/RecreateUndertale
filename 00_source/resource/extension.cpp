//============================================================
//
//	�g���q����֐����� [extension.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "extension.h"

//============================================================
//	�Ǎ��\�g���q�̓Ǎ�����
//============================================================
extension::ALoad extension::LoadExtension(const char* pFilePath)
{
	ALoad vecLoad;	// �g���q�̓��I�z��

	// �t�@�C�����J��
	std::ifstream file(pFilePath);	// �t�@�C���X�g���[��
	if (file.fail())
	{ // �t�@�C�����J���Ȃ������ꍇ

		// �G���[���b�Z�[�W�{�b�N�X
		MessageBox(nullptr, "�g���q�t�@�C���̓ǂݍ��݂Ɏ��s�I", "�x���I", MB_ICONWARNING);

		// �����l��Ԃ�
		return vecLoad;
	}

	// �t�@�C����Ǎ�
	std::string str;	// �Ǎ�������
	while (file >> str)
	{ // �t�@�C���̏I�[�ł͂Ȃ��ꍇ���[�v

		if (str.front() == '#')
		{ // �R�����g�A�E�g����Ă���ꍇ

			// ��s�S�ēǂݍ���
			std::getline(file, str);
		}
		else if (str == "EXTENSION")
		{
			file >> str;	// ����Ǎ�
			file >> str;	// �Ǎ��\�Ȋg���q��Ǎ�

			// �ǂݍ��񂾊g���q���Ō���ɒǉ�
			vecLoad.push_back(str);
		}
	}

	// �t�@�C�������
	file.close();

	// �g���q�̓��I�z���Ԃ�
	return vecLoad;
}

//============================================================
//	�Ǎ��\�t���O�̎擾����
//============================================================
bool extension::IsLoadOK(const ALoad& rLoadInfo, const char* pLoadFilePath)
{
	std::filesystem::path fsFullPath = pLoadFilePath;			// �t�@�C���p�X
	std::filesystem::path fsExtension = fsFullPath.extension();	// �g���q

	int nSize = (int)rLoadInfo.size();	// �ǂݍ��߂�g���q�̑���
	for (int i = 0; i < nSize; i++)
	{ //  �ǂݍ��߂�g���q�̑������J��Ԃ�

		// �g���q���Ǎ��\�Ȍ`�����������ꍇ������
		if (fsExtension == rLoadInfo[i]) { return true; }
	}

	// �ǂݍ��݉\�g���q������Ȃ��ꍇ������
	return false;
}
