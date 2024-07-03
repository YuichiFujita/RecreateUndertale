//============================================================
//
//	�X�e�[�W���� [stage.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "stage.h"
#include "manager.h"
#include "texture.h"
#include "collision.h"

#include "tileSpawn.h"
#include "tileTrans.h"

#include "sceneGame.h"
#include "player.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const char *INIT_PASS = "data\\ROOM\\room004.txt";	// �Z�b�g�A�b�v�e�L�X�g���΃p�X
}

//************************************************************
//	�e�N���X [CStage] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CStage::CStage()
{
	// �����o�ϐ����N���A
	memset(&m_limit, 0, sizeof(m_limit));	// �X�e�[�W�͈�
}

//============================================================
//	�f�X�g���N�^
//============================================================
CStage::~CStage()
{

}

//============================================================
//	����������
//============================================================
HRESULT CStage::Init(void)
{
	// �����o�ϐ���������
	memset(&m_limit, 0, sizeof(m_limit));	// �X�e�[�W�͈�

	// �X�e�[�W�̊���
	if (FAILED(BindStage(INIT_PASS)))
	{ // �Ǎ��Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CStage::Uninit(void)
{

}

//============================================================
//	�X�e�[�W��������
//============================================================
HRESULT CStage::BindStage(const char *pStagePass)
{
	// �t�@�C�����J��
	std::ifstream file(pStagePass);	// �t�@�C���X�g���[��
	if (file.fail())
	{ // �t�@�C�����J���Ȃ������ꍇ

		// �G���[���b�Z�[�W�{�b�N�X
		MessageBox(nullptr, "�X�e�[�W�Z�b�g�A�b�v�̓ǂݍ��݂Ɏ��s�I", "�x���I", MB_ICONWARNING);

		// ���s��Ԃ�
		return E_FAIL;
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

		// �X�e�[�W�͈͏��̓Ǎ�
		else if (FAILED(LoadLimit(&file, str)))
		{ // �Ǎ��Ɏ��s�����ꍇ

			// ���s��Ԃ�
			assert(false);
			return E_FAIL;
		}

		// �o���^�C�����̓Ǎ�
		else if (FAILED(LoadSpawn(&file, str)))
		{ // �Ǎ��Ɏ��s�����ꍇ

			// ���s��Ԃ�
			assert(false);
			return E_FAIL;
		}

		// �J�ڃ^�C�����̓Ǎ�
		else if (FAILED(LoadTrans(&file, str)))
		{ // �Ǎ��Ɏ��s�����ꍇ

			// ���s��Ԃ�
			assert(false);
			return E_FAIL;
		}
	}

	// �t�@�C�������
	file.close();

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�ʒu�̕␳����
//============================================================
void CStage::LimitPosition(D3DXVECTOR3& rPos, const float fRadius)
{
	// XY���ʊp���̓�������
	collision::InBoxPillarXY
	( // ����
		rPos,				// ����ʒu
		VEC3_ZERO,			// ���茴�_�ʒu
		VEC3_ALL(fRadius),	// ����T�C�Y(�E�E��E��)
		VEC3_ALL(fRadius),	// ����T�C�Y(���E���E�O)
		D3DXVECTOR3(fabsf(m_limit.fRight), fabsf(m_limit.fUp), 0.0f),	// ���茴�_�T�C�Y(�E�E��E��)
		D3DXVECTOR3(fabsf(m_limit.fLeft), fabsf(m_limit.fDown), 0.0f)	// ���茴�_�T�C�Y(���E���E�O)
	);
}

//============================================================
//	��������
//============================================================
CStage *CStage::Create(void)
{
	// �X�e�[�W�̐���
	CStage *pStage = new CStage;
	if (pStage == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �X�e�[�W�̏�����
		if (FAILED(pStage->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �X�e�[�W�̔j��
			SAFE_DELETE(pStage);
			return nullptr;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return pStage;
	}
}

//============================================================
//	�j������
//============================================================
void CStage::Release(CStage *&prStage)
{
	// �X�e�[�W�̏I��
	assert(prStage != nullptr);
	prStage->Uninit();

	// �������J��
	SAFE_DELETE(prStage);
}

//============================================================
//	�X�e�[�W�͈͏��̓Ǎ�����
//============================================================
HRESULT CStage::LoadLimit(std::ifstream *pFile, std::string& rString)
{
	// �t�@�C���X�g���[�������ݒ�̏ꍇ������
	if (pFile == nullptr) { assert(false); return E_FAIL; }

	// �X�e�[�W�͈͂̐ݒ�
	if (rString == "LIMITSET")
	{
		SLimit limit;		// �X�e�[�W�͈͂̑���p
		std::string str;	// �Ǎ�������

		do { // END_LIMITSET��ǂݍ��ނ܂Ń��[�v

			// �������ǂݍ���
			*pFile >> str;

			if (str.front() == '#')
			{ // �R�����g�A�E�g����Ă���ꍇ

				// ��s�S�ēǂݍ���
				std::getline(*pFile, str);
			}
			else if (str == "UP")
			{
				*pFile >> str;			// ����Ǎ�
				*pFile >> limit.fUp;	// ��ʒu��Ǎ�
			}
			else if (str == "DOWN")
			{
				*pFile >> str;			// ����Ǎ�
				*pFile >> limit.fDown;	// ���ʒu��Ǎ�
			}
			else if (str == "LEFT")
			{
				*pFile >> str;			// ����Ǎ�
				*pFile >> limit.fLeft;	// ���ʒu��Ǎ�
			}
			else if (str == "RIGHT")
			{
				*pFile >> str;			// ����Ǎ�
				*pFile >> limit.fRight;	// �E�ʒu��Ǎ�
			}
		} while (str != "END_LIMITSET");	// END_LIMITSET��ǂݍ��ނ܂Ń��[�v

		// �X�e�[�W�͈͂̐ݒ�
		SetLimit(limit);
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�o���^�C�����̓Ǎ�����
//============================================================
HRESULT CStage::LoadSpawn(std::ifstream *pFile, std::string& rString)
{
	// �t�@�C���X�g���[�������ݒ�̏ꍇ������
	if (pFile == nullptr) { assert(false); return E_FAIL; }

	// �o���^�C���̐ݒ�
	if (rString == "SPAWNSET")
	{
		std::string str;	// �Ǎ�������
		std::string pass;	// �J�ڑO���[���p�X
		D3DXVECTOR3 pos;	// �ʒu

		do { // END_SPAWNSET��ǂݍ��ނ܂Ń��[�v

			// �������ǂݍ���
			*pFile >> str;

			if (str.front() == '#')
			{ // �R�����g�A�E�g����Ă���ꍇ

				// ��s�S�ēǂݍ���
				std::getline(*pFile, str);
			}
			else if (str == "PREV_ROOMPASS")
			{
				*pFile >> str;		// ����Ǎ�
				*pFile >> pass;		// �J�ڑO�̃��[���p�X��Ǎ�

				// ���[���p�X��W����
				useful::StandardizePathPart(&pass);
			}
			else if (str == "POS")
			{
				*pFile >> str;		// ����Ǎ�
				*pFile >> pos.x;	// �ʒuX��Ǎ�
				*pFile >> pos.y;	// �ʒuY��Ǎ�
				*pFile >> pos.z;	// �ʒuZ��Ǎ�
			}
		} while (str != "END_SPAWNSET");	// END_SPAWNSET��ǂݍ��ނ܂Ń��[�v

		// �o���^�C���̐���
		if (CTileSpawn::Create(pass.c_str(), pos) == nullptr)
		{ // �����Ɏ��s�����ꍇ

			// ���s��Ԃ�
			assert(false);
			return E_FAIL;
		}

		if (INIT_PASS == pass)
		{
			// TODO
			CSceneGame::GetPlayer()->SetVec3Position(pos);
		}
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�J�ڃ^�C�����̓Ǎ�����
//============================================================
HRESULT CStage::LoadTrans(std::ifstream *pFile, std::string& rString)
{
	// �t�@�C���X�g���[�������ݒ�̏ꍇ������
	if (pFile == nullptr) { assert(false); return E_FAIL; }

	// �J�ڃ^�C���̐ݒ�
	if (rString == "TRANSSET")
	{
		std::string str;	// �Ǎ�������
		std::string pass;	// �J�ڐ惋�[���p�X
		D3DXVECTOR3 pos;	// �ʒu

		do { // END_TRANSSET��ǂݍ��ނ܂Ń��[�v

			// �������ǂݍ���
			*pFile >> str;

			if (str.front() == '#')
			{ // �R�����g�A�E�g����Ă���ꍇ

				// ��s�S�ēǂݍ���
				std::getline(*pFile, str);
			}
			else if (str == "NEXT_ROOMPASS")
			{
				*pFile >> str;		// ����Ǎ�
				*pFile >> pass;		// �J�ڐ�̃��[���p�X��Ǎ�

				// ���[���p�X��W����
				useful::StandardizePathPart(&pass);
			}
			else if (str == "POS")
			{
				*pFile >> str;		// ����Ǎ�
				*pFile >> pos.x;	// �ʒuX��Ǎ�
				*pFile >> pos.y;	// �ʒuY��Ǎ�
				*pFile >> pos.z;	// �ʒuZ��Ǎ�
			}
		} while (str != "END_TRANSSET");	// END_TRANSSET��ǂݍ��ނ܂Ń��[�v

		// �J�ڃ^�C���̐���
		if (CTileTrans::Create(pass.c_str(), pos) == nullptr)
		{ // �����Ɏ��s�����ꍇ

			// ���s��Ԃ�
			assert(false);
			return E_FAIL;
		}
	}

	// ������Ԃ�
	return S_OK;
}