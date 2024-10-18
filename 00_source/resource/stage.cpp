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
#include "fade.h"
#include "camera.h"
#include "collision.h"

#include "tileMap.h"
#include "tileColl.h"
#include "tileSpawn.h"
#include "tileTrans.h"

#include "sceneGame.h"
#include "player.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const char *INIT_PASS = "data\\ROOM\\room004.txt";	// �Z�b�g�A�b�v�e�L�X�g���΃p�X	// TODO�F���̒萔���O���ǂݍ��݂ł���悤�ɂ��Ȃ���
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

	// ���蓖�Ă��X�e�[�W��ۑ�
	m_sNextRoomPath = INIT_PASS;

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
//	�J�ڐ惋�[���̐ݒ菈��
//============================================================
void CStage::SetFadeRoom(const char *pRoomPath)
{
	CFade *pFade = GET_MANAGER->GetFade();	// �t�F�[�h���

	// ���[���p�X�̕ۑ�
	m_sPrevRoomPath = m_sNextRoomPath;	// �J�ڌ�
	m_sNextRoomPath = pRoomPath;		// �J�ڐ�

	// �J�ڐ惋�[���̐ݒ�
	pFade->SetRoomFade();
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
//	�X�e�[�W��������
//============================================================
HRESULT CStage::BindStage(const char *pStagePath)
{
	// ���x���^�C���̃I�u�W�F�N�g�S�j��
	CObject::ReleaseAll(CObject::LABEL_TILE);

	// TODO�F��ŏ���
	CTileColl::Create(CTileColl::TYPE_TRIANGLE,	D3DXVECTOR3(SIZE_TILE * -2.0f, SIZE_TILE * 2.0f, -1.0f));
	CTileColl::Create(CTileColl::TYPE_BOX,		D3DXVECTOR3(SIZE_TILE *  0.0f, SIZE_TILE * 2.0f, -1.0f));
	CTileColl::Create(CTileColl::TYPE_TRIANGLE,	D3DXVECTOR3(SIZE_TILE *  2.0f, SIZE_TILE * 2.0f, -1.0f));

	// �t�@�C�����J��
	std::ifstream file(pStagePath);	// �t�@�C���X�g���[��
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

		// �}�b�v�^�C�����̓Ǎ�
		else if (FAILED(LoadMap(&file, str)))
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
//	�X�e�[�W�͈͏��̓Ǎ�����
//============================================================
HRESULT CStage::LoadLimit(std::ifstream *pFile, std::string& rString)
{
	// �t�@�C���X�g���[�������ݒ�̏ꍇ������
	if (pFile == nullptr) { assert(false); return E_FAIL; }

	// �Ǎ��J�n�ʒu�ł͂Ȃ��ꍇ������
	if (rString != "LIMITSET") { return S_OK; }

	// �X�e�[�W�͈͂̐ݒ�
	std::string str;	// �Ǎ�������
	SLimit limit;		// �X�e�[�W�͈͂̑���p
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

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�}�b�v�^�C�����̓Ǎ�����
//============================================================
HRESULT CStage::LoadMap(std::ifstream *pFile, std::string& rString)
{
	// �t�@�C���X�g���[�������ݒ�̏ꍇ������
	if (pFile == nullptr) { assert(false); return E_FAIL; }

	// �Ǎ��J�n�ʒu�ł͂Ȃ��ꍇ������
	if (rString != "MAPSET") { return S_OK; }

	// �}�b�v�^�C���̐ݒ�
	std::string str;	// �Ǎ�������
	do { // END_MAPSET��ǂݍ��ނ܂Ń��[�v

		// �������ǂݍ���
		*pFile >> str;

		if (str == "MAP")
		{
			D3DXVECTOR3 pos = VEC3_ZERO;	// �ʒu
			int nType = 0;					// ���
			do { // END_MAP��ǂݍ��ނ܂Ń��[�v

				// �������ǂݍ���
				*pFile >> str;

				if (str.front() == '#')
				{ // �R�����g�A�E�g����Ă���ꍇ

					// ��s�S�ēǂݍ���
					std::getline(*pFile, str);
				}
				else if (str == "TYPE")
				{
					*pFile >> str;		// ����Ǎ�
					*pFile >> nType;	// ��ނ�Ǎ�
				}
				else if (str == "POS")
				{
					*pFile >> str;		// ����Ǎ�
					*pFile >> pos.x;	// �ʒuX��Ǎ�
					*pFile >> pos.y;	// �ʒuY��Ǎ�
					*pFile >> pos.z;	// �ʒuZ��Ǎ�
				}
			} while (str != "END_MAP");	// END_MAP��ǂݍ��ނ܂Ń��[�v

			// �}�b�v�^�C���̐���
			if (CTileMap::Create((CTileMap::EType)nType, pos) == nullptr)
			{ // �����Ɏ��s�����ꍇ

				// ���s��Ԃ�
				assert(false);
				return E_FAIL;
			}
		}
	} while (str != "END_MAPSET");	// END_MAPSET��ǂݍ��ނ܂Ń��[�v

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

	// �Ǎ��J�n�ʒu�ł͂Ȃ��ꍇ������
	if (rString != "SPAWNSET") { return S_OK; }

	// �o���^�C���̐ݒ�
	std::string str;	// �Ǎ�������
	do { // END_SPAWNSET��ǂݍ��ނ܂Ń��[�v

		// �������ǂݍ���
		*pFile >> str;

		if (str == "SPAWN")
		{
			std::string passPrev;			// �J�ڌ����[���p�X
			D3DXVECTOR3 pos = VEC3_ZERO;	// �ʒu
			CPlayer::EAngle angle = (CPlayer::EAngle)0;	// �p�x
			do { // END_SPAWN��ǂݍ��ނ܂Ń��[�v

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
					*pFile >> passPrev;	// �J�ڌ��̃��[���p�X��Ǎ�

					// ���[���p�X��W����
					useful::StandardizePathPart(&passPrev);
				}
				else if (str == "POS")
				{
					*pFile >> str;		// ����Ǎ�
					*pFile >> pos.x;	// �ʒuX��Ǎ�
					*pFile >> pos.y;	// �ʒuY��Ǎ�
					*pFile >> pos.z;	// �ʒuZ��Ǎ�
				}
				else if (str == "ANGLE")
				{
					*pFile >> str;	// ����Ǎ�
					*pFile >> str;	// �p�x��Ǎ�

					// �ǂݍ��񂾊p�x��ۑ�
					if		(str == "UP")	 { angle = CPlayer::ANGLE_UP; }		// ��
					else if	(str == "DOWN")	 { angle = CPlayer::ANGLE_DOWN; }	// ��
					else if	(str == "LEFT")	 { angle = CPlayer::ANGLE_LEFT; }	// ��
					else if	(str == "RIGHT") { angle = CPlayer::ANGLE_RIGHT; }	// �E
				}
			} while (str != "END_SPAWN");	// END_SPAWN��ǂݍ��ނ܂Ń��[�v

			// �o���^�C���̐���
			if (CTileSpawn::Create(passPrev.c_str(), pos) == nullptr)
			{ // �����Ɏ��s�����ꍇ

				// ���s��Ԃ�
				assert(false);
				return E_FAIL;
			}

			// �v���C���[�o����̐ݒ�
			if (passPrev == m_sPrevRoomPath)
			{ // �^�C���̓Ǎ��p�X�ƃ��[���̑J�ڌ��p�X�������ꍇ

				// �v���C���[�̕����J��
				CSceneGame::GetPlayer()->TransRoom(pos, angle);
			}
		}
	} while (str != "END_SPAWNSET");	// END_SPAWNSET��ǂݍ��ނ܂Ń��[�v

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

	// �Ǎ��J�n�ʒu�ł͂Ȃ��ꍇ������
	if (rString != "TRANSSET") { return S_OK; }

	// �J�ڃ^�C���̐ݒ�
	std::string str;	// �Ǎ�������
	do { // END_TRANSSET��ǂݍ��ނ܂Ń��[�v

		// �������ǂݍ���
		*pFile >> str;

		if (str == "TRANS")
		{
			std::string passNext;			// �J�ڐ惋�[���p�X
			D3DXVECTOR3 pos = VEC3_ZERO;	// �ʒu
			do { // END_TRANS��ǂݍ��ނ܂Ń��[�v

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
					*pFile >> passNext;	// �J�ڐ�̃��[���p�X��Ǎ�

					// ���[���p�X��W����
					useful::StandardizePathPart(&passNext);
				}
				else if (str == "POS")
				{
					*pFile >> str;		// ����Ǎ�
					*pFile >> pos.x;	// �ʒuX��Ǎ�
					*pFile >> pos.y;	// �ʒuY��Ǎ�
					*pFile >> pos.z;	// �ʒuZ��Ǎ�
				}
			} while (str != "END_TRANS");	// END_TRANS��ǂݍ��ނ܂Ń��[�v

			// �J�ڃ^�C���̐���
			if (CTileTrans::Create(passNext.c_str(), pos) == nullptr)
			{ // �����Ɏ��s�����ꍇ

				// ���s��Ԃ�
				assert(false);
				return E_FAIL;
			}
		}
	} while (str != "END_TRANSSET");	// END_TRANSSET��ǂݍ��ނ܂Ń��[�v

	// ������Ԃ�
	return S_OK;
}