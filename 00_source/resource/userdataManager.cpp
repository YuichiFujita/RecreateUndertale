//============================================================
//
//	���[�U�[�f�[�^�}�l�[�W���[���� [userdataManager.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "userdataManager.h"
#include "manager.h"
#include "playerStatus.h"
#include "playerItem.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const char* FILE0_TXT		= "data\\TXT\\file0.txt";			// �����f�[�^�e�L�X�g���΃p�X
	const char* INIT_STATUS_TXT	= "data\\TXT\\init_status.txt";		// �X�e�[�^�X�������e�L�X�g���΃p�X
	const char* INIT_ITEM_TXT	= "data\\TXT\\init_item.txt";		// �����A�C�e���������e�L�X�g���΃p�X
	const char* INIT_USER_TXT	= "data\\TXT\\init_userdata.txt";	// ���[�U�[�f�[�^�������e�L�X�g���΃p�X
}

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
CUserDataManager* CUserDataManager::m_pInstance = nullptr;	// ���g�̃C���X�^���X

//************************************************************
//	�e�N���X [CUserDataManager] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CUserDataManager::CUserDataManager() :
	m_nRoom		(0),	// �����ԍ�
	m_nFun		(0),	// FUN�l
	m_fPlayTime	(0.0f)	// ���v���C����
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CUserDataManager::~CUserDataManager()
{

}

//============================================================
//	����������
//============================================================
HRESULT CUserDataManager::Init()
{
	// �����o�ϐ���������
	m_nRoom		= 0;	// �����ԍ�
	m_nFun		= 0;	// FUN�l
	m_fPlayTime	= 0.0f;	// ���v���C����

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CUserDataManager::Uninit()
{

}

//============================================================
//	�X�V����
//============================================================
void CUserDataManager::Update(const float fDeltaTime)
{
	if (GET_MANAGER->GetMode() == CScene::MODE_GAME)
	{ // �Q�[����ʂ̏ꍇ

		// ���v���C���Ԃ����Z
		m_fPlayTime += fDeltaTime;
	}
}

//============================================================
//	�v���C���[�X�e�[�^�X�̏���������
//============================================================
HRESULT CUserDataManager::InitPlayerStatus(CPlayerStatus* pStatus)
{
	// �v���C���[�X�e�[�^�X�̓Ǎ�
	if (FAILED(LoadPlayerStatus(pStatus, INIT_STATUS_TXT)))
	{ // �Ǎ��Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	�v���C���[�X�e�[�^�X�̓Ǎ�����
//============================================================
HRESULT CUserDataManager::LoadPlayerStatus(CPlayerStatus* pStatus)
{
	// �v���C���[�X�e�[�^�X�̓Ǎ�
	if (FAILED(LoadPlayerStatus(pStatus, FILE0_TXT)))
	{ // �Ǎ��Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	�v���C���[�����A�C�e���̏���������
//============================================================
HRESULT CUserDataManager::InitPlayerItem(CPlayerItem* pItem)
{
	// �v���C���[�����A�C�e���̓Ǎ�
	if (FAILED(LoadPlayerItem(pItem, INIT_ITEM_TXT)))
	{ // �Ǎ��Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	�v���C���[�����A�C�e���̓Ǎ�����
//============================================================
HRESULT CUserDataManager::LoadPlayerItem(CPlayerItem* pItem)
{
	// �v���C���[�����A�C�e���̓Ǎ�
	if (FAILED(LoadPlayerItem(pItem, FILE0_TXT)))
	{ // �Ǎ��Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	���[�U�[�f�[�^�̏���������
//============================================================
HRESULT CUserDataManager::InitUserData()
{
	// ���[�U�[�f�[�^�̓Ǎ�
	if (FAILED(LoadUserData(INIT_USER_TXT)))
	{ // �Ǎ��Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	���[�U�[�f�[�^�̓Ǎ�����
//============================================================
HRESULT CUserDataManager::LoadUserData()
{
	// ���[�U�[�f�[�^�̓Ǎ�
	if (FAILED(LoadUserData(FILE0_TXT)))
	{ // �Ǎ��Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	�����f�[�^�̏���������
//============================================================
HRESULT CUserDataManager::InitAllData
(
	CPlayerStatus* pStatus,	// �v���C���[�X�e�[�^�X���
	CPlayerItem* pItem		// �v���C���[�����A�C�e�����
)
{
	// �X�e�[�^�X�̏�����
	if (FAILED(InitPlayerStatus(pStatus)))
	{ // �������Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// �����A�C�e���̏�����
	if (FAILED(InitPlayerItem(pItem)))
	{ // �������Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// ���[�U�[�f�[�^�̏�����
	if (FAILED(InitUserData()))
	{ // �������Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	�C���X�^���X��������
//============================================================
CUserDataManager* CUserDataManager::Create()
{
	// �C���X�^���X�����ς�
	assert(m_pInstance == nullptr);

	// ���[�U�[�f�[�^�}�l�[�W���[�̐���
	m_pInstance = new CUserDataManager;
	if (m_pInstance == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// ���[�U�[�f�[�^�}�l�[�W���[�̏�����
		if (FAILED(m_pInstance->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ���[�U�[�f�[�^�}�l�[�W���[�̔j��
			SAFE_DELETE(m_pInstance);
			return nullptr;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return m_pInstance;
	}
}

//============================================================
//	�C���X�^���X�擾����
//============================================================
CUserDataManager* CUserDataManager::GetInstance()
{
	// �C���X�^���X������
	assert(m_pInstance != nullptr);

	// ���g�̃C���X�^���X��Ԃ�
	return m_pInstance;
}

//============================================================
//	�C���X�^���X�j������
//============================================================
void CUserDataManager::Release()
{
	// ���[�U�[�f�[�^�}�l�[�W���[�̏I��
	assert(m_pInstance != nullptr);
	m_pInstance->Uninit();

	// �������J��
	SAFE_DELETE(m_pInstance);
}

//============================================================
//	�v���C���[�X�e�[�^�X�̓Ǎ����� (�p�X�w��)
//============================================================
HRESULT CUserDataManager::LoadPlayerStatus(CPlayerStatus* pStatus, const char* pFilePath)
{
	// �t�@�C�����J��
	std::ifstream file(pFilePath);	// �t�@�C���X�g���[��
	if (file.fail())
	{ // �t�@�C�����J���Ȃ������ꍇ

		// �G���[���b�Z�[�W�{�b�N�X
		MessageBox(nullptr, "�v���C���[�X�e�[�^�X�̓ǂݍ��݂Ɏ��s�I", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �t�@�C����Ǎ�
	std::string str;	// �Ǎ�������
	while (file >> str)
	{ // �t�@�C���̏I�[�ł͂Ȃ��ꍇ���[�v

		if (str.front() == '#') { std::getline(file, str); }	// �R�����g�A�E�g
		else if (str == "STATUSSET")
		{
			do { // END_STATUSSET��ǂݍ��ނ܂Ń��[�v

				// �������ǂݍ���
				file >> str;

				if (str.front() == '#') { std::getline(file, str); }	// �R�����g�A�E�g
				else if (str == "NAME")
				{
					file >> str;	// ����Ǎ�
					file >> str;	// �v���C���[����Ǎ�
					pStatus->SetName(str);
				}
				else if (str == "LOVE")
				{
					int nLove;
					file >> str;	// ����Ǎ�
					file >> nLove;	// ���x����Ǎ�
					pStatus->SetLove(nLove);
				}
				else if (str == "HP")
				{
					int nHP;
					file >> str;	// ����Ǎ�
					file >> nHP;	// �̗͂�Ǎ�
					pStatus->SetHP(nHP);
				}
				else if (str == "MAX_HP")
				{
					int nMaxHP;
					file >> str;	// ����Ǎ�
					file >> nMaxHP;	// �ő�̗͂�Ǎ�
					pStatus->SetMaxHP(nMaxHP);
				}
				else if (str == "EXP")
				{
					int nExp;
					file >> str;	// ����Ǎ�
					file >> nExp;	// �o���l��Ǎ�
					pStatus->SetExp(nExp);
				}
				else if (str == "WPN_ITEMIDX")
				{
					int nItemIdx;
					file >> str;		// ����Ǎ�
					file >> nItemIdx;	// ����A�C�e���C���f�b�N�X��Ǎ�
					pStatus->SetWpnItemIdx(nItemIdx);
				}
				else if (str == "AMR_ITEMIDX")
				{
					int nItemIdx;
					file >> str;		// ����Ǎ�
					file >> nItemIdx;	// �h��A�C�e���C���f�b�N�X��Ǎ�
					pStatus->SetAmrItemIdx(nItemIdx);
				}
				else if (str == "NUM_GOLD")
				{
					int nNumGold;
					file >> str;		// ����Ǎ�
					file >> nNumGold;	// ��������Ǎ�
					pStatus->SetNumGold(nNumGold);
				}
				else if (str == "NUM_KILL")
				{
					int nNumKill;
					file >> str;		// ����Ǎ�
					file >> nNumKill;	// �E�Q����Ǎ�
					pStatus->SetNumKill(nNumKill);
				}
			} while (str != "END_STATUSSET");	// END_STATUSSET��ǂݍ��ނ܂Ń��[�v
		}
	}

	// �t�@�C�������
	file.close();

	return S_OK;
}

//============================================================
//	�v���C���[�����A�C�e���̓Ǎ����� (�p�X�w��)
//============================================================
HRESULT CUserDataManager::LoadPlayerItem(CPlayerItem* pItem, const char* pFilePath)
{
	// �t�@�C�����J��
	std::ifstream file(pFilePath);	// �t�@�C���X�g���[��
	if (file.fail())
	{ // �t�@�C�����J���Ȃ������ꍇ

		// �G���[���b�Z�[�W�{�b�N�X
		MessageBox(nullptr, "�v���C���[�����A�C�e���̓ǂݍ��݂Ɏ��s�I", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �t�@�C����Ǎ�
	std::string str;	// �Ǎ�������
	while (file >> str)
	{ // �t�@�C���̏I�[�ł͂Ȃ��ꍇ���[�v

		if (str.front() == '#') { std::getline(file, str); }	// �R�����g�A�E�g
		else if (str == "ITEMSET")
		{
			do { // END_ITEMSET��ǂݍ��ނ܂Ń��[�v

				// �������ǂݍ���
				file >> str;

				if (str.front() == '#') { std::getline(file, str); }	// �R�����g�A�E�g
				else if (str == "ITEMIDX")
				{
					int nItemIdx;
					file >> str;		// ����Ǎ�
					file >> nItemIdx;	// �A�C�e���C���f�b�N�X��Ǎ�

					// �A�C�e���C���f�b�N�X���Ō���ɒǉ�
					pItem->PushBackItem(nItemIdx);
				}
			} while (str != "END_ITEMSET");	// END_ITEMSET��ǂݍ��ނ܂Ń��[�v
		}
	}

	// �t�@�C�������
	file.close();

	return S_OK;
}

//============================================================
//	���[�U�[�f�[�^�̓Ǎ�����
//============================================================
HRESULT CUserDataManager::LoadUserData(const char* pFilePath)
{
	// �t�@�C�����J��
	std::ifstream file(pFilePath);	// �t�@�C���X�g���[��
	if (file.fail())
	{ // �t�@�C�����J���Ȃ������ꍇ

		// �G���[���b�Z�[�W�{�b�N�X
		MessageBox(nullptr, "���[�U�[�f�[�^�̓ǂݍ��݂Ɏ��s�I", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �t�@�C����Ǎ�
	std::string str;	// �Ǎ�������
	while (file >> str)
	{ // �t�@�C���̏I�[�ł͂Ȃ��ꍇ���[�v

		if (str.front() == '#') { std::getline(file, str); }	// �R�����g�A�E�g
		else if (str == "USERSET")
		{
			do { // END_USERSET��ǂݍ��ނ܂Ń��[�v

				// �������ǂݍ���
				file >> str;

				if (str.front() == '#') { std::getline(file, str); }	// �R�����g�A�E�g
				else if (str == "ROOM")
				{
					file >> str;		// ����Ǎ�
					file >> m_nRoom;	// �����ԍ���Ǎ�
				}
				else if (str == "FUN")
				{
					file >> str;	// ����Ǎ�
					file >> m_nFun;	// FUN�l��Ǎ�
				}
				else if (str == "PLAYTIME")
				{
					file >> str;			// ����Ǎ�
					file >> m_fPlayTime;	// ���v���C���Ԃ�Ǎ�
				}
			} while (str != "END_USERSET");	// END_USERSET��ǂݍ��ނ܂Ń��[�v
		}
	}

	// �t�@�C�������
	file.close();

	return S_OK;
}

//============================================================
//	�����f�[�^�̕ۑ�����
//============================================================
HRESULT CUserDataManager::SaveAllData
(
	CPlayerStatus* pStatus,	// �v���C���[�X�e�[�^�X���
	CPlayerItem* pItem		// �v���C���[�����A�C�e�����
)
{
	// �t�@�C�����J��
	std::ofstream file(FILE0_TXT);	// �t�@�C���X�g���[��
	if (file.fail())
	{ // �t�@�C�����J���Ȃ������ꍇ

		// �G���[���b�Z�[�W�{�b�N�X
		MessageBox(nullptr, "�����f�[�^�̏����o���Ɏ��s�I", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �����_�̏����o���������w��
	file << std::fixed << std::setprecision(4);

	// ���o���̏����o��
	file << "#==============================================================================" << std::endl;
	file << "#" << std::endl;
	file << "#	�����f�[�^�e�L�X�g [file0.txt]" << std::endl;
	file << "#	Author : ���c �E��" << std::endl;
	file << "#" << std::endl;
	file << "#==============================================================================" << std::endl;

	// �X�e�[�^�X�̏����o��
	file << "#------------------------------------------------------------------------------" << std::endl;
	file << "#	�X�e�[�^�X���" << std::endl;
	file << "#------------------------------------------------------------------------------" << std::endl;
	file << "STATUSSET" << std::endl;
	file << "	NAME 		= " << pStatus->GetName()		<< std::endl;
	file << "	LOVE 		= " << pStatus->GetLove()		<< std::endl;
	file << "	HP 			= " << pStatus->GetHP()			<< std::endl;
	file << "	MAX_HP 		= " << pStatus->GetMaxHP()		<< std::endl;
	file << "	EXP			= " << pStatus->GetExp()		<< std::endl;
	file << "	WPN_ITEMIDX	= " << pStatus->GetWpnItemIdx()	<< std::endl;
	file << "	AMR_ITEMIDX	= " << pStatus->GetAmrItemIdx()	<< std::endl;
	file << "	NUM_GOLD	= " << pStatus->GetNumGold()	<< std::endl;
	file << "	NUM_KILL	= " << pStatus->GetNumKill()	<< std::endl;
	file << "END_STATUSSET" << std::endl;
	file << std::endl;

	// �����A�C�e���̏����o��
	file << "#------------------------------------------------------------------------------" << std::endl;
	file << "#	�����A�C�e�����" << std::endl;
	file << "#------------------------------------------------------------------------------" << std::endl;
	file << "ITEMSET" << std::endl;
	for (int i = 0; i < pItem->GetNumItem(); i++)
	{ // �����A�C�e�������J��Ԃ�

		file << "	ITEMIDX = " << pItem->GetItemIdx(i) << std::endl;
	}
	file << "END_ITEMSET" << std::endl;
	file << std::endl;

	// �A�C�e���{�b�N�X�̏����o��
	file << "#------------------------------------------------------------------------------" << std::endl;
	file << "#	�A�C�e���{�b�N�X���" << std::endl;
	file << "#------------------------------------------------------------------------------" << std::endl;
	file << "ITEMBOXSET" << std::endl;
	// TODO�F�����ɃA�C�e���{�b�N�X���C���f�b�N�X�̏����o��
	file << "END_ITEMBOXSET" << std::endl;
	file << std::endl;

	// �����Ƀ��[�U�[�f�[�^�̏����o��
	file << "#------------------------------------------------------------------------------" << std::endl;
	file << "#	���[�U�[�f�[�^���" << std::endl;
	file << "#------------------------------------------------------------------------------" << std::endl;
	file << "USERSET" << std::endl;
	file << "	ROOM	 = " << m_nRoom		<< std::endl;
	file << "	FUN		 = " << m_nFun		<< std::endl;
	file << "	PLAYTIME = " << m_fPlayTime	<< std::endl;
	file << "END_USERSET" << std::endl;

	// �t�@�C�������
	file.close();

	return S_OK;
}

//============================================================
//	�����f�[�^�ۑ��t�@�C�������邩�̊m�F����
//============================================================
bool CUserDataManager::IsCheckSaveData()
{
	// �w�肵���p�X�����邩��Ԃ�
	return std::filesystem::exists(FILE0_TXT);
}

//============================================================
//	���v���C���ԕ�����̎擾����
//============================================================
std::string CUserDataManager::GetStrPlayTime()
{
	// �v���C���Ԃ�/�b�ɕϊ�
	const long lLongTime = (DWORD)(m_fPlayTime * 1000.0f);		// ���v���C��������
	const int nSecTime = (int)(lLongTime / 1000) % 60;			// ���v���C�����b
	const int nMinTime = (int)(lLongTime / 60000);				// ���v���C������

	// �b�����ꌅ�̏ꍇ�̓[�����ߗp��������쐬
	const std::string sZero = (nSecTime < 10) ? "0" : "";

	// ��/�b�𕶎���ɕϊ�
	const std::string sSec = sZero + std::to_string(nSecTime);	// ���v���C�b������
	const std::string sMin = std::to_string(nMinTime);			// ���v���C��������

	// ���v���C���ԕ�������쐬���Ԃ�
	return (sMin + ":" + sSec);
}
